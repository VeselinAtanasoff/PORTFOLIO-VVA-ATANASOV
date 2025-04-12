#include <Arduino.h>
#include <mcp_can.h>
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Dashboard.h"
#include "LCDScreen.h"

#define CAN0_INT 2

Dashboard *dashboard;

void setup()
{
  Wire.begin();
  Serial.begin(115200);

  dashboard = new Dashboard(CAN0_INT);

  byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for (address = 1; address < 127; address++)
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
      {
        Serial.print("0");
      }
      Serial.println(address, HEX);
      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknow error at address 0x");
      if (address < 16)
      {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
  {
    Serial.println("No I2C devices found\n");
  }
  else
  {
    Serial.println("done\n");
  }

  xTaskCreate([](void *parameters)
              { dashboard->CANListener(); }, "CANListener", 8192, NULL, 1, NULL);
  xTaskCreate([](void *parameters)
              { dashboard->ButtonListener(); }, "CANListener", 4096, NULL, 1, NULL);
  xTaskCreate([](void *parameters)
              { dashboard->PotentiometerListener(); }, "CANListener", 4096, NULL, 1, NULL);
  xTaskCreate([](void *parameters)
              { dashboard->StatusCheck(); }, "StatusCheck", 4096, NULL, 1, NULL);
}

void loop()
{
}