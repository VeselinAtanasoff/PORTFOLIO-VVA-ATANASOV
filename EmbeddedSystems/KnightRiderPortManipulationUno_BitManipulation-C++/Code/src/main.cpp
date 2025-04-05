#include <Arduino.h>

#define LEDMASK (1 << PB0)
#define BUTTONMASK (1 << PD5)// pin 5 external ressistor 
#define BURRONMASK_SWEEP (1 << PD2)// pin 2 pull up 
#define LEDBUILTINMASK (1 << DDB5)
#define LED1MASK (1 << PB1)
#define LED2MASK (1 << PB2)
#define LED3MASK (1 << PB3)
#define LED4MASK (1 << PB4)

unsigned long startMillis;


enum StateA
{
  SHIFTLR,
  DELAYLR,
  SHIFTRL,
  DELAYRL
};

StateA current_state = SHIFTLR;
uint8_t maskA = 0x08; // Starting mask (0000 1000)      
uint16_t maskB = 0x0780;// Starting mask (0000 0111 1000 0000)          
unsigned long previousMillis = 0;   // Stores the last time the state was updated
const unsigned long interval = 100; // Interval at which to change states

void setup()
{
  Serial.begin(9600);
  DDRB = DDRB | (LEDMASK | LED1MASK | LED2MASK | LED3MASK | LED4MASK | LEDBUILTINMASK); // Set LED pins as output
  DDRD = ((DDRD & ~BUTTONMASK) | (DDRD & ~BURRONMASK_SWEEP));                           // Set PD5 and PD2 as input
  PORTD = PORTD | BURRONMASK_SWEEP;                                                     // Enable pull-up resistor on PD2
}

void blink()
{
  unsigned long currentMillis = millis(); // Update current time
  if (currentMillis - startMillis >= period)
  {
    PORTB ^= LEDMASK; // Toggle the external LED
    startMillis = currentMillis;
  }
}

void sweep()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    // Save the last time you changed the mask
    previousMillis = currentMillis;

    switch (current_state)
    {
    case SHIFTLR:
      if (maskA != 0x08) // 0b1000 in binary
      {             
        maskA <<= 1; // Shift mask left
        
      }
      else
      {
        current_state = DELAYLR; // Switch state
      }
      break;

    case DELAYLR:
      current_state = SHIFTRL; // Change direction of shift
      break;

    case SHIFTRL:
      if (maskA != 0x01) //compare mask to determine if it is at the right end
      {             
        maskA >>= 1; // Shift mask right
        
      }
      else
      {
        current_state = DELAYRL; // Switch state
      }
      break;

    case DELAYRL:
      current_state = SHIFTLR; // Change direction of shift
      break;
    }
    
    // Clear bits 1 to 4 and set according to maskA
    PORTB = (PORTB & 0xE1) | (maskA << 1);
  }
}


void sweep_b()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    // Save the last time you changed the mask
    previousMillis = currentMillis;

    switch (current_state)
    {
    case SHIFTLR:
      if (maskB != 0xF000)
      {             // Check if the mask is not yet at the left end
        maskB <<= 1; // Shift mask left
      }
      else
      {
        current_state = DELAYLR; // Switch state
      }
      break;

    case DELAYLR:
      current_state = SHIFTRL; // Change direction of shift
      break;

    case SHIFTRL:
      if (maskB != 0x000F)
      {             // Check if the mask is not yet at the right end
        maskB >>= 1; // Shift mask right
      }
      else
      {
        current_state = DELAYRL; // Switch state
      }
      break;

    case DELAYRL:
      current_state = SHIFTLR; // Change direction of shift
      break;
    }
    PORTB = (PORTB & ~((1 << PB1) | (1 << PB2) | (1 << PB3) | (1 << PB4))) | ((maskB & 0x01) << PB1) | ((maskB & 0x02) << (PB2 - 1)) | ((maskB & 0x04) << (PB3 - 2)) | ((maskB & 0x08) << (PB4 - 3));                               
    
  }
}

void button()
{
  if (PIND & BUTTONMASK)
  {
    PORTB = PORTB | LEDBUILTINMASK; // Turn on the built-in LED
  }
  else
  {
    PORTB = PORTB & ~LEDBUILTINMASK; // Turn off the built-in LED
  }
}


void burron_test()
{
  if (PIND & BURRONMASK_SWEEP)
  {
    sweep_b(); // Switch between the two sweep functions depending on the state of the button
  }
  else
  {
    sweep(); 
  }
}

void loop()
{
  
  burron_test();
  button();
  blink();

}