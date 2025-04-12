#ifndef IROTEN_H
#define IROTEN_H

#include <Arduino.h>

#define ROT_EN_A 27
#define ROT_EN_B 26

class iRotEn{
    public:
        virtual int rotEn() = 0;
};

#endif