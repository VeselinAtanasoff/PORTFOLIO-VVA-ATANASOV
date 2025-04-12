#pragma once
#include "stm32f303xe.h"
#include <cstdio>
#include <cstring>
#include <cstdarg>

class UI {
public:
    UI();
    void sendString(const char *str);
    void sendInt(const int value);
    char* receiveString();
    void sendFormattedString(const char *format, ...);

private:
    void initUSART();
    static const int BUFLENGTH = 100;
    char sndBuf[BUFLENGTH];
    char rcvBuf[BUFLENGTH];
};