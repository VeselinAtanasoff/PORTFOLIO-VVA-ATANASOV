#ifndef ILIGHT_H
#define ILIGHT_H

class ILight
{
public:
    virtual ~ILight() {};

    virtual void AdjustLightIntensity(uint8_t) = 0;
    virtual bool LightCheck() = 0;
};

#endif
