#include "Timer.h"

Timer::Timer() : msTicks(0) {
    SysTick_Init();
    SystemClock_Config();
}

uint32_t Timer::getMillis() {
    return msTicks;
}

void Timer::delay(uint32_t time_ms) {
    uint32_t start = getMillis();
    while ((getMillis() - start) < time_ms);
}

void Timer::SystemClock_Config(void){
    // Configure Flash latency for 48 < HCLK ≤ 72 MHz, see datasheet. Do this before setting the system clock to 72 MHz.
    FLASH->ACR &= ~FLASH_ACR_LATENCY;
    FLASH->ACR |= FLASH_ACR_LATENCY_2;

    // Enable the HSI (internal high-speed) oscillator
    RCC->CR |= RCC_CR_HSION;
    while (!(RCC->CR & RCC_CR_HSIRDY))
        ; // Wait until HSI is ready

    // Set the APB1 prescaler to 2
    RCC->CFGR &= ~RCC_CFGR_PPRE1;
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;

    // Set the PLL SRC to HSI and PREDIV to /1
    RCC->CFGR &= ~RCC_CFGR_PLLSRC;
    RCC->CFGR |= RCC_CFGR_PLLSRC_HSI_PREDIV;

    // Set PLL multiplier to 9 (8 MHz * 9 = 72 MHz)
    RCC->CFGR &= ~RCC_CFGR_PLLMUL;
    RCC->CFGR |= RCC_CFGR_PLLMUL9;

    // Enable the PLL
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY))
        ; // Wait until PLL is ready

    // Select PLL as system clock source
    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
        ; // Wait until PLL becomes the system clock

    // Update the system core clock variable
    SystemCoreClockUpdate();
}

void Timer::SysTick_Init(void){
    SysTick->CTRL = 0; // Disable SysTick

    // Set the reload value to 72 MHz * 1000 Hz = 72000 - 1
   SysTick->LOAD = reloadValue;

    // Reset the SysTick counter value
    SysTick->VAL = 0;

    // Set the SysTick interrupt priority to the lowest
    NVIC_SetPriority(SysTick_IRQn, (1 << __NVIC_PRIO_BITS) - 1);

    // Enable the clock source
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;

    // Enable the SysTick interrupt
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;

    // Enable SysTick
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}
