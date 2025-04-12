#ifndef MLDR_H
#define MLDR_H

#include <ILdr.h>
#include <stdint.h>
#include <gmock/gmock.h>


class MLdr : public ILdr
{
public:
    MOCK_METHOD1(SetupLightSensor, void(int));
    MOCK_METHOD0(ReadLightLevel, uint16_t());
};

#endif