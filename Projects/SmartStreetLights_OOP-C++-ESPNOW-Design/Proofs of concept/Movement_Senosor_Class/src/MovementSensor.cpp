#include "MovementSensor.h"

const float SOUND_SPEED = 0.0343;

#define DEBOUNCE_DELAY 200 

// Constructor
MovementSensor::MovementSensor() : trigPin(-1), echoPin(-1), ledPin(-1), lastMovementState(false), lastDebounceTime(0) {}

void MovementSensor::SetupSensor(int trig, int echo, int led)
{
  trigPin = trig;
  echoPin = echo;
  ledPin = led;

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // Initialize PWM for the LED
  ledcSetup(0, 5000, 8);
  ledcAttachPin(ledPin, 0);
}

float MovementSensor::MeasureDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // Timeout after 30ms

  if (duration == 0)
  {
    Serial.println("Timeout: no echo received");
    return -1;
  }

  float distance = (duration * SOUND_SPEED) / 2;
  return distance;
}

bool MovementSensor::DetectMovement()
{
  float distance = MeasureDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  bool currentMovementState = (distance > 0 && distance <= 100);

  // debouncing
  unsigned long currentTime = millis();
  if (currentMovementState != lastMovementState)
  {
    lastDebounceTime = currentTime;  // reset debounce timer if state has changed
  }

  if ((currentTime - lastDebounceTime) > DEBOUNCE_DELAY)
  {
    // update state only if debounce time has passed
    if (currentMovementState != movementState)
    {
      movementState = currentMovementState;

      // Update LED
      if (movementState)
      {
        ledcWrite(0, 255); // Turn LED on
      }
      else
      {
        ledcWrite(0, 0); // Turn LED off
      }
    }
  }

  lastMovementState = currentMovementState;
  return movementState;
}
