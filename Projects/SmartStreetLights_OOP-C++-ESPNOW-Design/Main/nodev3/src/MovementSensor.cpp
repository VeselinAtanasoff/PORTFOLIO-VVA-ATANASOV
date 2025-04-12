#include "MovementSensor.h"

MovementSensor::MovementSensor(int trig, int echo)
    : trigPin(trig), echoPin(echo), ultrasonic(trigPin, echoPin), lastMeasuredDistance(0.0f), initialized(false) {}

float MovementSensor::MeasureDistance()
{
    float distance = ultrasonic.read(CM);

    if (distance < 0)
    {
        return lastMeasuredDistance;
    }
    return distance;
}

bool MovementSensor::DetectMovement()
{
    float currentDistance = MeasureDistance();

    if (!initialized)
    {
        static unsigned long lastInitTime = 0;
        if (millis() - lastInitTime > 2000)
        {
            initialized = true;
            lastMeasuredDistance = currentDistance;
        }
        return false;
    }

    const float movementThreshold = 3.5;

    if (fabs(currentDistance - lastMeasuredDistance) > movementThreshold)
    {
        lastMeasuredDistance = currentDistance;

        return true;
    }

    lastMeasuredDistance = currentDistance;

    return false; //
}