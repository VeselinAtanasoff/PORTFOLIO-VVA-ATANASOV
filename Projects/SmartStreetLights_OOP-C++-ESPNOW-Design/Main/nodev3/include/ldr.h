#ifndef LDR_H
#define LDR_H

#include "ILdr.h"
#include <Arduino.h>

constexpr int MAXLDR = 4095;

class Ldr : public ILdr
{
public:
    Ldr(uint8_t pin);
    int ReadLightLevel() override;

private:
    uint8_t pin;
};

#endif