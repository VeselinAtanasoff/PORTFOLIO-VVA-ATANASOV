#include <Arduino.h>

const int redLed = 4;
const int yellowLed = 5;
const int greenLed = 6;

const unsigned long TIMEOUT = 5000; // Timeout period in milliseconds
const long BLINKDELAY = 1000;

unsigned long blinkStart = 0;
bool blink = false;

enum State {
  RED,
  YELLOW,
  GREEN,
  ERROR_STATE
};

State currentState = ERROR_STATE; // Initial state



void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
}

void processCommand(String command) {
  if (command == "FORCE#RED") {
    digitalWrite(redLed, HIGH);
    digitalWrite(yellowLed, LOW);
    digitalWrite(greenLed, LOW);
    currentState = RED;
    Serial.println("A"); // Send acknowledgement
  } else if (command == "FORCE#YELLOW") {
    digitalWrite(redLed, LOW);
    digitalWrite(yellowLed, HIGH);
    digitalWrite(greenLed, LOW);
    currentState = YELLOW;
    Serial.println("A"); // Send acknowledgement
  } else if (command == "FORCE#GREEN") {
    digitalWrite(redLed, LOW);
    digitalWrite(yellowLed, LOW);
    digitalWrite(greenLed, HIGH);
    currentState = GREEN;
    Serial.println("A"); // Send acknowledgement
  } else if(command == "ERROR") {
    currentState = ERROR_STATE;
    Serial.println("A"); // Send non-acknowledgement
  }else {
    currentState = ERROR_STATE;
    Serial.println("N"); // Send non-acknowledgement
  }
}

void loop() {
  
  if (Serial.available() > 0) {
    char startChar = '!'; // Start character
    char endChar = ';';   // End character

    // Read characters until the start character is encountered
    while (Serial.read() != startChar) {
      // Discard characters until start character is found
    }

    // Read characters until the end character is encountered
    String command = Serial.readStringUntil(endChar);

    // Process the command
    processCommand(command);

    // Update the time when the last command was received

  }

  switch (currentState) {
    case RED:
      // Do nothing, red LED is already lit
      break;

    case YELLOW:
      // Do nothing, yellow LED is already lit
      break;

    case GREEN:
      // Do nothing, green LED is already lit
      break;

    case ERROR_STATE:
      if(millis() >= blinkStart + BLINKDELAY)
      {
        if(blink)
        {
            digitalWrite(greenLed, LOW);
            digitalWrite(yellowLed, LOW);
            digitalWrite(redLed, LOW); 
            blink = false;
        }
        else
        {
            digitalWrite(greenLed, LOW);
            digitalWrite(yellowLed, HIGH);
            digitalWrite(redLed, LOW); 
            blink = true;
        }
        blinkStart = millis();
      }
      break;
  }
}

  





