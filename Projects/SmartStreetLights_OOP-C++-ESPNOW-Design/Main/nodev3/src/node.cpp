#include "node.h"
#include <algorithm>
#include <iostream>

uint8_t myPwr = 0;
uint8_t rightErrCounter = 0;
uint8_t leftErrCounter = 0;
Message receivedMessage;
Connection *rightConnection;
Connection *leftConnection;
Connection *monitorConnection;

uint8_t peerLeftAddress[MACADDRESSLENGTH];
uint8_t peerRightAddress[MACADDRESSLENGTH];
uint8_t monitorAddress[MACADDRESSLENGTH];

unsigned long previousMillis = 0;
bool isLeftError = false;
bool isRightError = false;
bool lastLeftErrState = false;
bool lastRightErrState = false;

bool mostLeftNode = false;
bool mostRightNode = false;

bool isMACAllZero(uint8_t *mac)
{
    for (int i = 0; i < MACADDRESSLENGTH; i++)
    {
        if (mac[i] != 0)
        {
            return false;
        }
    }
    return true;
}

bool isMonitorMac(const uint8_t *mac)
{
    uint8_t monitorAddress[MACADDRESSLENGTH] = {0x7C, 0x9E, 0xBD, 0xF3, 0xDE, 0x0C};

    for (int i = 0; i < MACADDRESSLENGTH; i++)
    {
        if (mac[i] != monitorAddress[i])
        {
            return false;
        }
    }

    return true;
}

void OnDataRecv(const uint8_t *mac, const uint8_t *data, int data_len) // Update function to receive adresses from monitor
{
    Serial.println("received");
    Message sendMessage;
    PositionMac receivedMac;

    switch (isMonitorMac(mac))
    {
    case true:
        Serial.println("is monitor");
        memcpy(&receivedMac, data, sizeof(receivedMac));
        // if (leftConnection != nullptr)
        // {
        //     leftConnection->RemovePeer();
        //     delete leftConnection;
        // }
        // if (rightConnection != nullptr)
        // {
        //     rightConnection->RemovePeer();
        //     delete rightConnection;
        // }
        leftConnection->RemovePeer();
        rightConnection->RemovePeer();
        memcpy(peerLeftAddress, receivedMac.left, sizeof(peerLeftAddress));
        memcpy(peerRightAddress, receivedMac.right, sizeof(peerRightAddress));
        leftConnection->AddPeer(peerLeftAddress);
        rightConnection->AddPeer(peerRightAddress);
        // if (!isMACAllZero(peerLeftAddress))
        // {
        //     leftConnection = new Connection((peerLeftAddress), &OnDataRecv);
        // }
        // if (!isMACAllZero(peerRightAddress))
        // {
        //     rightConnection = new Connection((peerRightAddress), &OnDataRecv);
        // }

        for (int i = 0; i < MACADDRESSLENGTH; i++)
        {
            Serial.print(peerLeftAddress[i], HEX);
        }
        Serial.println();
        for (int i = 0; i < MACADDRESSLENGTH; i++)
        {
            Serial.print(peerRightAddress[i], HEX);
        }
        Serial.println();

        if (isMACAllZero(receivedMac.left))
        {
            mostLeftNode = true;
        }
        if (isMACAllZero(receivedMac.right))
        {
            mostRightNode = true;
        }
        break;

    case false:
        memcpy(&receivedMessage, data, sizeof(receivedMessage));

        if ((receivedMessage.data) == 10)
        {
            myPwr = receivedMessage.data;

            Serial.print("current power: ");
            Serial.println(myPwr);
        }
        else if (receivedMessage.data >= myPwr) // The power is updated based on the message received, if the data of the message
                                                // is less or equal to the current power, current power will not change
        {
            myPwr = (receivedMessage.data) - 25;
            sendMessage.data = myPwr;

            if (mostLeftNode)
            {
                rightConnection->SendData(sendMessage);
            }
            else if (mostRightNode)
            {
                leftConnection->SendData(sendMessage);
            }
            else
            {
                leftConnection->SendData(sendMessage);
                rightConnection->SendData(sendMessage); // This node also sends its power to the neighbouring nodes if a message is received
            }

            Serial.print("current power: ");
            Serial.println(myPwr);
        }

        break;
    }
}

Node::Node(PositionMac *peerMACs, ILight *paramLight, ILdr *paramPotm, IMovementSensor *paramMovementSensor)
{
    memcpy((peerLeftAddress), (peerMACs->left), sizeof(peerLeftAddress));
    memcpy((peerRightAddress), (peerMACs->right), sizeof(peerRightAddress));
    memcpy((monitorAddress), (peerMACs->monitor), sizeof(monitorAddress));

    light = paramLight;
    ldr = paramPotm;
    movementSensor = paramMovementSensor;

    leftConnection = new Connection((peerLeftAddress), &OnDataRecv);
    rightConnection = new Connection((peerRightAddress), &OnDataRecv);
    Serial.println("Peers initialized");
    if (isMACAllZero(peerLeftAddress))
    {
        mostLeftNode = true;
        Serial.println("most left node");
    }
    if (isMACAllZero(peerRightAddress))
    {
        mostRightNode = true;
        Serial.println("most right node");
    }
    monitorConnection = new Connection((monitorAddress), &OnDataRecv);
}

void Node::HandleDay() // include deepsleep and sending a message on wakeup
{
    Serial.println("day state");
    lastState = state;
    myPwr = LEVEL0;
    uint16_t lightLevel = ldr->ReadLightLevel();
    light->AdjustLightIntensity(myPwr);

    if (!light->LightCheck())
    {
        state = HARDWARE_ERROR;
    }

    if (lightLevel < LIGHT_THRESHOLD)
    {
        myPwr = LEVEL1;
        light->AdjustLightIntensity(myPwr);
        state = NIGHT;
    }
    delay(5000);
}

void Node::HandleNight()
{
    Serial.println("in night");
    lastState = state;
    Message msg;
    uint16_t lightLevel = ldr->ReadLightLevel();
    msg.messageType = PING;
    msg.data = 0;

    if (!light->LightCheck())
    {
        state = HARDWARE_ERROR;
    }

    if (lightLevel >= LIGHT_THRESHOLD)
    {
        state = DAY;
    }

    if (!isMACAllZero(peerLeftAddress))
    {
        leftConnection->SendData(msg);
        if (leftConnection->GetSentStatus() == ESP_NOW_SEND_SUCCESS)
        {
            isLeftError = false;
            leftErrCounter = 0;
        }
        else
        {
            leftErrCounter++;
        }
    }
    if (!isMACAllZero(peerRightAddress))
    {
        rightConnection->SendData(msg);
        if (rightConnection->GetSentStatus() == ESP_NOW_SEND_SUCCESS)
        {
            isRightError = false;
            rightErrCounter = 0;
        }
        else
        {
            rightErrCounter++;
        }
    }

    if (leftErrCounter >= 10)
    {
        isLeftError = true;
        myPwr = LEVEL2;
        light->AdjustLightIntensity(myPwr);
        Serial.println("compensating");
    }
    if (rightErrCounter >= 10)
    {
        isRightError = true;
        myPwr = LEVEL2;
        light->AdjustLightIntensity(myPwr);
        Serial.println("compensating");
    }

    if ((isRightError != lastRightErrState) || (isLeftError != lastLeftErrState))
    {
        if (isRightError || isLeftError)
        {
            state = CONNECTION_ERROR;
        }

        lastLeftErrState = isLeftError;
        lastRightErrState = isRightError;
    }

    if (millis() - previousMillis > 7000)
    {
        myPwr = LEVEL1;
        light->AdjustLightIntensity(myPwr);
        previousMillis = millis();
    }

    if (movementSensor->DetectMovement())
    {
        Serial.println("person detected sending message...");
        myPwr = LEVEL5;
        light->AdjustLightIntensity(myPwr);
        msg.messageType = PWR;
        msg.data = myPwr;

        if (leftConnection != nullptr)
        {
            leftConnection->SendData(msg);
            Serial.println("left sent");
        }
        if (rightConnection != nullptr)
        {
            rightConnection->SendData(msg);
            Serial.println("right sent");
        }
    }
    Serial.print("My power: ");
    Serial.println(myPwr);
    delay(500);
}

void Node::HandleConnectionError()
{
    Serial.println("connection error");
    Message errorMsg;
    errorMsg.messageType = ERR;
    errorMsg.data = 1;
    monitorConnection->SendData(errorMsg);
    delay(100);
    state = NIGHT;
}

void Node::HandleHardwareError()
{
    Serial.println("light bulb ded");
    Message msg;
    msg.messageType = ERR;
    msg.data = HARDWARE_ERROR_CODE;
    monitorConnection->SendData(msg);
    delay(10000);
}

void Node::HandleStates()
{
    switch (state)
    {
    case IDLE:
        state = DAY;
        break;

    case DAY:
        HandleDay();
        break;

    case NIGHT:
        HandleNight();
        break;
    case HARDWARE_ERROR:
        HandleHardwareError();
        break;
    case CONNECTION_ERROR:
        HandleConnectionError();
        break;
    }
}