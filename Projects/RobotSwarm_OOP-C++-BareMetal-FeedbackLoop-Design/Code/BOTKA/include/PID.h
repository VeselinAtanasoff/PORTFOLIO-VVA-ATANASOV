#pragma once
#include "stm32f303xe.h"
#include "Timer.h"
#include "Ultrasonic.h"
#include "UI.h"

constexpr uint32_t setpoint = 10;

class PID
{
    public:
        PID(Timer timer, Ultrasonic ultrasonic, UI ui);
        void PIDController(int32_t *power);
    private:
        Timer timer;
        Ultrasonic ultrasonic;
        UI ui;

        int32_t Error();
};