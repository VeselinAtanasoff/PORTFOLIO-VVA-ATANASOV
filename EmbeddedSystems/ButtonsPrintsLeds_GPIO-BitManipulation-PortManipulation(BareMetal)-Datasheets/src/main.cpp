#include <Arduino.h>

#define BUTTON_MASK_D10 (1 << PB2)
#define BUTTON_MASK_D11 (1 << PB3)
#define LED_MASK_D5 (1 << PD5)
#define LED_MASK_D6 (1 << PD6)
#define DEBOUNCE_TIME 50

unsigned long lastToggleTime = 0;

void setup()
{
  Serial.begin(9600);
  DDRB &= ~BUTTON_MASK_D10 & ~BUTTON_MASK_D11;
  PORTB |= BUTTON_MASK_D10 | BUTTON_MASK_D11;
  DDRD |= LED_MASK_D5 | LED_MASK_D6;
}

bool debounceButton(uint8_t buttonMask)
{
  if (!(PINB & buttonMask)) {
    delay(DEBOUNCE_TIME);
    if (!(PINB & buttonMask)) {
      return true;
    }
  }
  return false;
}

void loop()
{
  bool buttonD10 = debounceButton(BUTTON_MASK_D10);
  bool buttonD11 = debounceButton(BUTTON_MASK_D11);
  if (buttonD10 && buttonD11) {
    if (millis() - lastToggleTime >= 500) {
      PORTD ^= LED_MASK_D5;
      PORTD ^= LED_MASK_D6;
      lastToggleTime = millis();
    }
  } else if (buttonD10) {
    PORTD |= LED_MASK_D5;
    PORTD &= ~LED_MASK_D6;
  } else if (buttonD11) {
    PORTD &= ~LED_MASK_D5;
    PORTD |= LED_MASK_D6;
    Serial.println("Hello World!");
  } else {
    PORTD &= ~LED_MASK_D5;
    PORTD &= ~LED_MASK_D6;
  }
  delay(20);
}

