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

void GPIOx_Init(void);

extern "C" void EXTI9_5_IRQHandler(void)
{
    // Reset interrupt flag
    EXTI->PR = EXTI_PR_PR8;

    // Toggle the LED
    GPIOA->ODR ^= GPIO_ODR_10;
}

extern "C" void EXTI15_10_IRQHandler(void)
{
    // Reset interrupt flag
    EXTI->PR = EXTI_PR_PR13;

    // Toggle the LED
    GPIOA->ODR ^= GPIO_ODR_5;
}

int main(void)
{
    GPIOx_Init();                         // Function updated to include PC13 as input
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; // Enable the system configuration controller clock

    SYSCFG->EXTICR[2] &= ~SYSCFG_EXTICR3_EXTI8_PA; // Select port A pin 8
    SYSCFG->EXTICR[2] |= SYSCFG_EXTICR3_EXTI8_PA;
    EXTI->FTSR |= EXTI_FTSR_TR8;  // Set falling edge trigger
    EXTI->IMR |= EXTI_IMR_MR8;    // Enable interrupt request from line 8
    NVIC_EnableIRQ(EXTI9_5_IRQn); // Enable EXTI4 interrupt

    SYSCFG->EXTICR[3] &= ~SYSCFG_EXTICR4_EXTI13_PC; // Select port C pin 13
    SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;
    EXTI->FTSR |= EXTI_FTSR_TR13;   // Set falling edge trigger
    EXTI->RTSR |= EXTI_RTSR_TR13;   // Set rising edge trigger
    EXTI->IMR |= EXTI_IMR_MR13;     // Enable interrupt request from line 13
    NVIC_EnableIRQ(EXTI15_10_IRQn); // Enable EXTI15_10 interrupt

    while (1)
    {
    }
}

void GPIOx_Init(void)
{
    // Enable GPIOA clock
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    // Set pin PA5 as output
    GPIOA->MODER &= ~GPIO_MODER_MODER5;            // Reset bits
    GPIOA->MODER |= 0b01 << GPIO_MODER_MODER5_Pos; // Set bits for output mode

    // Enable GPIOC clock by setting pin 19 of the RCC_AHBENR register
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    // Set pin PC13 as input
    GPIOC->MODER &= ~GPIO_MODER_MODER13;            // Reset bits and set PC13 as input by enabling the schmitt trigger circuit
    GPIOC->PUPDR |= 0b01 << GPIO_PUPDR_PUPDR13_Pos; // Enable the pull-up resistor
    // Set pin PA10(D2) as output
    GPIOA->MODER &= ~GPIO_MODER_MODER10; // Reset bits
    GPIOA->MODER |= 0b01 << GPIO_MODER_MODER10_Pos;
    // Set pin PA8(D7) as input and enable the pull-up resistor
    GPIOA->MODER &= ~GPIO_MODER_MODER8; // Reset bits
    GPIOA->PUPDR |= 0b01 << GPIO_PUPDR_PUPDR8_Pos;
}
