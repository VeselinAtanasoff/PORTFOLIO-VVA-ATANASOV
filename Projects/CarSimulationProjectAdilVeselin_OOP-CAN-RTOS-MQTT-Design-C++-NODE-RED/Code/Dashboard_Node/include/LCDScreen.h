#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

constexpr unsigned long LCD_I2C_ADDR = 0x27;
constexpr int lcdColumns = 16;
constexpr int lcdRows = 2;

class LCDScreen
{
public:
    LCDScreen();

    void PrintFirstRow(const String msg, int cursorPos);
    void PrintSecondRow(const String msg, int cursorPos);
    void Clear();

private:
    LiquidCrystal_I2C LCD;

};