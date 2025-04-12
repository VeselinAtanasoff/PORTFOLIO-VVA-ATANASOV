#pragma once

#include <Arduino.h>
#include <mcp_can.h>
#include <SPI.h>
#include <TempStates.h>
#include <EngineStates.h>

constexpr unsigned long BRAKES_ID = 0x001;
constexpr unsigned long SPEED_ID = 0x002;
constexpr unsigned long HIGH_TEMP_ID = 0x003;
constexpr unsigned long TEMP_OK_ID = 0x007;
constexpr unsigned long TEMP_ID = 0x010;
constexpr unsigned long ENGINE_PING_ID = 0x013;

constexpr int potPin = 12;
constexpr int engineLEDPin = 25;
constexpr int CS_PIN = 5;
constexpr int TEMP_THRESHOLD = 105;

class Engine
{
public:
    Engine();

    void CANListener();
    void HandleTempStates();
    void HandleEngineStates();
    void UpdateTemp();
    void SendHighTempAlert();
    void SendTempOK();
    void PingListener();

private:
    uint8_t temp;
    int speed;
    TempStates tempState = NORMAL;
    TempStates previousTempState = NORMAL;
    EngineStates engineState = RUNNING;
    MCP_CAN CAN;
};