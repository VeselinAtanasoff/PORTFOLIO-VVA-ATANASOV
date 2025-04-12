#pragma once

#include <Arduino.h>
#include <mcp_can.h>
#include <SPI.h>
#include "States.h"

constexpr int potPin = 12;
constexpr int CS_PIN = 5;
constexpr int PSI_THRESHOLD = 30;
constexpr unsigned long LOW_PSI_ID = 0x004;
constexpr unsigned long PSI_OK_ID = 0x008;
constexpr unsigned long PSI_ID = 0x009;
constexpr unsigned long PING_ID = 0x011;

class Tires{
    public:
        Tires();
        void HandleStates();
        void updatePSI();
        void SendLowPSIAlert();
        void SendPSIOK();
        void PingListener();
    private:
        uint8_t PSI;
        States state=NORMAL;
        States previousState=NORMAL;
        MCP_CAN CAN;
};