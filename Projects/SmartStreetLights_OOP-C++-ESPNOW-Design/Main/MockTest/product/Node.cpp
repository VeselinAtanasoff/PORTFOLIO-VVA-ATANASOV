#include <Node.h>

Node::Node(PositionMac *peerMACs, IConnection &connection, ILight &light, ILdr &lightSensor, IMovementSensor &movementSensor)
    : connection(connection), light(light), lightSensor(lightSensor), movementSensor(movementSensor)
{
    memcpy((peerMACs->left), (this->peerLeftAddress), sizeof(peerMACs->left));
    memcpy((peerMACs->right), (this->peerRightAddress), sizeof(peerMACs->right));
    memcpy((peerMACs->most_left), (this->peerAltLeftAddress), sizeof(peerMACs->most_left));
    memcpy((peerMACs->most_right), (this->peerAltRightAddress), sizeof(peerMACs->most_right));
    memcpy((peerMACs->monitor), (this->monitorAddress), sizeof(peerMACs->monitor));
}

void Node::HandleDay()
{
    uint16_t lightLevel = lightSensor.ReadLightLevel();

    if (!light.LightCheck())
    {
        state = HARDWARE_ERROR;
    }
    else if (lightLevel < 400)
    {
        myPower = LEVEL1;
        state = NIGHT;
    }
}

void Node::HandleNight()
{
    uint16_t lightLevel = lightSensor.ReadLightLevel();

    if (!light.LightCheck())
    {
        state = HARDWARE_ERROR;
        return;
    }
    else if (lightLevel >= 400)
    {
        state = DAY;
        return;
    }

    if (movementSensor.DetectMovement())
    {
        myPower = LEVEL5;
        light.AdjustLightIntensity(myPower);
        message.messageType = PWR;
        message.data = myPower;
        connection.SendData(message);
        if (!connection.GetSentStatus())
        {
            lastState = state;
            state = CONNECTION_ERROR_DETECTION;
        }
    }
}

void Node::HandleConnectionError()
{
    Message msg;
    msg.messageType = ERR;

    if (mostLeftNode == false && mostRightNode == false)
    {
        if (!connection.GetSentStatus())
        {
            msg.data = LEFT_ERROR_CODE;
            connection.SendData(msg);
        }
        if (!connection.GetSentStatus())
        {
            msg.data = RIGHT_ERROR_CODE;
            connection.SendData(msg);
        }
    }
    else if (mostLeftNode == true)
    {
        if (!connection.GetSentStatus())
        {
            msg.data = RIGHT_ERROR_CODE;
            connection.SendData(msg);
        }
    }
    else if (mostRightNode == true)
    {
        if (!connection.GetSentStatus())
        {
            msg.data = LEFT_ERROR_CODE;
            connection.SendData(msg);
        }
    }

    state = lastState;
}

void Node::HandleConnectionErrorDetection()
{
    uint8_t errorCount = 0;

    while (errorCount != 5)
    {
        connection.SendData(lastMessage);
        if (!connection.GetSentStatus())
        {
            errorCount++;
        }
        else
        {
            state = lastState;
            break;
        }
    }
    if (errorCount == 5)
    {
        state = CONNECTION_ERROR;
    }
}

void Node::HandleHardwareError()
{
    

    Message msg;
    msg.messageType = ERR;
    msg.data = HARDWARE_ERROR_CODE;
    connection.SendData(msg);

}

States Node::HandleStates()
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

    return state;
}