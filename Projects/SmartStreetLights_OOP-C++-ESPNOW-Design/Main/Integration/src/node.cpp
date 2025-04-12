#include "node.h"
#include <algorithm>
#include <iostream>

uint8_t myPwr = 0;
Message receivedMessage;
Connection *rightConnection;
Connection *leftConnection;
Connection *rightAltConnection;
Connection *leftAltConnection;
Connection *monitorConnection;

uint8_t peerLeftAddress[MACADDRESSLENGTH];
uint8_t peerAltLeftAddress[MACADDRESSLENGTH];
uint8_t peerRightAddress[MACADDRESSLENGTH];
uint8_t peerAltRightAddress[MACADDRESSLENGTH];
uint8_t monitorAddress[MACADDRESSLENGTH];

unsigned long previousMillis = 0;

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
    Message sendMessage;
    PositionMac receivedMac;

    switch (isMonitorMac(mac))
    {
    case true:
        memcpy(&receivedMac, data, sizeof(receivedMac));
        memcpy(peerAltLeftAddress, receivedMac.most_left, sizeof(peerAltLeftAddress));
        memcpy(peerLeftAddress, receivedMac.left, sizeof(peerLeftAddress));
        memcpy(peerRightAddress, receivedMac.right, sizeof(peerRightAddress));
        memcpy(peerAltRightAddress, receivedMac.most_right, sizeof(peerAltRightAddress));
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

            if (!isMACAllZero(peerLeftAddress))
            {
                leftConnection->SendData(sendMessage);
            }
            if (!isMACAllZero(peerRightAddress))
            {
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
    memcpy((peerAltLeftAddress), (peerMACs->most_left), sizeof(peerAltLeftAddress));
    memcpy((peerAltRightAddress), (peerMACs->most_right), sizeof(peerAltRightAddress));
    memcpy((monitorAddress), (peerMACs->monitor), sizeof(monitorAddress));

    light = paramLight;
    ldr = paramPotm;
    movementSensor = paramMovementSensor;

    if (!isMACAllZero(peerRightAddress))
    {
        rightConnection = new Connection((peerRightAddress), &OnDataRecv);
        Serial.println("right initialized");
    }
    else
    {
        mostRightNode = true;
        Serial.println("this is most right node");
    }
    if (!isMACAllZero(peerLeftAddress))
    {
        leftConnection = new Connection((peerLeftAddress), &OnDataRecv);
        Serial.println("left initialized");
    }
    else
    {
        mostLeftNode = true;
        Serial.println("this is most left node");
    }
    if (!isMACAllZero(peerAltLeftAddress))
    {
        leftAltConnection = new Connection((peerAltLeftAddress), &OnDataRecv);
        Serial.println("most left initialized");
    }
    else if (!isMACAllZero(peerAltRightAddress))
    {
        rightAltConnection = new Connection((peerAltRightAddress), &OnDataRecv);
        Serial.println("most right initialized");
    }
    monitorConnection = new Connection((monitorAddress), &OnDataRecv);
}

void Node::HandleDay() // include deepsleep and sending a message on wakeup
{
    lastState = state;
    myPwr = 0;
    uint16_t lightLevel = ldr->ReadLightLevel();
    light->AdjustLightIntensity(myPwr);
    if (!light->LightCheck())
    {
        state = HARDWARE_ERROR;
    }
    delay(1000);
    if (lightLevel < LIGHT_THRESHOLD)
    {
        state = NIGHT;
    }
}

void Node::HandleNight()
{
    lastState = state;
    Message msg;
    uint16_t lightLevel = ldr->ReadLightLevel();
    if (millis() - previousMillis > 2000)
    {
        if (!light->LightCheck())
        {
            state = HARDWARE_ERROR;
        }
        previousMillis = millis();
    }

    if (lightLevel >= LIGHT_THRESHOLD)
    {
        state = DAY;
    }
    myPwr = LEVEL1;
    light->AdjustLightIntensity(myPwr);

    if (movementSensor->DetectMovement())
    {
        Serial.println("person detected sending message...");
        myPwr = LEVEL5;
        light->AdjustLightIntensity(myPwr);
        msg.messageType = PWR;
        msg.data = myPwr;
        lastMessage = msg;
        if (isMACAllZero(peerLeftAddress))
        {
            mostLeftNode = true;
        }
        else
        {
            leftConnection->SendData(msg);
            if (leftConnectionStatus == false)
            {
                leftAltConnection->SendData(msg);
                Serial.println("trying to send left alt");
            }
            if ((leftConnection->GetSentStatus()) == ESP_NOW_SEND_FAIL)
            {
                state = CONNECTION_ERROR_DETECTION;
            }
            else
            {
                leftConnectionStatus = true;
                // delete leftAltConnection;
            }
            mostLeftNode = false;
        }
        if (isMACAllZero(peerRightAddress))
        {
            mostRightNode = true;
        }
        else
        {
            rightConnection->SendData(msg);

            if (rightConnectionStatus == false)
            {
                rightAltConnection->SendData(msg);
                Serial.println("trying to send right alt");
            }

            if ((rightConnection->GetSentStatus()) == ESP_NOW_SEND_FAIL)
            {
                state = CONNECTION_ERROR_DETECTION;
            }
            else
            {
                rightConnectionStatus = true;
                // delete rightAltConnection;
            }
            mostRightNode = false;
        }
    }
}

void Node::HandleConnectionErrorDetection()
{
    uint8_t errorCount = 0;
    Serial.println("entered hardware connection detection");

    if ((mostLeftNode == false) && (mostRightNode == false))
    {
        while (errorCount < 5)
        {
            leftConnection->SendData(lastMessage);
            rightConnection->SendData(lastMessage);
            if (((leftConnection->GetSentStatus()) == ESP_NOW_SEND_FAIL) || ((rightConnection->GetSentStatus()) == ESP_NOW_SEND_FAIL))
            {
                errorCount++;
            }
            else
            {
                state = lastState;
                break;
            }
            delay(20);
        }
    }
    else if (mostLeftNode == true)
    {
        while (errorCount < 5)
        {
            rightConnection->SendData(lastMessage);
            if ((rightConnection->GetSentStatus()) == ESP_NOW_SEND_FAIL)
            {
                errorCount++;
            }
            else
            {
                state = lastState;
                break;
            }
            delay(20);
        }
    }
    else if (mostRightNode == true)
    {
        while (errorCount < 5)
        {
            leftConnection->SendData(lastMessage);
            if ((leftConnection->GetSentStatus()) == ESP_NOW_SEND_FAIL)
            {
                errorCount++;
            }
            else
            {
                state = lastState;
                break;
            }
            delay(20);
        }
    }

    if (errorCount >= 5)
    {
        state = CONNECTION_ERROR;
    }
}

void Node::HandleConnectionError()
{
    Message msg;
    msg.messageType = ERR;

    if (mostLeftNode == false && mostRightNode == false)
    {
        if ((leftConnection->GetSentStatus()) == ESP_NOW_SEND_FAIL)
        {
            msg.data = LEFT_ERROR_CODE;
            monitorConnection->SendData(msg);
            Serial.println("this is left");
            leftConnectionStatus = false;
        }
        if ((rightConnection->GetSentStatus()) == ESP_NOW_SEND_FAIL)
        {
            msg.data = RIGHT_ERROR_CODE;
            monitorConnection->SendData(msg);
            Serial.println("this is right");
            rightConnectionStatus = false;
        }
    }
    else if (mostLeftNode == true)
    {
        if ((rightConnection->GetSentStatus()) == ESP_NOW_SEND_FAIL)
        {
            msg.data = RIGHT_ERROR_CODE;
            monitorConnection->SendData(msg);
            rightConnectionStatus = false;
        }
    }
    else if (mostRightNode == true)
    {
        if ((leftConnection->GetSentStatus()) == ESP_NOW_SEND_FAIL)
        {
            msg.data = LEFT_ERROR_CODE;
            monitorConnection->SendData(msg);
            leftConnectionStatus = false;
        }
    }

    state = lastState;
}

void Node::HandleHardwareError()
{
    Message msg;
    msg.messageType = ERR;
    msg.data = HARDWARE_ERROR_CODE;
    monitorConnection->SendData(msg);
    delay(1000);
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
    case CONNECTION_ERROR_DETECTION:
        HandleConnectionErrorDetection();
        break;
    }
}