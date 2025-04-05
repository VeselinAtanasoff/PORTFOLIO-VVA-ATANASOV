#include <Arduino.h>

// Debounce parameters
#define DEBOUNCE_TIME 0.3
#define SAMPLE_FREQUENCY 10
#define MAXIMUM (DEBOUNCE_TIME * SAMPLE_FREQUENCY)

// Button and LED pin masks
#define BUTTON_MASK_D10 (1 << PB2)
#define BUTTON_MASK_D11 (1 << PB3)
#define LED_MASK_D5 (1 << PD5)
#define LED_MASK_D6 (1 << PD6)

// Debouncer variables for button D10
unsigned int integratorD10 = 0;
unsigned int outputD10 = 0;

// Debouncer variables for button D11
unsigned int integratorD11 = 0;
unsigned int outputD11 = 0;

// Button states
volatile bool rawButtonD10 = false;
volatile bool rawButtonD11 = false;

void debounceButton(volatile bool &input, unsigned int &integrator, unsigned int &output);

void setup()
{
  Serial.begin(9600);
  
  // Set the button pins as input and enable the pull-up resistors
  DDRB &= ~BUTTON_MASK_D10 & ~BUTTON_MASK_D11;
  PORTB |= BUTTON_MASK_D10 | BUTTON_MASK_D11;
  
  // Set the LED pins as output
  DDRD |= LED_MASK_D5 | LED_MASK_D6;
  
  // Enable pin change interrupts for pin group 1
  PCICR |= (1 << PCIE0);
  
  // Enable pin change interrupts for pins PB2 and PB3
  PCMSK0 |= (1 << PCINT2) | (1 << PCINT3);
  
  // Enable global interrupts
  sei();
}

ISR(PCINT0_vect)
{
  rawButtonD10 = !(PINB & BUTTON_MASK_D10);
  rawButtonD11 = !(PINB & BUTTON_MASK_D11);
}

void loop()
{
  debounceButton(rawButtonD10, integratorD10, outputD10);
  debounceButton(rawButtonD11, integratorD11, outputD11);

  if (outputD10 && outputD11) {
    static uint32_t lastTime = 0;
    uint32_t currentTime = millis();

    if (currentTime - lastTime > 500) {
      lastTime = currentTime;
      PORTD ^= LED_MASK_D5;
      PORTD ^= LED_MASK_D6;
    }
  } else if (outputD10) {
    PORTD |= LED_MASK_D5;
    PORTD &= ~LED_MASK_D6;
  } else if (outputD11) {
    PORTD &= ~LED_MASK_D5;
    PORTD |= LED_MASK_D6;
    Serial.println("Hello World!");
  } else {
    PORTD &= ~LED_MASK_D5;
    PORTD &= ~LED_MASK_D6;
  }
}

void debounceButton(volatile bool &input, unsigned int &integrator, unsigned int &output)
{
  if (input == 0) {
    if (integrator > 0)
      integrator--;
  } else if (integrator < MAXIMUM) {
    integrator++;
  }

  if (integrator == 0) {
    output = 0;
  } else if (integrator >= MAXIMUM) {
    output = 1;
    integrator = MAXIMUM; // Defensive code if integrator got corrupted
  }
}
