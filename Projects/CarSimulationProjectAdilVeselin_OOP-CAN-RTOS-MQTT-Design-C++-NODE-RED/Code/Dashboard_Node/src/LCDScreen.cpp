#include "LCDScreen.h"

LCDScreen::LCDScreen() : LCD(LCD_I2C_ADDR, lcdColumns, lcdRows)
{
    LCD.init();
    LCD.backlight();
}

void LCDScreen::PrintFirstRow(const String msg, int cursorPos)
{
    LCD.setCursor(cursorPos, 0);
    LCD.print(msg);
}

void LCDScreen::PrintSecondRow(const String msg, int cursorPos)
{
    LCD.setCursor(cursorPos, 1);
    LCD.print(msg);
}

void LCDScreen::Clear()
{
    LCD.clear();
}