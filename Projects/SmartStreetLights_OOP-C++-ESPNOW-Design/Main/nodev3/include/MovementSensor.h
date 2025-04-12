#ifndef MOVEMENT_SENSOR_H
#define MOVEMENT_SENSOR_H

#include <Arduino.h>
#include <Ultrasonic.h> // Include the Ultrasonic library
#include <IMovementSensor.h>

class MovementSensor : public IMovementSensor
{
private:
  int trigPin;
  int echoPin;
  Ultrasonic ultrasonic;
  float lastMeasuredDistance;
  bool initialized; // boolean for giving sensor some time at the start to stablize
                    // before providing readings (to avoid fake movement detection)

public:
  // Constructor
  MovementSensor(int trig, int echo);

  // Measure distance using the ultrasonic sensor
  float MeasureDistance();

  // Detect movement based on the measured distance
  bool DetectMovement() override;
};

#endif // MOVEMENT_SENSOR_H
