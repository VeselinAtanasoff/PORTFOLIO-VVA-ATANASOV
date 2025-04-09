#ifndef TOOLBOX_H
#define TOOLBOX_H

#include "stm32f303xe.h"
#include <stdio.h>
#include <string.h>

#define millisecond 0.001
#define BUFLENGTH 100
#define ReloadValue ((millisecond * SystemCoreClock) - 1)

extern volatile uint32_t millisValue;
extern char sndBuf[BUFLENGTH];
extern char rcvBuf[BUFLENGTH];

extern "C"
{
    void SystemClock_Config(void);
    void SysTick_Init(void);
    void USART2_Init(void);
    void USART2_SendString(char *str);
    char *USART2_ReceiveString(void);
    uint32_t GetMillis(void);
    void Delay(uint32_t time_ms);
}

#endif // TOOLBOX_H
