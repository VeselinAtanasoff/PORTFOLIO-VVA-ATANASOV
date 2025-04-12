#include "Indicator.h"

Indicator::Indicator(int pin)
{
    this->pin = pin;
    pinMode(this->pin, OUTPUT);
    this->blink = false;
}

void Indicator::Blink()
{
    bool ledState = true;
    while (1)
    {
        while (this->blink)
        {
            digitalWrite(this->pin, ledState);
            ledState = !ledState;
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
        TurnOff();
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    vTaskDelete(nullptr);
}

void Indicator::TurnOff()
{
    digitalWrite(this->pin, LOW);
}

void Indicator::SwitchOnOff()
{
    this->blink = !this->blink;
    vTaskDelete(nullptr);
}