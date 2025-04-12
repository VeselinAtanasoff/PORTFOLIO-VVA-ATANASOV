#ifndef ILDR_H
#define ILDR_H

class ILdr
{
public:
    virtual ~ILdr(){};
    virtual void SetupLightSensor(int) = 0;
    virtual uint16_t ReadLightLevel() = 0;
};

#endif