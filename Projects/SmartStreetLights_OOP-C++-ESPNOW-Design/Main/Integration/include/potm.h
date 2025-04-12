#ifndef POTM_H
#define POTM_H

#include "ILdr.h"
#include <Arduino.h>

constexpr int POTPIN = 32;

class Potm : public ILdr {
    public:
    int ReadLightLevel() override;
};

#endif