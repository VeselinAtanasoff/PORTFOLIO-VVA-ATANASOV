#ifndef MLIGHT_H
#define MLIGHT_H

#include "ILight.h"

#include <gmock/gmock.h>

class MLight : public ILight
{
public:
    MOCK_METHOD1(AdjustLightIntensity, void(uint8_t));
    MOCK_METHOD0(LightCheck, bool());
};

#endif
