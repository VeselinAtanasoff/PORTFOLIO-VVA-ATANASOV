#include <Arduino.h>
#include "ldr.h"
#include "rotEn.h"

Ldr ldr;
RotEn rotEn;

void setup() { 
  pinMode (ROT_EN_A, INPUT);
  pinMode (ROT_EN_B, INPUT);
  ldr.SetupLightSensor(LDR);
  
  Serial.begin (9600);
} 

void loop() {
  // uncomment the code below to run ldr

  int value = ldr.ReadLightLevel();



  // uncomment the code below to run rotary encoder

  // int value = rotEn.rotEn();
  // if(value != -1){
  //   Serial.println(value);
  // }
}