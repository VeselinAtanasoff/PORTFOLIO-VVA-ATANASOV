#ifndef ILDR_H
#define ILDR_H

#include <Arduino.h>

#define LDR 4
#define MAXLDR 4095

class iLdr{
  public:
    virtual void SetupLightSensor(uint8_t pin);
    virtual int ReadLightLevel() = 0;
};

#endif