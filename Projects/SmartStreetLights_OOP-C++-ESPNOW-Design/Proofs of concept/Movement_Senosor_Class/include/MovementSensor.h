#ifndef MOVEMENT_SENSOR_H
#define MOVEMENT_SENSOR_H

#include <Arduino.h>

class MovementSensor
{
private:
  int trigPin;
  int echoPin;
  int ledPin;

  bool movementState;             // current movement state (true = detected, false = not detected)
  bool lastMovementState;         // last measured movement state
  unsigned long lastDebounceTime; // time when movement state last changed

public:
  // Constructor
  MovementSensor();

  void SetupSensor(int trig, int echo, int led);

  float MeasureDistance();

  bool DetectMovement();
};

#endif // MOVEMENT_SENSOR_H
