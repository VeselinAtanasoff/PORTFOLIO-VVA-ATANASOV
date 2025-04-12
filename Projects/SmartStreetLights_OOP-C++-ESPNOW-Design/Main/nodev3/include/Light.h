#ifndef LIGHT_H
#define LIGHT_H
#include <Arduino.h>
#include <ILight.h>

class Light : public ILight{
  public:
    Light(uint8_t lPin, uint8_t rPin);
    void AdjustLightIntensity(uint8_t percent) override;
    bool LightCheck() override;
  private:
    uint8_t ledPin;
    uint8_t readPin;
    uint8_t previousIntensity=0;
    void LightCheckWrite();
};

#endif