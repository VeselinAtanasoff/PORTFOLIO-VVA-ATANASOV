#include "Timer.h"
#include "Ultrasonic.h"
#include "UI.h"
#include "PIDValues.h"
#include "Motors.h"
#include "States.h"

// Function to map a value from one range to another
int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

Timer timer;
Ultrasonic ultrasonic;
UI ui;
Motors motors;
States states;

extern "C" void SysTick_Handler(void)
{
    timer.msTicks++;
    // Every 50 ms trigger the ultrasonic sensor
    if (timer.msTicks % 50 == 0)
    {
        ultrasonic.triggerSensor();
    }
}

void PIDToMotor(int32_t power)
{
    //power = power + conversionFactor;
    int32_t power2;
    if (power > ccwMaxPower)
    {
        power = ccwMaxPower;
        
    }else if(power < ccwMinPower){
        power = stopPower;
    }
    power2 = map(power, ccwMinPower, ccwMaxPower, cwMinPower, cwMaxPower);
    if(power2==cwMinPower){
        power = stopPower;
    }
    ui.sendFormattedString("Power 1: %d\r\n", power);
    ui.sendFormattedString("Power 2: %d\r\n", power2);

    motors.MoveForward(power, power2);
}

void PIDController()
{
<<<<<<< HEAD
    static int32_t previousPower = 0;
    int32_t error = 0;
    const float kp = 190.6;
    const float ki = 0.0;
    const float kd = 69.0;
=======
    float error = 0;
    // kp - 150, ki - 0.05, kd - 100 - works fine
    const float kp = 150.0;
    const float ki = 0.05;
    const float kd = 100.0;
>>>>>>> 5bfa0322547821b74c49b1afde0062c7afc4a213
    int32_t integral = 0;
    int32_t previousError = 0;
    int32_t derivative = 0;
    int32_t power = 0;
<<<<<<< HEAD
    int32_t distance = ultrasonic.getFilteredDistance();
    while (distance>setpoint)
    {
        distance = ultrasonic.getFilteredDistance();
        ui.sendFormattedString("Distance: %d cm\r\n", distance);
        error = distance - setpoint;
        ui.sendFormattedString("Error: %d\r\n", error);
=======
    float distance = ultrasonic.getFilteredDistance();
    while (distance>setpoint + tolerance)
    {
        distance = ultrasonic.getFilteredDistance();
        ui.sendFormattedString("Distance: %.2f cm\r\n", distance);
        error = distance - setpoint;
        ui.sendFormattedString("Error: %.2f\r\n", error);
>>>>>>> 5bfa0322547821b74c49b1afde0062c7afc4a213
        integral += error;
        derivative = error - previousError; 
        previousError = error;
        if (error == 0 || error < 0) 
        {
            integral = 0;
        }
        power = error * kp + derivative * kd + integral * ki;
        PIDToMotor(power);
        ui.sendFormattedString("Power PID: %d\r\n", power);
        timer.delay(10);
    }
    states = TURNING;
}

<<<<<<< HEAD
int main()
{
    ui.sendString("System Initialized!\r\n");

    while (true)
    {
        // if(ultrasonic.checkForWall()){
        //     ui.sendString("Wall detected!\r\n");
        // }
        // ui.sendFormattedString("Distance: %d cm\r\n", ultrasonic.getDistance());

        // timer.delay(400);
        PIDController();
        ui.sendString("Here\r\n");

        // uint32_t distance = ultrasonic.getFilteredDistance();
        // ui.sendFormattedString("Distance: %d cm\r\n", distance);
        
        // timer.delay(500);
=======
int main(){
    while (true){    
        switch (states)
        {
        case MOVING:
            PIDController();
            break;
        
        case TURNING:
            motors.StopMotors();
            motors.RotateCar();
            timer.delay(motors.GenerateAngle());
            timer.delay(500); // cigani s me40ve
            states = MOVING;
            break;
        }
>>>>>>> 5bfa0322547821b74c49b1afde0062c7afc4a213
    }
    
}