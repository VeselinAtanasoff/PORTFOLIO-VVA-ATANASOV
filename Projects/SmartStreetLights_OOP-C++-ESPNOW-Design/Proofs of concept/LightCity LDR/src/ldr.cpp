#include "ldr.h"

void iLdr :: SetupLightSensor(uint8_t pin){
  pinMode (pin, INPUT);
}

int iLdr :: ReadLightLevel(){
  int ldrValue = analogRead(LDR);
  ldrValue = map(ldrValue, 0, MAXLDR, 0, 100);
  return ldrValue;
}