#pragma once

#include <Arduino.h>

#define HEADLIGHTS_ID 0x006

constexpr int HEADLIGHTS_PIN = 4;

class Headlights
{
    public:
        Headlights();
        void SwitchOnOff();
    private:
        bool isOn;
};