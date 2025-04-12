#include "Headlights.h"
#include "Indicator.h"
#include <mcp_can.h>
#include <SPI.h>

#define CAN_CS 5
#define PING_ID 0x012

const int lIndicatorPin = 15;
const int rIndicatorPin = 2;

MCP_CAN CAN(CAN_CS);
Headlights *headlights;
Indicator *leftIndicator;
Indicator *rightIndicator;

void CanListener()
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
        if (canId == HEADLIGHTS_ID)
        {
          if ((int)buf[0] == 1)
          {
            xTaskCreate([](void *pvParameters)
                        { headlights->SwitchOnOff(); }, "SwitchOnOff", 2048, NULL, 1, NULL);
          }
        }
        else if (canId == INDICATOR_ID)
        {
          if ((char)buf[0] == 'R')
          {
            xTaskCreate([](void *pvParameters)
                        { rightIndicator->SwitchOnOff(); }, "SwitchRBlinkerOnOff", 2048, NULL, 1, NULL);
          }
          else if ((char)buf[0] == 'L')
          {
            xTaskCreate([](void *pvParameters)
                        { leftIndicator->SwitchOnOff(); }, "SwitchLBlinkerOnOff", 2048, NULL, 1, NULL);
          }
        }
        else if (canId == PING_ID)
        {
          vTaskDelay(100 / portTICK_PERIOD_MS);
          unsigned char message[] = {0x01};
          if (CAN.sendMsgBuf(PING_ID, 0, 1, message) == CAN_OK)
          {
            Serial.println("Ping response sent successfully!");
          }
          else
          {
            Serial.println("Error sending ping response!");
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
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
  vTaskDelete(nullptr);
}

void setup()
{
  Serial.begin(115200);

  // Initialize MCP2515
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
  Serial.println("MCP2515 in Normal Mode...");
  headlights = new Headlights();
  leftIndicator = new Indicator(lIndicatorPin);
  rightIndicator = new Indicator(rIndicatorPin);
  xTaskCreate([](void *pvParameters)
              { CanListener(); }, "CanListener", 4096, NULL, 1, NULL);
  xTaskCreate([](void *pvParameters)
              { leftIndicator->Blink(); }, "BlinkLeftIndicator", 2048, NULL, 1, NULL);
  xTaskCreate([](void *pvParameters)
              { rightIndicator->Blink(); }, "BlinkRightIndicator", 2048, NULL, 1, NULL);
  Serial.println("Lights node initialized...");
}

void loop()
{
}