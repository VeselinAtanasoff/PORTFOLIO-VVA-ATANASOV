#pragma once

#include <Arduino.h>
#include <mcp_can.h>
#include <SPI.h>
#include "LCDScreen.h"

#define BRAKES_ID 0x001
#define SPEED_ID 0x002
#define HIGH_TEMP_ID 0x003
#define LOW_PSI_ID 0x004
#define INDICATOR_ID 0x005
#define HEADLIGHTS_ID 0x006
#define TEMP_OK_ID 0x007
#define PSI_OK_ID 0x008
#define PSI_ID 0x009
#define TEMP_ID 0x010
#define TIRES_PING_ID 0x011
#define LIGHTS_PING_ID 0x012
#define ENGINE_PING_ID 0x013

constexpr int potPin = 32;
constexpr int leftIndicatorBtnPin = 13;
constexpr int rightIndicatorBtnPin = 15;
constexpr int headlightsBtnPin = 14;
constexpr int brakesBtnPin = 4;
constexpr int CS_PIN = 5;

class Dashboard
{
public:
    Dashboard(int intPin);

    void ButtonListener();
    void PotentiometerListener();
    void CANListener();
    void SendCANMessageBasedOnButton(int buttonIndex);
    void SendCANMessageBasedOnPot(int rpmValue);

    void HandleHighTempWarning();
    void HandleLowPSIWarning();

    void HandleTempOK();
    void HandlePSIOK();
    void HandlePSI(int PSI);
    void HandleTemp(int temp);

    void StatusCheck();
    void PingLight();
private:
    int intPin;
    LCDScreen *lcd;
};