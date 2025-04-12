#ifndef MOTORS_H
#define MOTORS_H

#include "stm32f303xe.h"

// Define constants for motor control
#define NEUTRAL_PWM 1500  // Neutral PWM value
#define ROTATE_PWM_RIGHT  1720  // PWM value for rotating
#define ROTATE_PWM_LEFT  1280  // PWM value for rotating

class Motors {
public:
    // Constructor
    Motors();

    // Public Methods
    void RotateCar();  // Rotate car: 1 = left, 0 = right
    void MoveForward(int power1, int power2);             // Move forward with specified power
    void StopMotors();              // Stop all motors
    int GenerateAngle();   // Generate a random blocking delay

private:
    // Private Member Variables
    int pwmMotor1; // PWM duty cycle for motor 1
    int pwmMotor2; // PWM duty cycle for motor 2

    // Private Methods
    void GPIO_Init();       // Initialize GPIO pins
    void PWM_Out_Init();    // Initialize PWM output
    void ApplyPWM();        // Apply current PWM values to hardware
    void Delay(uint32_t ms); // Delay function for timing
};

#endif // MOTORS_H
