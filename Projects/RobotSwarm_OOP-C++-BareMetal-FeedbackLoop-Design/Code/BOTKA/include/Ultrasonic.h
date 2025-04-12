#pragma once
#include "stm32f303xe.h"

#define PSCValue 71
#define ARRValue 59999
class Ultrasonic {
public:
    Ultrasonic();
    void triggerSensor();
    bool checkForWall();
    float getFilteredDistance();

private:
    void initGPIO();
    void initPWMOutput();
    void initPWMInput();
    float getDistance();
    float distance;
    float filteredDistance; // Store the current filtered value
    float alpha = 0.8; // Smoothing factor adjust lower if filter is too slow or higher if too noisy
};