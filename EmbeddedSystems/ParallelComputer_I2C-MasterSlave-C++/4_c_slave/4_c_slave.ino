#include <Wire.h>

#define SLAVE_ADDRESS 0x50
#define REG_INA 0x21
#define REG_INB 0x22
#define REG_MIN 0x23
#define REG_MAX 0x24

byte inA, inB;

void setup() {
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
}

void loop() {
  delay(100);
}

void receiveData(int byteCount) {
  while (Wire.available()) {
    byte reg = Wire.read();
    if (reg == REG_INA) {
      inA = Wire.read();
    } else if (reg == REG_INB) {
      inB = Wire.read();
    }
  }
}

void sendData() {
  Wire.write(inA < inB ? inA : inB); // MIN
  Wire.write(inA > inB ? inA : inB); // MAX
}

