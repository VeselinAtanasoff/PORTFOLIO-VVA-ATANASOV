////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The example code below is created in VSCode with PlatformIO for the NUCLEO-F303RE board, using the CMSIS framework.
// For this code to work, create a new PlatformIO CMSIS project for the STM32 NUCLEO F303RE board and select the
// CMSIS framework as this will install the required libraries / header files.
// It is the minimal code for:
// - Toggling the onboard LED.
// - Set the system clock to 72 MHz.
// - Sending the "Hello, World!" message through USART2.
// To be able to call STM32 HAL functions like HAL_Delay() one has to do the following:
// - When creating the project, select the STM32Cube framework i.s.o. the CMSIS framework. This will install the HAL libraries.
// - Add #include "stm32f3xx_hal.h".
// - Initialize the System timer SysTick and add the 'extern "C" void SysTick_Handler(void)'.
// - In the SysTick handler, call HAL_IncTick().
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "stm32f303xe.h"
#include <stdio.h>
#include <string.h>
#define ReloadValue ((0.001*SystemCoreClock)-1) // This is the reload value for 1ms ticks with a 72MHz clock calculated
// using the formula: ReloadValue = (DesiredTick * ClockFrequency) - 1

volatile uint32_t millisValue; // counts 1ms ticks

void SystemClock_Config(void);
void GPIOx_Init(void);
uint32_t GetMillis(void);
void Delay(uint32_t time_ms);

extern "C" void SysTick_Handler(void)
{
    GPIOA -> ODR^= GPIO_ODR_8;
    millisValue++;
}

int main(void)
{
    SystemClock_Config();
    GPIOx_Init();
    SysTick->CTRL = 0;           // Disable SysTick
    SysTick->LOAD = ReloadValue; // Set reload register to 71999 which will trigger an interrupt event every 1ms
    SysTick->VAL = 0;            // Reset the SysTick counter value

    NVIC_SetPriority(SysTick_IRQn, (1 << __NVIC_PRIO_BITS) - 1); // Set the SysTick interrupt priority
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;                 // Select the system clock(the Cortex impulse generator) as the source
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;                   // Enable SysTick interrupt
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;                    // Enable SysTick

    uint32_t previousMillis = 0;

    while (1)
    {
        if (GPIOC->IDR & GPIO_IDR_13)
        {
            uint32_t currentMillis = GetMillis();

            if (currentMillis - previousMillis >= 500)
            {

                GPIOA->ODR ^= GPIO_ODR_5;
                previousMillis = currentMillis;
            }
        }
        else
        {
            GPIOA->ODR ^= GPIO_ODR_5;
            Delay(1000);
        }
    }
}

void SystemClock_Config(void)
{
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

void GPIOx_Init(void)
{
    // Enable GPIOA clock
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    // Set pin PA5 as output
    GPIOA->MODER &= ~GPIO_MODER_MODER5;            // Reset bits
    GPIOA->MODER |= 0b01 << GPIO_MODER_MODER5_Pos; // Set bits for output mode
    GPIOA->MODER &= ~GPIO_MODER_MODER8;
    GPIOA->MODER |= 0b01 << GPIO_MODER_MODER8_Pos;

    // Enable GPIOC clock by setting pin 19 of the RCC_AHBENR register
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    // Set pin PC13 as input
    GPIOC->MODER &= ~GPIO_MODER_MODER13;            // Reset bits and set PC13 as input by enabling the schmitt trigger circuit
    GPIOC->PUPDR |= 0b01 << GPIO_PUPDR_PUPDR13_Pos; // Enable the pull-up resistor

}

uint32_t GetMillis(void)
{
    return millisValue;
}

void Delay(uint32_t time_ms)
{
    uint32_t currentMillis = millisValue;
    while ((millisValue - currentMillis) < time_ms)
        ;
}
