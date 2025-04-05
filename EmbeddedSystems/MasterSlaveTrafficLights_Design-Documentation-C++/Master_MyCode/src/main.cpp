#include <Arduino.h>

const int masterGreenLed = 5; 
const int masterYellowLed = 6; 
const int masterRedLed = 7; 
const int buttonPin = 2;  

const long greenDuration = 5000;
const long yellowDuration = 2000;
const long redDuration = 5000;
const long PERMITTEDRESPONSEDELAY = 2000;

unsigned long stateStartTime = 0;
unsigned long currentMillis = 0;

const long BLINKDELAY = 1000;
unsigned long blinkStart = 0;
bool blink = false;

const int debounceDelay = 70; // Debounce delay in milliseconds
int buttonState = HIGH; // Current state of the button
int lastButtonState = HIGH; // Previous state of the button
unsigned long lastDebounceTime = 0; // Time of the last button state change

enum state {
  WAIT,
  GREEN,
  YELLOW,
  RED,
  ERROR
};

enum subState{
  SENDGREEN,
  SENDYELLOW,
  SENDRED
};

subState currentSubState = SENDGREEN;
state currentState = WAIT; // Initial state set to WAIT
int nackCount = 0; // Number of NACKs received
bool tooManyNacks = false; // Flag to indicate if too many NACKs have been received

String WaitForReply();

void setup() {
  Serial.begin(9600);
  pinMode(masterGreenLed, OUTPUT);
  pinMode(masterYellowLed, OUTPUT);
  pinMode(masterRedLed, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}



void buttonHandler() {
  int reading = digitalRead(buttonPin); // Read the button state

  // Check if the button state has changed
  if (reading != lastButtonState) {
    lastDebounceTime = millis(); // Update the debounce time
  }

  // Check if the button state has been stable for the debounce delay
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Check if the button is pressed
    if (reading == LOW) {
      if (currentState == ERROR) {
        currentState = WAIT;
        currentSubState=SENDGREEN; // Go to WAIT state
      } else {
        
        currentState = ERROR; // Go to ERROR state
      }
    }
  }

  lastButtonState = reading; // Update the last button state
}

void sendGreenState() {
  Serial.println("!FORCE#GREEN;");
  digitalWrite(masterGreenLed, LOW);
  digitalWrite(masterYellowLed, LOW);
  digitalWrite(masterRedLed, HIGH);
  if(WaitForReply().indexOf('A') != -1)
  { 
      currentState = ERROR; 
  }
  if(currentMillis - stateStartTime >= redDuration) {
    currentSubState = SENDYELLOW;
    stateStartTime = currentMillis;
  }
}



void sendYellowState() {
  Serial.println("!FORCE#YELLOW;");
  digitalWrite(masterGreenLed, LOW);
  digitalWrite(masterYellowLed, LOW);
  digitalWrite(masterRedLed, HIGH);
  if(WaitForReply().indexOf('A') != -1)
  { 
      currentState = ERROR; 
  }
  if(currentMillis - stateStartTime >= yellowDuration) {
    currentSubState = SENDRED;
    stateStartTime = currentMillis;
  }
}

void sendRedState() {
  Serial.println("!FORCE#RED;");
  digitalWrite(masterGreenLed, LOW);
  digitalWrite(masterYellowLed, LOW);
  digitalWrite(masterRedLed, HIGH);
  if(WaitForReply().indexOf('A') != -1)
  { 
      currentState = ERROR; 
  }
  if(currentMillis - stateStartTime >= redDuration) {
    currentState = GREEN;
    stateStartTime = currentMillis;
  }
}

void waitState() {
  switch (currentSubState){
    case SENDGREEN:
      sendGreenState();
      break;
    case SENDYELLOW:
      sendYellowState();
      break;  
    case SENDRED:
      sendRedState();
      break;
  }
}

void greenState() {
  Serial.println("!FORCE#RED;");
  digitalWrite(masterGreenLed, HIGH);
  digitalWrite(masterYellowLed, LOW);
  digitalWrite(masterRedLed, LOW);
  if(WaitForReply().indexOf('A') != -1)
  { 
      currentState = ERROR; 
  }
  if(currentMillis - stateStartTime >= greenDuration) {
    currentState = YELLOW;
    stateStartTime = currentMillis;
  }
}

void yellowState() {
  Serial.println("!FORCE#RED;");
  digitalWrite(masterGreenLed, LOW);
  digitalWrite(masterYellowLed, HIGH);
  digitalWrite(masterRedLed, LOW);
  if(WaitForReply().indexOf('A') != -1)
  { 
      currentState = ERROR; 
  }
  if(currentMillis - stateStartTime >= yellowDuration) {
    currentState = RED;
    stateStartTime = currentMillis;
  }
}

void redState() {
  Serial.println("!FORCE#RED;");
  digitalWrite(masterGreenLed, LOW);
  digitalWrite(masterYellowLed, LOW);
  digitalWrite(masterRedLed, HIGH);
  if(WaitForReply().indexOf('A') != -1)
  { 
      currentState = ERROR; 
  }
  if(currentMillis - stateStartTime >= redDuration) {
    currentState = WAIT;
    currentSubState = SENDGREEN;
    stateStartTime = currentMillis;
  }
}

void errorState() {
  Serial.println("!ERROR;");
  if(WaitForReply().indexOf('A') != -1)
  { 
      currentState = WAIT;
      currentSubState = SENDGREEN; 
  }
  if(millis() >= blinkStart + BLINKDELAY)//blink
      {
        if(blink)
        {
            digitalWrite(masterGreenLed, LOW);
            digitalWrite(masterYellowLed, LOW);
            digitalWrite(masterRedLed, LOW); 
            blink = false;
        }
        else
        {
            digitalWrite(masterGreenLed, LOW);
            digitalWrite(masterYellowLed, HIGH);
            digitalWrite(masterRedLed, LOW); 
            blink = true;
        }
        blinkStart = millis();
      }
}

void handleAckNack(String message) {
  if (message == "ACK") {
    nackCount = 0; // Reset nack count if ACK is received
    tooManyNacks = false;
  } else if (message == "NACK") {
    nackCount++; // Increment nack count if NACK is received
    if (nackCount >= 15) { // Adjust the threshold as needed
      tooManyNacks = true;
    }
  }
}

void loop() {
  currentMillis = millis();
  buttonHandler();

  switch(currentState) {
    case WAIT:
      waitState();
      break;
    case GREEN:
      greenState();
      break;
    case YELLOW:
      yellowState();
      break;
    case RED:
      redState();
      break;
    case ERROR:
      errorState();
      break;
  }
}


String WaitForReply()
{
    unsigned long startTime = millis();
    String reply = "";
    while (reply == "")
    {
        if(millis() >= startTime + PERMITTEDRESPONSEDELAY)
        {
            Serial.println("!ERROR;");
            currentState = ERROR;
            return "";
        }
        while (Serial.available() > 0)
        {
            reply += Serial.read();
        }
    }
    return reply;
}

  
  
