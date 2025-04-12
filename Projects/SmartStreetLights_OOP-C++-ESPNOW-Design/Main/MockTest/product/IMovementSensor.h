#ifndef IMOVEMENT_SENSOR_H
#define IMOVEMENT_SENSOR_H

class IMovementSensor
{
public:
    ~IMovementSensor() {};
    virtual void SetupSensor(int) = 0;
    virtual bool DetectMovement() = 0;
};

#endif