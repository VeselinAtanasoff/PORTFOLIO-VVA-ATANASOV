#ifndef MICROWAVE_H
#define MICROWAVE_H

#include "Event.h"
#include "State.h"
#include "ILight.h"
#include "IMotor.h"
#include "ISystem.h"
#include "IUserInterface.h"

class Microwave
{
public:
    Microwave(ILight& light, IMotor& motor, ISystem& system, IUserInterface& ui);

    void HandleEvent(Event ev);
    State HandleIdleState(Event ev);
    State GetCurrentState() const { return currentState; }

private:
    State currentState;
    ILight& light;
    IMotor& motor;
    ISystem& system;
    IUserInterface& ui;
};

#endif
