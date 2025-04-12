#include "Motors.h"
#include "Timer.h"
#include <cstdlib>
#include <ctime>

// Constructor
Motors::Motors() : pwmMotor1(NEUTRAL_PWM), pwmMotor2(NEUTRAL_PWM) {
    GPIO_Init();
    PWM_Out_Init();
}

// Public Methods
void Motors::RotateCar(){
    int direction = rand() % 2; // Generate a random direction
    if (direction == 1) { // Rotate left
        pwmMotor1 = ROTATE_PWM_LEFT; // Set PWM for motor 1
        pwmMotor2 = ROTATE_PWM_LEFT; // Stop motor 2
    } else if (direction == 0) { // Rotate right
        pwmMotor1 = ROTATE_PWM_RIGHT; // Stop motor 1
        pwmMotor2 = ROTATE_PWM_RIGHT; // Set PWM for motor 2
    }
    ApplyPWM(); // Apply the PWM values to the hardware
    GenerateAngle(); // Generate a random blocking delay for turning motors
}

void Motors::MoveForward(int power1, int power2) {
    pwmMotor1 = power1; // Set power for motor 1
    pwmMotor2 = power2; // Set power for motor 2
    ApplyPWM(); // Apply the PWM values to the hardware
}

void Motors::StopMotors() {
    pwmMotor1 = NEUTRAL_PWM;
    pwmMotor2 = NEUTRAL_PWM;
    ApplyPWM();
}

int Motors::GenerateAngle() {
    int angle = rand() % (1500 - 500 + 1) + 500;
    return angle;
}

// Private Methods
void Motors::GPIO_Init() {
    // Enable GPIOB clock
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

    // Configure PB4 for TIM3_CH1 (Servo 1)
    GPIOB->MODER &= ~GPIO_MODER_MODER4;
    GPIOB->MODER |= (0b10 << GPIO_MODER_MODER4_Pos);

    GPIOB->AFR[0] &= ~GPIO_AFRL_AFRL4;
    GPIOB->AFR[0] |= (0b0010 << GPIO_AFRL_AFRL4_Pos);

    // Configure PB5 for TIM3_CH2 (Servo 2)
    GPIOB->MODER &= ~GPIO_MODER_MODER5;
    GPIOB->MODER |= (0b10 << GPIO_MODER_MODER5_Pos);

    GPIOB->AFR[0] &= ~GPIO_AFRL_AFRL5;
    GPIOB->AFR[0] |= (0b0010 << GPIO_AFRL_AFRL5_Pos);
}

void Motors::PWM_Out_Init() {
    // Enable clock for TIM3
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    // Set prescaler: (72 MHz / 720) = 100 kHz timer clock
    TIM3->PSC = 71;

    // Set auto-reload value: (100 kHz / 50 Hz) - 1 = 1999
    TIM3->ARR = 19999; // ARR + 1 = 2000

    // Configure TIM3_CH1 (Servo 1) as PWM mode 1
    TIM3->CCMR1 &= ~TIM_CCMR1_OC1M;
    TIM3->CCMR1 |= (0b110 << TIM_CCMR1_OC1M_Pos);

    TIM3->CCMR1 |= TIM_CCMR1_OC1PE; // Enable preload for CH1
    TIM3->CCER |= TIM_CCER_CC1E;    // Enable output for CH1

    // Configure TIM3_CH2 (Servo 2) as PWM mode 1
    TIM3->CCMR1 &= ~TIM_CCMR1_OC2M;
    TIM3->CCMR1 |= (0b110 << TIM_CCMR1_OC2M_Pos);

    TIM3->CCMR1 |= TIM_CCMR1_OC2PE; // Enable preload for CH2
    TIM3->CCER |= TIM_CCER_CC2E;    // Enable output for CH2

    // Enable counter
    TIM3->CR1 |= TIM_CR1_CEN;
}

void Motors::ApplyPWM() {
    TIM3->CCR1 = pwmMotor1; // Apply PWM value to motor 1
    TIM3->CCR2 = pwmMotor2; // Apply PWM value to motor 2
}
