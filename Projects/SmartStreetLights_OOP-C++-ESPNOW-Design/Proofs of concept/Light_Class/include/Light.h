#ifndef LIGHT_H
#define LIGHT_H
#include <Arduino.h>
#define PWM_CHANNEL_LED 0
#define PWM_FREQUENCY_LED 5000
#define PWM_RESOLUTION_LED 8
#define MIN_CHECK_INTENSITY 25
#define MAX_CHECK_INTENSITY 75
#define MIN_N_CHECK_READINGS 8
#define FAULTY_LED_READING 4095

class Light {
  public:
    Light();
    void AdjustLightIntensity(int percent);
    bool LightCheck();
  private:
    uint8_t ledPin=2;
    uint8_t readPin=34;
    uint8_t previousIntensity=0;
    void LightCheckWrite();
};

#endif