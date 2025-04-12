#include <Arduino.h>
#include <mcp_can.h>
#include <SPI.h>
#include "Engine.h"

Engine *engine;

void setup()
{
  engine = new Engine();
  xTaskCreate([](void *parameters)
              { engine->CANListener(); }, "CANListener", 2048, NULL, 1, NULL);
  xTaskCreate([](void *parameters)
              { engine->HandleTempStates(); }, "HandleTempStates", 2048, NULL, 1, NULL);
  xTaskCreate([](void *parameters)
              { engine->HandleEngineStates(); }, "HandleEngineStates", 2048, NULL, 1, NULL);
  xTaskCreate([](void *parameters)
              { engine->PingListener(); }, "PingListener", 2048, NULL, 1, NULL);
}

void loop() {}
