#include "Engine.h"

Engine::Engine() : CAN(CS_PIN)
{
    this->temp = 0;
    Serial.begin(115200);
    pinMode(potPin, INPUT);
    pinMode(engineLEDPin, OUTPUT);
    if (CAN.begin(MCP_ANY, CAN_1000KBPS, MCP_8MHZ) == CAN_OK)
    {
        Serial.println("MCP2515 Initialized Successfully!");
    }
    else
    {
        Serial.println("Error Initializing MCP2515...");
        while (1)
            ;
    }
    CAN.setMode(MCP_NORMAL);
}

void Engine::CANListener()
{
    unsigned char len = 0;
    unsigned char buf[16];
    unsigned long canId = 0;

    while (1)
    {
        if (CAN_MSGAVAIL == CAN.checkReceive())
        {
            if (CAN.readMsgBuf(&canId, &len, buf) == CAN_OK)
            {
                Serial.print("ID: ");
                canId = canId & 0x7FF;
                Serial.println(canId, HEX);
                Serial.print(" Data: ");
                for (int i = 0; i < len; i++)
                {
                    Serial.print(buf[i], HEX);
                    Serial.println(" ");
                }

                if (canId == BRAKES_ID)
                {
                    if ((char)buf[0] == 'B')
                    {
                        if (this->engineState == RUNNING)
                        {
                            this->engineState = STOPPED;
                            Serial.println("Engine STOPPED");
                        }
                        else
                        {
                            this->engineState = RUNNING;
                            Serial.println("Engine RUNNING");
                        }
                    }
                }
                else if (canId == SPEED_ID)
                {
                    if (len == 2)
                    {
                        speed = (buf[0] << 8 | buf[1]);
                        Serial.println(speed);
                    }
                }
            }
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    vTaskDelete(nullptr);
}

void Engine::HandleTempStates()
{
    while (1)
    {
        if (this->tempState == NORMAL)
        {
            if (previousTempState == HIGH_TEMP)
            {
                this->SendTempOK();
            }
            this->UpdateTemp();
            if (this->temp > TEMP_THRESHOLD)
            {
                this->tempState = HIGH_TEMP;
            }

            previousTempState = NORMAL;
        }
        else if (this->tempState == HIGH_TEMP)
        {
            if (previousTempState == NORMAL)
            {
                this->SendHighTempAlert();
            }
            this->UpdateTemp();
            if (this->temp < TEMP_THRESHOLD)
            {
                this->tempState = NORMAL;
            }
            previousTempState = HIGH_TEMP;
        }
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(nullptr);
}

void Engine::HandleEngineStates()
{
    while (1)
    {
        if (this->engineState == RUNNING)
        {
            digitalWrite(engineLEDPin, HIGH);
        }
        else if (this->engineState == STOPPED)
        {
            digitalWrite(engineLEDPin, LOW);
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    vTaskDelete(nullptr);
}

void Engine::UpdateTemp()
{
    int sensorValue = analogRead(potPin);
    this->temp = map(sensorValue, 0, 1023, 0, 128);
    Serial.println("Temperature: " + String(this->temp));
    if (CAN.sendMsgBuf(TEMP_ID, 0, sizeof(this->temp), (unsigned char *)&this->temp) == CAN_OK)
    {
        Serial.println("Temperature Sent Successfully!");
    }
    else
    {
        Serial.println("Error Sending Temperature...");
        Serial.println();
    }
}

void Engine::SendHighTempAlert()
{
    unsigned char message[] = "H";
    if (CAN.sendMsgBuf(HIGH_TEMP_ID, 0, sizeof(message), message) == CAN_OK)
    {
        Serial.println("High Temperature Alert Sent Successfully!");
    }
    else
    {
        Serial.println("Error Sending High Temperature Alert...");
        Serial.println(CAN.sendMsgBuf(HIGH_TEMP_ID, 0, sizeof(message), message));
    }
}

void Engine::SendTempOK()
{
    unsigned char message[] = "OK";
    if (CAN.sendMsgBuf(TEMP_OK_ID, 0, sizeof(message), message) == CAN_OK)
    {
        Serial.println("Temperature OK Sent Successfully!");
    }
    else
    {
        Serial.println("Error Sending Temperature OK...");
    }
}

void Engine::PingListener()
{
    while (1)
    {
        unsigned char len = 0;
        unsigned char buf[16];
        unsigned long canId = 0;

        if (CAN_MSGAVAIL == CAN.checkReceive())
        {
            if (CAN.readMsgBuf(&canId, &len, buf) == CAN_OK)
            {
                Serial.print("ID: ");
                canId = canId & 0x7FF;
                Serial.print(canId, HEX);
                Serial.print(" Data: ");
                for (int i = 0; i < len; i++)
                {
                    Serial.print(buf[i], HEX);
                    Serial.print(" ");
                }
                if (canId == ENGINE_PING_ID)
                {
                    if ((int)buf[0] == 1)
                    {
                        CAN.sendMsgBuf(ENGINE_PING_ID, 0, sizeof(buf), buf);
                    }
                }
            }
        }
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
    vTaskDelete(nullptr);
}