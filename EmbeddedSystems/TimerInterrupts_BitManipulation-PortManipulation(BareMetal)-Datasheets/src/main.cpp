#include <Arduino.h>

// Debounce parameters
#define DEBOUNCE_TIME 0.3
#define SAMPLE_FREQUENCY 10
#define MAXIMUM (DEBOUNCE_TIME * SAMPLE_FREQUENCY)

// Button and LED pin masks
#define LED_MASK_D8 (1 << PB0)
#define LED_MASK_D9 (1 << PB1)
#define BUTTON_MASK_D10 (1 << PB2)
#define BUTTON_MASK_D11 (1 << PB3)
#define LED_MASK_D5 (1 << PD5)
#define LED_MASK_D6 (1 << PD6)
#define INTERNAL_LED (1 << PB5)

// Debouncer variables for button D10
unsigned int integratorD10 = 0;
unsigned int outputD10 = 0;

// Debouncer variables for button D11
unsigned int integratorD11 = 0;
unsigned int outputD11 = 0;

// Button states
volatile bool rawButtonD10 = false;
volatile bool rawButtonD11 = false;

// Counter variable for binary counter
uint8_t counter = 0;
uint8_t slowDownCounter = 0;

// Counter for internal LED
int ledCounter = 0;

void debounceButton(volatile bool &input, unsigned int &integrator, unsigned int &output);

void setup()
{
  Serial.begin(9600);

  // Set the button pins as input and enable the pull-up resistors
  DDRB |= LED_MASK_D8 | LED_MASK_D9 | INTERNAL_LED;
  DDRB &= ~BUTTON_MASK_D10 & ~BUTTON_MASK_D11;
  PORTB |= BUTTON_MASK_D10 | BUTTON_MASK_D11;

  // Set the LED pins as output
  DDRD |= LED_MASK_D5 | LED_MASK_D6;

  // Enable pin change interrupts for pin group 1
  PCICR |= (1 << PCIE0);

  // Enable pin change interrupts for pins PB2 and PB3
  PCMSK0 |= (1 << PCINT2) | (1 << PCINT3);

  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  // Set CTC mode (Clear Timer on Compare Match)
  TCCR1B |= (1 << WGM12);

  // Set compare match register for 4Hz increments
  // OCR1A = [16,000,000 / (prescaler * desired frequency)] - 1 (must be <65536)
  OCR1A = 62499; // (16000000 / (64 * 4Hz)) - 1

  // Set CS11 and CS10 bits for 64 prescaler
  TCCR1B |= (1 << CS11) | (1 << CS10);

  // Enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  // Enable global interrupts
  sei();
}

ISR(PCINT0_vect)
{
  rawButtonD10 = !(PINB & BUTTON_MASK_D10);
  rawButtonD11 = !(PINB & BUTTON_MASK_D11);
}

ISR(TIMER1_COMPA_vect)
{
  ledCounter++;
  if (outputD11)
  {
    OCR1A = 31249;
    if (ledCounter == 4)
    {
      PORTB ^= INTERNAL_LED;
      ledCounter = 0;
    }
  }
  else
  {
    OCR1A = 62499;
    if(ledCounter>2){
      ledCounter = ledCounter - 2;
    }
    if (ledCounter == 2)
    {
      PORTB ^= INTERNAL_LED;
      ledCounter = 0;
    }
  }

  PORTD &= ~((1 << PD5) | (1 << PD6));
  PORTB &= ~((1 << PB0) | (1 << PB1));

  if (outputD10)
  {
    if (slowDownCounter >= 2)
    {
      counter++;
      slowDownCounter = 0;
    }
    else
    {
      slowDownCounter++;
    }
  }
  else
  {
    counter++;
  }

  PORTD |= (counter & 0b0011) << PD5;
  PORTB |= (counter & 0b1100) >> 2;

  if (counter == 16)
  {
    counter = 0;
  }
}

void loop()
{
  debounceButton(rawButtonD10, integratorD10, outputD10);
  debounceButton(rawButtonD11, integratorD11, outputD11);
}

void debounceButton(volatile bool &input, unsigned int &integrator, unsigned int &output)
{
  if (input == 0)
  {
    if (integrator > 0)
      integrator--;
  }
  else if (integrator < MAXIMUM)
  {
    integrator++;
  }

  if (integrator == 0)
  {
    output = 0;
  }
  else if (integrator >= MAXIMUM)
  {
    output = 1;
    integrator = MAXIMUM; // Defensive code if integrator got corrupted
  }
}
