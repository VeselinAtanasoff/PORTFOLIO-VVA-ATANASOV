#ifndef LDR_H
#define LDR_H

#include "iLdr.h"
#include <Arduino.h>

class Ldr : public iLdr {
    public:
        void SetupLightSensor(uint8_t pin);
        int ReadLightLevel();
};

#endif