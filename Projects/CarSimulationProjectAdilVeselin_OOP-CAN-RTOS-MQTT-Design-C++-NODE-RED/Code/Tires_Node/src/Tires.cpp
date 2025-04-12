#include "Tires.h"

Tires::Tires() : CAN(CS_PIN)
{
    this->PSI = 0;
    Serial.begin(115200);
    pinMode(potPin, INPUT);
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

void Tires::HandleStates()
{
    while (1)
    {
        if (this->state == NORMAL)
        {
            if (previousState == LOW_PSI)
            {
                this->SendPSIOK();
            }
            this->updatePSI();
            if (this->PSI < PSI_THRESHOLD)
            {
                this->state = LOW_PSI;
            }

            previousState = NORMAL;
        }
        else if (this->state == LOW_PSI)
        {
            if (previousState == NORMAL)
            {
                this->SendLowPSIAlert();
            }
            this->updatePSI();
            if (this->PSI > PSI_THRESHOLD)
            {
                this->state = NORMAL;
            }
            previousState = LOW_PSI;
        }
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(nullptr);
}

void Tires::updatePSI()
{
    int sensorValue = analogRead(potPin);
    this->PSI = map(sensorValue, 0, 1023, 0, 100);
    Serial.println("PSI: " + String(this->PSI));
    if (CAN.sendMsgBuf(PSI_ID, 0, sizeof(this->PSI), (unsigned char *)&this->PSI) == CAN_OK)
    {
        Serial.println("PSI Sent Successfully!");
    }
    else
    {
        Serial.println("Error Sending PSI...");
    }
    if (CAN.begin(MCP_ANY, CAN_1000KBPS, MCP_8MHZ) == CAN_OK)
    {
        Serial.println("MCP2515 Reinitialized Successfully!");
        CAN.setMode(MCP_NORMAL);
    }
    else
    {
        Serial.println("Error Reinitializing MCP2515...");
    }
}

void Tires::SendLowPSIAlert()
{
    unsigned char message[] = "L";
    if (CAN.sendMsgBuf(LOW_PSI_ID, 0, sizeof(message), message) == CAN_OK)
    {
        Serial.println("Low PSI Alert Sent Successfully!");
    }
    else
    {
        Serial.println("Error Sending Low PSI Alert...");
    }
}

void Tires::SendPSIOK()
{
    unsigned char message[] = "OK";
    if (CAN.sendMsgBuf(PSI_OK_ID, 0, sizeof(message), message) == CAN_OK)
    {
        Serial.println("PSI OK Sent Successfully!");
    }
    else
    {
        Serial.println("Error Sending PSI OK...");
    }
}

void Tires::PingListener()
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
                if (canId == PING_ID)
                {
                    if ((int)buf[0] == 1)
                    {
                        CAN.sendMsgBuf(PING_ID, 0, sizeof(buf), buf);
                    }
                }
            }
            if (CAN.begin(MCP_ANY, CAN_1000KBPS, MCP_8MHZ) == CAN_OK)
            {
                Serial.println("MCP2515 Reinitialized Successfully!");
                CAN.setMode(MCP_NORMAL);
            }
            else
            {
                Serial.println("Error Reinitializing MCP2515...");
            }
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    vTaskDelete(nullptr);
}