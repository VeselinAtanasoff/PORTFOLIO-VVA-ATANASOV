#include <Arduino.h>
#include "MovementSensor.h"

MovementSensor sensor;

void setup()
{
  Serial.begin(115200);

  // Trig pin = 5, Echo pin = 18, LED pin = 13
  sensor.SetupSensor(5, 18, 13);

  delay(1000);
}

void loop()
{
  // Check for movement
  bool movement = sensor.DetectMovement();
  // Debugging output
  if (movement)
  {
    Serial.println("Movement detected!");
  }
  else
  {
    Serial.println("No movement detected.");
  }

  delay(200);
}
