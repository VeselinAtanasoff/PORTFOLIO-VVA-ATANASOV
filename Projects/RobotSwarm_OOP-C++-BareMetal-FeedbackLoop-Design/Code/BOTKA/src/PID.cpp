#include "PID.h"    

PID::PID(Timer timer, Ultrasonic ultrasonic, UI ui)
{
    this->timer = timer;
    this->ultrasonic = ultrasonic;
    this->ui = ui;
    ui.sendString("PID Controller Initialized!\r\n");
}

int32_t PID::Error()
{
    uint32_t actual = ultrasonic.getFilteredDistance();
    return setpoint - actual;
}

void PID::PIDController(int32_t *power)
{
    int32_t error = 0;
    const float kp = 1;
    const float ki = 1;
    const float kd = 1;
    uint32_t integral = 0;
    uint32_t previousError = 0;
    uint32_t derivative = 0;
    while (1)//This condition will be changed depending on the application
    {
        ui.sendString("PID Controller Running!\r\n");
        error = Error();

        integral += error;
        derivative = error - previousError;//Calculating the derivative
        previousError = error;
        if (error == 0 || error < 0)//Reset the integral where no power is needed to maintain position
        {
            integral = 0;
        }
        *power = -1*(error * kp + integral * ki + derivative * kd);
        ui.sendFormattedString("Power: %f\r\n", power);
        timer.delay(20);
    }
}