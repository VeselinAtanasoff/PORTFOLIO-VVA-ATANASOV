#include "ldr.h"
#include <Arduino.h>

Ldr::Ldr(uint8_t pin)
{
  pinMode(pin, INPUT);
  this->pin = pin;
}

int Ldr::ReadLightLevel()
{
  int ldrValue = analogRead(pin);
  ldrValue = map(ldrValue, 0, MAXLDR, 0, 100);
  return ldrValue;
}