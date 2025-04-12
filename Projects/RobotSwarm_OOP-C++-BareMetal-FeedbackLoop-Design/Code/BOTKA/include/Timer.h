#pragma once
#include "stm32f303xe.h"

#define reloadValue 72000

class Timer {
public:
    Timer();
    uint32_t getMillis();
    void delay(uint32_t time_ms);
    volatile uint32_t msTicks;

private:
    void SystemClock_Config(void);
    void SysTick_Init(void);
};

extern "C" void SysTick_Handler(void);

