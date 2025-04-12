#include <potm.h>

int16_t lightLevel;

int Potm :: ReadLightLevel()
{
    lightLevel = analogRead(POTPIN);
    lightLevel = map(lightLevel, 0, 4095, 100, 800);
    return lightLevel;
}