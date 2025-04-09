#include "stm32f303xe.h"
#include <stdio.h>
#include <string.h>
#include "toolbox.h"

void GPIOx_Init(void);
void TIM2_PWM_Input_Init(void); 
void TIM3_PWM_Input_Init(void);
int GetAngle(void);

int main(void)
{
    SystemClock_Config();
    USART2_Init();
    SysTick_Init();
    TIM2_PWM_Input_Init();
    TIM3_PWM_Input_Init();
    GPIOx_Init();
    

    uint32_t previousMillis = 0;
    int distance = 0;
    int angle = 0;
    char sndBuf[BUFLENGTH];

    while (1)
    {
        uint32_t currentMillis = GetMillis();
        if(currentMillis - previousMillis >= 20)
        {
            GPIOA->ODR ^= GPIO_ODR_4;
            previousMillis = currentMillis;
        }
        distance = TIM2->CCR2/58;
        angle = GetAngle();
        sprintf(sndBuf, "Servo angle position: %d\n", angle);
        USART2_SendString(sndBuf);
        sprintf(sndBuf, "Distance: %d cm\n", distance);
        USART2_SendString(sndBuf);
        Delay(2000);
    }
}

void GPIOx_Init(void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    // Set PA0 as alternate function (AF1 for TIM2 CH1)
    GPIOA->MODER &= ~(GPIO_MODER_MODER0); // Clear mode bits for PA0
    GPIOA->MODER |= GPIO_MODER_MODER0_1;  // Set alternate function mode for PA0
    GPIOA->AFR[0] &= ~(GPIO_AFRL_AFRL0);  // Clear alternate function bits
    GPIOA->AFR[0] |= (1 << GPIO_AFRL_AFRL0_Pos); // Set AF1 for TIM2 CH1 on PA0

    // Set PB4 as alternate function (AF2 for TIM3 CH1)
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    GPIOB->MODER &= ~(GPIO_MODER_MODER4); // Clear mode bits for PB4
    GPIOB->MODER |= GPIO_MODER_MODER4_1;  // Set alternate function mode for PB4
    GPIOB->AFR[0] &= ~(GPIO_AFRL_AFRL4);  // Clear alternate function bits
    GPIOB->AFR[0] |= (2 << GPIO_AFRL_AFRL4_Pos); // Set AF2 for TIM3 CH1 on PB4

    // Set PA4 as output
    GPIOA->MODER &= ~(GPIO_MODER_MODER4); // Clear mode bits for PA1
    GPIOA->MODER |= GPIO_MODER_MODER4_0;  // Set output mode for PA1
}

void TIM2_PWM_Input_Init(void)
{
    // Enable TIM2 clock
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // Prescaler needs to be 72-1 to get 1 MHz timer clock.
    TIM2->PSC = 71;

    TIM2->CCMR1 &= ~TIM_CCMR1_CC1S; // Clear CC1S bits
    TIM2->CCMR1 |= TIM_CCMR1_CC1S_0; // CC1 channel is set to input

    //Set CC1 to capture on rising edge (non-inverted)
    TIM2->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC1NP); // Clear CC1P and CC1NP for rising edge

    //Enable Capture/Compare 1 capture
    TIM2->CCER |= TIM_CCER_CC1E; // Enable capture on CC1

    //Configure CC2 as input, map IC2 to TI1
    TIM2->CCMR1 &= ~TIM_CCMR1_CC2S; // Clear CC2S bits
    TIM2->CCMR1 |= TIM_CCMR1_CC2S_1; // CC2 channel is set to input, IC2 is mapped to TI1

    //Set CC2 to capture on falling edge (inverted)
    TIM2->CCER &= ~TIM_CCER_CC2NP; // Clear CC2NP (no inversion)
    TIM2->CCER |= TIM_CCER_CC2P;   // Set CC2P for falling edge

    // Enable Capture/Compare 2 capture
    TIM2->CCER |= TIM_CCER_CC2E; // Enable capture on CC2

    // Set Trigger selection to Filtered Timer Input 1
    TIM2->SMCR &= ~TIM_SMCR_TS; // Clear TS bits
    TIM2->SMCR |= TIM_SMCR_TS_2 | TIM_SMCR_TS_0; // Set TS bits to '101' (Filtered Timer Input 1)

    // Set Slave mode selection to Reset Mode
    TIM2->SMCR &= ~TIM_SMCR_SMS; // Clear SMS bits
    TIM2->SMCR |= TIM_SMCR_SMS_2; // Set SMS bits to '100' (Reset Mode)

    // Enable the counter
    TIM2->CR1 |= TIM_CR1_CEN;
}

void TIM3_PWM_Input_Init(void)
{
    // Enable TIM3 clock
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    // Prescaler needs to be 72-1 to get 1 MHz timer clock.
    TIM3->PSC = 71;

    TIM3->CCMR1 &= ~TIM_CCMR1_CC1S; // Clear CC1S bits
    TIM3->CCMR1 |= TIM_CCMR1_CC1S_0; // CC1 channel is set to input

    //Set CC1 to capture on rising edge (non-inverted)
    TIM3->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC1NP); // Clear CC1P and CC1NP for rising edge

    //Enable Capture/Compare 1 capture
    TIM3->CCER |= TIM_CCER_CC1E; // Enable capture on CC1

    //Configure CC2 as input, map IC2 to TI1
    TIM3->CCMR1 &= ~TIM_CCMR1_CC2S; // Clear CC2S bits
    TIM3->CCMR1 |= TIM_CCMR1_CC2S_1; // CC2 channel is set to input, IC2 is mapped to TI1

    //Set CC2 to capture on falling edge (inverted)
    TIM3->CCER &= ~TIM_CCER_CC2NP; // Clear CC2NP (no inversion)
    TIM3->CCER |= TIM_CCER_CC2P;   // Set CC2P for falling edge

    // Enable Capture/Compare 2 capture
    TIM3->CCER |= TIM_CCER_CC2E; // Enable capture on CC2

    // Set Trigger selection to Filtered Timer Input 1
    TIM3->SMCR &= ~TIM_SMCR_TS; // Clear TS bits
    TIM3->SMCR |= TIM_SMCR_TS_2 | TIM_SMCR_TS_0; // Set TS bits to '101' (Filtered Timer Input 1)

    // Set Slave mode selection to Reset Mode
    TIM3->SMCR &= ~TIM_SMCR_SMS; // Clear SMS bits
    TIM3->SMCR |= TIM_SMCR_SMS_2; // Set SMS bits to '100' (Reset Mode)

    // Enable the counter
    TIM3->CR1 |= TIM_CR1_CEN;
}

int GetAngle(void)
{
    float dutyCycleMin = 2.9;
    float dutyCycleMax = 91.7;
    int unitsFullCircle = 360;

    // Calculate duty cycle based on TIM3 feedback values
    float dutyCycle = (100.0 * TIM3->CCR2) / 1100;  // 1100 us is the full period (approx. 1/910 Hz)
    
    // Calculate the angle
    int angle = ((dutyCycle - dutyCycleMin) * unitsFullCircle) / (dutyCycleMax - dutyCycleMin + 1);

    return angle;
}