#ifndef CONCRETE_ROT_EN_H
#define CONCRETE_ROT_EN_H

#include "ILdr.h"
#include <Arduino.h>

constexpr int ROT_EN_A = 27;
constexpr int ROT_EN_B = 26;

class RotEn : public ILdr {
    public:
    int ReadLightLevel() override;
};

#endif