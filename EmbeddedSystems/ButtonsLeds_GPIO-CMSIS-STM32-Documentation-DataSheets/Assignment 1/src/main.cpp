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

void SystemClock_Config(void);
void GPIOx_Init(void);
void USART2_Init(void);
void USART2_SendString(char *str);
char *USART2_ReceiveString(void);
void Delay(uint32_t time_ms);

const int BUFLENGTH = 100;

char sndBuf[BUFLENGTH];
char rcvBuf[BUFLENGTH];

enum States
{
    TOGGLE,
    BLINK
};

States toggleState(bool buttonState, bool lastButtonState, enum States state);
States blinkState(bool buttonState, bool lastButtonState, enum States state);

int main(void)
{
    // Configure the system clock
    SystemClock_Config();
    GPIOx_Init();//Function updated to include PC13 as input

    bool buttonState;
    bool lastButtonState = false;
    States state = TOGGLE;

    while (1)
    {
        // Read the state of the button which is connected to pin PC13
        buttonState = GPIOC->IDR & GPIO_IDR_13;//use macros

        switch (state)
        {
        case TOGGLE:
            state = toggleState(buttonState, lastButtonState, state);
            break;
        case BLINK:
            state = blinkState(buttonState, lastButtonState, state);
            break;
        default:
            break;
        }

        lastButtonState = buttonState;
    }
}

States toggleState(bool buttonState, bool lastButtonState, enum States state)
{
    if (buttonState == false && lastButtonState == true)
    {
        GPIOA->ODR ^= GPIO_ODR_5;
        return TOGGLE;
    }
    else if (buttonState == false && lastButtonState == false)
    {
        return BLINK;
    }

    return TOGGLE;
}

States blinkState(bool buttonState, bool lastButtonState, enum States state)
{
    if (buttonState == false && lastButtonState == true)
    {
        return TOGGLE;
    }
    else if (buttonState == false && lastButtonState == false)
    {
        GPIOA->ODR ^= GPIO_ODR_5;
        Delay(1000);
        return BLINK;
    }

    return BLINK;
}

// Configure the system clock to 72 MHz. This means the APB1 peripheral clock and also the USART2 will be clocked at 36 MHz.
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

    // Enable GPIOC clock by setting pin 19 of the RCC_AHBENR register
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    // Set pin PC13 as input
    GPIOC->MODER &= ~GPIO_MODER_MODER13; // Reset bits and set PC13 as input by enabling the schmitt trigger circuit
}

// Initialize USART2
void USART2_Init(void)
{
    // Enable USART2 clock
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    // Set GPIO pin PA2 to alternate function.
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODER2) | (0b10 << GPIO_MODER_MODER2_Pos);
    // Select alternate function AF7 (USART2_TX) for GPIO pin PA2.
    GPIOA->AFR[0] = (GPIOA->AFR[0] & ~GPIO_AFRL_AFRL2) | (0b0111 << GPIO_AFRL_AFRL2_Pos);
    // Set GPIO pin PA3 to alternate function.
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODER3) | (0b10 << GPIO_MODER_MODER3_Pos);
    // Select alternate function AF7 (USART2_RX) for GPIO pin PA3.
    GPIOA->AFR[0] = (GPIOA->AFR[0] & ~GPIO_AFRL_AFRL3) | (0b0111 << GPIO_AFRL_AFRL3_Pos);

    // Configure USART2
    USART2->BRR = 36000000 / 9600; // Assuming 36 MHz clock, 9600 baud rate.
    USART2->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}

// Send a string through USART2.
void USART2_SendString(char *str)
{
    while (*str)
    {
        // Wait until transmit data register is empty.
        while (!(USART2->ISR & USART_ISR_TXE))
            ;
        USART2->TDR = *str++;
    }
}

// Receive a string through USART2
// This function blocks until a newline '\n' character is received.
char *USART2_ReceiveString(void)
{
    static int i = 0;
    char c = 0;
    USART2->ICR |= USART_ICR_ORECF; // Clear overrun error flag.
    while (i == 0 || c != '\0')
    {
        if (USART2->ISR & USART_ISR_RXNE)
        {

            c = USART2->RDR;
            if (c == '\n') // Return received, so string is complete.
            {
                c = '\0'; // Indicate end of string.
                rcvBuf[i++] = c;
            }
            else
            {
                if (i < BUFLENGTH - 1) // Prevent buffer overflow
                {
                    rcvBuf[i++] = c;
                }
            }
        }
    }
    i = 0; // Prepare for next string.
    return rcvBuf;
}

// Simple delay function, should not be used in serious applications.
void Delay(uint32_t time_ms)
{
    volatile uint32_t i, j;

    for (i = 0; i < time_ms; i++)
        for (j = 0; j < 2000; j++)
            ; // Adjust this loop for shorter or longer delays
}
