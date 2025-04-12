#include "node.h"

Connection *rightConnection;
Connection *leftConnection;
Connection *monitorConnection;
Message receivedMessage;
uint8_t myPwr;
uint64_t previousMillis = 0;

bool connectionError = false;

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

void OnDataRecv(const uint8_t *mac, const uint8_t *data, int data_len)
{
    Message sendMessage;
    memcpy(&receivedMessage, data, sizeof(receivedMessage));
    Serial.print("Received data: ");
    Serial.println(receivedMessage.data);
    if (receivedMessage.messageType == PWR)
    {
        if ((receivedMessage.data) == 10)
        {
            myPwr = receivedMessage.data;
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
        }
    }
    else if (receivedMessage.messageType == LDR)
    {
    }
}

Node::Node(ILight *light, ILdr *ldr, IMovementSensor *movementSensor, uint8_t *peerAddressLeft, uint8_t *peerAddressRight, uint8_t *monitorAddress)

{
    state = IDLE;
    this->light = light;
    this->ldr = ldr;
    this->movementSensor = movementSensor;
    leftConnection = new Connection(peerAddressLeft, &OnDataRecv);
    rightConnection = new Connection(peerAddressRight, &OnDataRecv);
    monitorConnection = new Connection(monitorAddress, &OnDataRecv);
    if (isMACAllZero(peerAddressLeft))
    {
        mostLeftNode = true;
    }
    if (isMACAllZero(peerAddressRight))
    {
        mostRightNode = true;
    }
}

void Node::HandleDay() // include deepsleep and sending a message on wakeup
{
    myPwr = 0;
    uint16_t lightLevel = ldr->ReadLightLevel();
    Serial.println(lightLevel);
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
    Message msg;
    if (connectionError)
    {
        myPwr = LEVEL4;
    }
    else
    {
        myPwr = LEVEL1;
    }
    light->AdjustLightIntensity(myPwr);
    if (millis() - previousMillis > 2000)
    {
        uint16_t lightLevel = ldr->ReadLightLevel();
        Serial.println(lightLevel);
        if (!light->LightCheck())
        {
            state = HARDWARE_ERROR;
        }
        if (lightLevel >= LIGHT_THRESHOLD)
        {
            state = DAY;
        }
        Ping();
        previousMillis = millis();
    }
    if (movementSensor->DetectMovement())
    {
        myPwr = LEVEL5;
        light->AdjustLightIntensity(myPwr);
        msg.messageType = PWR;
        msg.data = myPwr;
        if (mostLeftNode)
        {
            rightConnection->SendData(msg);
        }
        else if (mostRightNode)
        {
            leftConnection->SendData(msg);
        }
        else
        {
            leftConnection->SendData(msg);
            rightConnection->SendData(msg);
        }
        delay(2000);
    }
}

void Node::HandleHardwareError()
{
    Message msg;
    msg.messageType = ERR;
    msg.data = HARDWARE_ERROR_CODE;
    monitorConnection->SendData(msg);
    Serial.println("Hardware error detected");
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
    }
}

void Node::Ping()
{
    uint16_t lightLevel = ldr->ReadLightLevel();
    Message msg;
    msg.messageType = LDR;
    msg.data = lightLevel;

    if (mostLeftNode)
    {
        rightConnection->SendData(msg);
        if (rightConnection->GetSentStatus() == ESP_NOW_SEND_SUCCESS)
        {
            connectionError = false;
        }
        else
        {
            msg.messageType = ERR;
            msg.data = RIGHT_ERROR_CODE;
            delay(100);
            monitorConnection->SendData(msg);
            connectionError = true;
        }
    }
    else if (mostRightNode)
    {
        leftConnection->SendData(msg);
        if (leftConnection->GetSentStatus() == ESP_NOW_SEND_SUCCESS)
        {
            connectionError = false;
        }
        else
        {
            msg.messageType = ERR;
            msg.data = LEFT_ERROR_CODE;
            delay(100);
            monitorConnection->SendData(msg);
            connectionError = true;
        }
    }
    else
    {
        rightConnection->SendData(msg);
        if (rightConnection->GetSentStatus() == ESP_NOW_SEND_SUCCESS)
        {
            connectionError = false;
        }
        else
        {
            msg.messageType = ERR;
            msg.data = RIGHT_ERROR_CODE;
            delay(100);
            monitorConnection->SendData(msg);
            connectionError = true;
        }
        delay(100);
        leftConnection->SendData(msg);
        if (leftConnection->GetSentStatus() == ESP_NOW_SEND_SUCCESS)
        {
            connectionError = false;
        }
        else
        {
            msg.messageType = ERR;
            msg.data = LEFT_ERROR_CODE;
            delay(100);
            monitorConnection->SendData(msg);
            connectionError = true;
        }
    }
}
