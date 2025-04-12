#ifndef CONCRETE_ROT_EN_H
#define CONCRETE_ROT_EN_H

#include "iRotEn.h"
#include <Arduino.h>

int aLastState = LOW;
int counter = 0;

class RotEn : public iRotEn {
    public:
    int rotEn();
};

#endif