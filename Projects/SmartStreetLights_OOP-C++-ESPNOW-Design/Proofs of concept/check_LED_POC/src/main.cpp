#include <Arduino.h>

const int ledPin = 2;  
const int readPin = 34; 
int value = 0;

// Custom analogWrite function for ESP32
void analogWrite(uint8_t pin, uint32_t dutyCycle) {
  const int pwmChannel = 0; // Use channel 0 for this pin
  const int pwmFrequency = 5000; // Frequency in Hz
  const int pwmResolution = 8; // 8-bit resolution (0-255)

  // Configure the PWM channel
  ledcSetup(pwmChannel, pwmFrequency, pwmResolution);
  // Attach the PWM channel to the specified pin
  ledcAttachPin(pin, pwmChannel);
  // Write the duty cycle
  ledcWrite(pwmChannel, dutyCycle);
}

void setup() {
  Serial.begin(9600);
  pinMode(readPin, INPUT); 
}

void loop() {
  int percent = 0;
  map(percent, 0, 100, 0, 255);
  // 100% duty cycle (max brightness)
  analogWrite(ledPin, 255);
  value = analogRead(readPin);
  Serial.print("100%: ");
  Serial.println(value);
  delay(1000);

  // 75% duty cycle
  analogWrite(ledPin, 191);
  value = analogRead(readPin);
  Serial.print("75%: ");
  Serial.println(value);
  delay(1000);

  // 50% duty cycle
  analogWrite(ledPin, 128);
  value = analogRead(readPin);
  Serial.print("50%: ");
  Serial.println(value);
  delay(1000);

  // 25% duty cycle
  analogWrite(ledPin, 64);
  value = analogRead(readPin);
  Serial.print("25%: ");
  Serial.println(value);
  delay(1000);

  // 10% duty cycle
  analogWrite(ledPin, 26);
  value = analogRead(readPin);
  Serial.print("10%: ");
  Serial.println(value);
  delay(1000);

  // 0% duty cycle (off)
  analogWrite(ledPin, 0);
  value = analogRead(readPin);
  Serial.print("0%: ");
  Serial.println(value);
  delay(1000);
}

