#include "stm32f303xe.h"

#define millisecond 0.001

void SystemClock_Config(void);
void TIM2_PWM_Init(void);
void TIM3_PWM_Init(void);
void GPIO_Init(void);
void PWM_SetDutyCycle(uint8_t duty_cycle);
void Servo_Adjust(uint32_t angle);
void Delay(uint32_t time_ms);

int main(void)
{

    // Configure the system clock
    SystemClock_Config();
    // Initialize GPIO for PA1 (TIM2 Channel 2) and PA6 (TIM3 Channel 1)
    GPIO_Init();

    // Initialize TIM2 for PWM output on Channel 2 (PA1)
    TIM2_PWM_Init();

    // Initialize TIM3 for PWM output on Channel 1 (PA6)
    TIM3_PWM_Init();

    uint8_t servo_value = 0;

    Servo_Adjust(servo_value);
    Delay(1000);

    int8_t duty_cycle = 0;

    uint8_t step = 1;

    while (1)
    {

        for (duty_cycle = 0; duty_cycle <= 100; duty_cycle += step)
        {
            PWM_SetDutyCycle(duty_cycle); // Set duty cycle
            Delay(10);                    // Delay for 10 ms (control the speed of change)
        }

        for (duty_cycle = 100; duty_cycle > -1; duty_cycle -= step)
        {
            PWM_SetDutyCycle(duty_cycle); // Set duty cycle
            Delay(10);                    // Delay for 10 ms (control the speed of change)
        }

        for (servo_value = 0; servo_value <= 90; servo_value += step)
        {
            Servo_Adjust(servo_value);
            Delay(30);
        }
        Delay(1000);
        for (servo_value = 90; servo_value <= 180; servo_value += step)
        {
            Servo_Adjust(servo_value);
            Delay(30);
        }
        Delay(1000);
        for (servo_value = 180; servo_value >= 90; servo_value -= step)
        {
            Servo_Adjust(servo_value);
            Delay(30);
        }
        Delay(1000);
        for (servo_value = 90; servo_value > 0; servo_value -= step)
        {
            Servo_Adjust(servo_value);
            Delay(30);
        }
        Delay(1000);
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

// GPIO Initialization for PA1 as Alternate Function for TIM2 CH2
void GPIO_Init(void)
{
    // Enable clock for GPIOA
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    // Set PA1 as Alternate Function (AF1 for TIM2 CH2)

    // Clear the mode bits for PA1 and set it to Alternate Function (MODER1[1:0] = 10)
    GPIOA->MODER &= ~GPIO_MODER_MODER1;  // Clear mode bits (reset to 00)
    GPIOA->MODER |= GPIO_MODER_MODER1_1; // Set mode to 10 (Alternate Function)

    // Set PA1 Alternate Function to AF1 (TIM2_CH2)
    GPIOA->AFR[0] &= ~GPIO_AFRL_AFRL1_Msk;       // Clear AF bits (reset to 0000)
    GPIOA->AFR[0] |= (1 << GPIO_AFRL_AFRL1_Pos); // Set AF1 (AF1 is 0001, so we set AFRL[3:0] for PA1)

    // Set PA6 as Alternate Function (AF2 for TIM3 CH1)
    GPIOA->MODER &= ~GPIO_MODER_MODER6;  // Clear mode bits (reset to 00)
    GPIOA->MODER |= GPIO_MODER_MODER6_1; // Set mode to 10 (Alternate Function)

    // Set PA6 Alternate Function to AF2 (TIM3_CH1)
    GPIOA->AFR[0] &= ~GPIO_AFRL_AFRL6_Msk;            // Clear AF bits (reset to 0000)
    GPIOA->AFR[0] |= (0b0010 << GPIO_AFRL_AFRL6_Pos); // Set AF2 (AF2 is 0010, so we set AFRL[7:4] for PA6)
}

// Timer 2 PWM Initialization (Channel 2)
void TIM2_PWM_Init(void)
{
    // Enable clock for TIM2
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // Compute the prescaler and the auto-reload value
    uint32_t prescaler = 1;                          // Prescaler for 1ms period (1000Hz)
    uint32_t period = (0.001 * SystemCoreClock) - 1; // 1ms period for PWM frequency of 72Mhz

    // Set prescaler
    TIM2->PSC = prescaler;

    // Set auto-reload (period)
    TIM2->ARR = period;

    // Set PWM mode on Channel 2 (PA1)
    TIM2->CCMR1 &= ~(TIM_CCMR1_OC2M);              // Clear output compare mode for channel 2
    TIM2->CCMR1 |= (0b0110 << TIM_CCMR1_OC2M_Pos); // PWM mode 1 (OC2M = 110)

    // Enable preload on channel 2
    TIM2->CCMR1 |= TIM_CCMR1_OC2PE;

    // Enable output compare on Channel 2
    TIM2->CCER |= TIM_CCER_CC2E;

    // Enable auto-reload preload
    TIM2->CR1 |= TIM_CR1_ARPE;

    // Enable the counter
    TIM2->CR1 |= TIM_CR1_CEN;
}

// Timer 3 PWM Initialization (Channel 1)
void TIM3_PWM_Init(void)
{
    // Enable clock for TIM3
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    // Compute the prescaler and the auto-reload value
    // output of timer= (clock frequency)/(prescaler+1)*(auto-reload+1)
    // 50Hz=(72Mhz)/(719+1)*(auto-reload+1)
    uint32_t prescaler = 719;    // Prescaler for 1ms period (1000Hz)
    uint32_t auto_reload = 1999; // Auto-reload value for 50Hz PWM frequency

    // Set the prescaler value
    TIM3->PSC = prescaler;

    // Set the auto-reload value
    TIM3->ARR = auto_reload;

    // Set the PWM mode 1 for Channel 1
    TIM3->CCMR1 &= ~TIM_CCMR1_OC1M;                     // Clear OC1M bits
    TIM3->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; // Set PWM mode 1

    // Enable the output compare preload for channel 1
    TIM3->CCMR1 |= TIM_CCMR1_OC1PE;

    // Enable the output compare mode for channel 1
    TIM3->CCER |= TIM_CCER_CC1E;

    // Enable the counter
    TIM3->CR1 |= TIM_CR1_CEN;
}

// Function to set the duty cycle (0-100%)
void PWM_SetDutyCycle(uint8_t duty_cycle)
{
    if (duty_cycle > 100)
        duty_cycle = 100; // Limit to 100%
    if (duty_cycle < 0)
        duty_cycle = 0; // Limit to 0%

    if (duty_cycle == 0)
    {
        TIM2->CCR2 = 0;
    }
    else
    {
        uint32_t compare_value = (TIM2->ARR + 1) * duty_cycle / 100;
        TIM2->CCR2 = compare_value; // Set compare value for Channel 2
    }
}

// Function to adjust the servo angle
void Servo_Adjust(uint32_t angle)
{
    uint32_t compare_value = (angle * 1.07) + 55 + (angle * 0.05);
    TIM3->CCR1 = compare_value;
}

void Delay(uint32_t time_ms)
{
    volatile uint32_t i, j;

    for (i = 0; i < time_ms; i++)
        for (j = 0; j < 2000; j++)
            ; // Adjust this loop for shorter or longer delays
}
