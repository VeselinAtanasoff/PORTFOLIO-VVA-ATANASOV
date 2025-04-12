#include "Ultrasonic.h"
#include "UI.h"

UI uiUltrasonic;

Ultrasonic::Ultrasonic(){
    distance = 0;
    filteredDistance = 0;
    initGPIO();
    initPWMOutput();
    initPWMInput();
}

void Ultrasonic::initGPIO() {
    // PA10 as trigger output - TIM2 CH4 - AF10
    // PA11 as echo input - TIM4 CH1 - AF10

    // Enable GPIOA clock
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    // Set PA10 to alternate function mode (AF10 for TIM2 CH4)
    GPIOA->MODER &= ~GPIO_MODER_MODER10;  // Clear mode bits for PA10
    GPIOA->MODER |= (0b10 << GPIO_MODER_MODER10_Pos);  // Set alternate function mode for PA10
    // Set PA10 alternate function to AF10 (TIM2_CH4)
    GPIOA->AFR[1] &= ~GPIO_AFRL_AFRL2;  // Clear AFRL bits for PA10
    GPIOA->AFR[1] |= (0b1010 << GPIO_AFRL_AFRL2_Pos);  // Set AF10 for PA10

    // Set PA11 to alternate function mode (AF10 for TIM4 CH1)
    GPIOA->MODER &= ~GPIO_MODER_MODER11;  // Clear mode bits for PA11
    GPIOA->MODER |= (0b10 << GPIO_MODER_MODER11_Pos);  // Set alternate function mode for PA11
    // Set PA11 alternate function to AF10 (TIM4_CH1)
    GPIOA->AFR[1] &= ~GPIO_AFRH_AFRH3_Pos;  // Clear AFRL bits for PA11
    GPIOA->AFR[1] |= (0b1010 << GPIO_AFRH_AFRH3_Pos);  // Set AF10 for PA11
}

void Ultrasonic::initPWMOutput() {
    // Enable clock for TIM2
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // Set prescaler: assuming a clock of 72 MHz, divide by 72 to get a 1 MHz timer clock (1 µs per tick)
    TIM2->PSC = PSCValue ;  // Prescaler value: (72 MHz / 72) = 1 MHz

    // Set auto-reload value
    TIM2->ARR = ARRValue;  // ARR + 1 gives the period (1 MHz / 60000 - 1 = 16.67 Hz)

    // Set PWM mode 1 on channel 4 (PA3 or PA5 for TIM2 CH4 based on pin configuration)
    TIM2->CCMR2 &= ~TIM_CCMR2_OC4M;               // Clear output compare mode bits for channel 4
    TIM2->CCMR2 |= (0b0110 << TIM_CCMR2_OC4M_Pos); // Set PWM mode 1 on channel 4

    // Enable output on channel 4
    TIM2->CCER |= TIM_CCER_CC4E;

    // Enable auto-reload preload
    TIM2->CR1 |= TIM_CR1_ARPE;

    // Enable the timer counter
    TIM2->CR1 |= TIM_CR1_CEN;
}

void Ultrasonic::initPWMInput() {
// Enable APB1ENR
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
    // Prescaler value
    TIM4->PSC = PSCValue; // Prescaler value: (72 MHz / 72 - 1) = 1 MHz

    // Set CC1 channel as input with IC1 mapped on TI1
    TIM4->CCMR1 &= ~TIM_CCMR1_CC1S;
    TIM4->CCMR1 |= (0b01 << TIM_CCMR1_CC1S_Pos);
    // Set CC1NP / CC1P to rising edge - 0
    TIM4->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC1NP);
    // Enable capture on CC1
    TIM4->CCER |= TIM_CCER_CC1E;
    // Set CC2 channel as input with IC2 mapped on TI1
    TIM4->CCMR1 &= ~TIM_CCMR1_CC2S;
    TIM4->CCMR1 |= (0b10 << TIM_CCMR1_CC2S_Pos);
    // Set CC2NP to 0/CC2P to 1 to falling edge
    TIM4->CCER &= ~TIM_CCER_CC2NP;
    TIM4->CCER |= TIM_CCER_CC2P;
    // Enable capture on CC2
    TIM4->CCER |= TIM_CCER_CC2E;
    // Set trigger selection to Filtered Timer Input 1
    TIM4->SMCR &= ~TIM_SMCR_TS;
    TIM4->SMCR |= (0b101 << TIM_SMCR_TS_Pos);
    // Set slave mode selection to Reset Mode
    TIM4->SMCR &= ~TIM_SMCR_SMS;
    TIM4->SMCR |= (0b100 << TIM_SMCR_SMS_Pos);
    // Enable the counter
    TIM4->CR1 |= TIM_CR1_CEN; 
}

float Ultrasonic::getDistance() {
    return TIM4->CCR2 / 58;
}

void Ultrasonic::triggerSensor() {
    TIM2->CCR4 = 10;  // Send a 10 µs pulse
}

bool Ultrasonic::checkForWall() {
    return (getFilteredDistance() != 0 && getFilteredDistance() < 10);
}

float Ultrasonic::getFilteredDistance() {
    distance = getDistance();
    filteredDistance = (alpha * distance) + ((1 - alpha) * filteredDistance);
    return filteredDistance;
}