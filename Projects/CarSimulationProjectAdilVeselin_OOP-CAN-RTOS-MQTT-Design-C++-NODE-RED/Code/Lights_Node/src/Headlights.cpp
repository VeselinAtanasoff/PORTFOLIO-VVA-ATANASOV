#include "Headlights.h"

Headlights::Headlights()
{
    this->isOn = false;
    pinMode(HEADLIGHTS_PIN, OUTPUT);
}

void Headlights::SwitchOnOff()
{
    this->isOn = !this->isOn;
    digitalWrite(HEADLIGHTS_PIN, this->isOn);
    vTaskDelete(nullptr);
}