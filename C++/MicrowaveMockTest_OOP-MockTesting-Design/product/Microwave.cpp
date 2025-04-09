#include "Microwave.h"
#include <iostream>

Microwave::Microwave(ILight &light, IMotor &motor, ISystem &system, IUserInterface &ui)
    : currentState(STATE_IDLE), light(light), motor(motor), system(system), ui(ui)
{
}

State Microwave::HandleIdleState(Event ev)
{
    State result = STATE_IDLE;

    switch (ev)
    {
    case EV_DOOR_OPEN:
        light.On();
        break; // Prevent fallthrough warning

    case EV_START:
        light.On(); // Ensure light is on when heating starts (R4)
        motor.SetPower(ui.GetRequestedPower()); // Set power when heating starts
        ui.StartClock();
        result = STATE_HEATING;
        break;

    case EV_DOOR_CLOSED:
        light.Off(); // Ensure the light is off when the door is closed
        break;

    default:
        // Ignored event, nothing to do here
        break;
    }

    return result;
}

void Microwave::HandleEvent(Event ev)
{
    switch (currentState)
    {
    case STATE_IDLE:
        currentState = HandleIdleState(ev);
        break;

    case STATE_HEATING:
        switch (ev)
        {
        case EV_TIME_UP:
            light.Off();
            motor.SetPower(0);
            system.SetTimer(0);
            ui.StopClock();
            ui.Ping(); // Notify with a sound on time-up event (R7)
            currentState = STATE_IDLE;
            break;

        case EV_DOOR_OPEN:
            light.On();
            motor.SetPower(0);
            ui.StopClock();
            currentState = STATE_PAUSED;
            break;

        case EV_DOOR_CLOSED:
            light.On();
            motor.SetPower(ui.GetRequestedPower()); // Resume heating at the last power
            system.SetTimer(30); // Optionally set a timer; adjust as needed
            ui.StartClock();
            break;

        case EV_POWER_CHANGED:
            motor.SetPower(ui.GetRequestedPower()); // Allow changing power while heating (R2)
            break;

        default:
            // Ignored event, nothing to do here
            break;
        }
        break;

    case STATE_PAUSED:
        switch (ev)
        {
        case EV_DOOR_CLOSED:
            light.On();
            motor.SetPower(ui.GetRequestedPower()); // Resume heating with the requested power
            ui.StartClock();
            currentState = STATE_HEATING; // Transition back to heating state
            break;

        default:
            std::cerr << "ERROR: illegal/unhandled state with number: " << currentState;
            break;
        }
        break;
    }
}

