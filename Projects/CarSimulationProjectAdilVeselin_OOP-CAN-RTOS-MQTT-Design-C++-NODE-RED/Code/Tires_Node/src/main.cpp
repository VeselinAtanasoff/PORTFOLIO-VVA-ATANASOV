#include <Arduino.h>
#include <mcp_can.h>
#include <SPI.h>
#include "Tires.h"

Tires *tires;

void setup()
{
  tires = new Tires();
  xTaskCreate([](void *pvParameters)
              { tires->HandleStates(); }, "HandleStates", 4096, NULL, 1, NULL);
  xTaskCreate([](void *pvParameters)
              { tires->PingListener(); }, "PingListener", 4096, NULL, 1, NULL);
}

void loop() {}
