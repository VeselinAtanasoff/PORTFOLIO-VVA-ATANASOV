#ifndef MMOVEMENT_SENSOR_H
#define MMOVEMENT_SENSOR_H

#include <IMovementSensor.h>
#include <gmock/gmock.h>

class MMovementSensor : public IMovementSensor
{
public:
    MOCK_METHOD1(SetupSensor, void(int));
    MOCK_METHOD0(DetectMovement, bool());
};

#endif