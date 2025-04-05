#include <Wire.h>

#define SLAVE_ADDRESS 0x50
#define REG_INA 0x21
#define REG_INB 0x22
#define REG_MIN 0x23
#define REG_MAX 0x24

byte inA = 0, inB = 0, minVal = 0, maxVal = 0;

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  
  inA = 12; 
  inB = 4; 
  
  
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(REG_INA);
  Wire.write(inA);
  Wire.endTransmission();
  
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(REG_INB);
  Wire.write(inB);
  Wire.endTransmission();
  
  
  Wire.requestFrom(SLAVE_ADDRESS, 2);
  if(Wire.available() >= 2) {
    minVal = Wire.read();
    maxVal = Wire.read();
  }
  
  
  Serial.print("MIN: ");
  Serial.print(minVal);
  Serial.print(", MAX: ");
  Serial.println(maxVal);
  
  delay(1000); 
}

