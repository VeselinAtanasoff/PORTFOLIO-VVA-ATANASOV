#pragma once

#include <Arduino.h>

#define INDICATOR_ID 0x005

class Indicator
{
    public:
        Indicator(int pin);
        void Blink();
        void TurnOff();
        void SwitchOnOff();
    private:
        int pin;
        bool blink;
};

