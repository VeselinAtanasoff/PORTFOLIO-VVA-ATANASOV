#include "Microwave.h"
#include "MLight.h"
#include "MMotor.h"
#include "MSystem.h"
#include "MUserInterface.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::Return;
using ::testing::_;

class MicrowaveTest : public ::testing::Test
{
protected:
    MicrowaveTest()
        : microwave(light, motor, system, ui)
    {
    }

    virtual ~MicrowaveTest() {}

    MLight light;
    MMotor motor;
    MSystem system;
    MUserInterface ui;
    Microwave microwave;
};

TEST_F(MicrowaveTest, test_start_event)
{
    EXPECT_CALL(ui, GetRequestedPower()).WillOnce(Return(800));
    EXPECT_CALL(motor, SetPower(800));
    EXPECT_CALL(ui, StartClock());

    microwave.HandleEvent(EV_START); // Call the method
    EXPECT_EQ(STATE_HEATING, microwave.GetCurrentState()); // Check the state afterwards
}

TEST_F(MicrowaveTest, test_door_open_when_idle_event)
{
    EXPECT_CALL(light, On());
    microwave.HandleEvent(EV_DOOR_OPEN); // Call the method
    EXPECT_EQ(STATE_IDLE, microwave.GetCurrentState()); // Check the state afterwards
}

TEST_F(MicrowaveTest, test_time_up_event_in_heating)
{
    // Set the microwave to the heating state
    EXPECT_CALL(ui, GetRequestedPower()).WillOnce(Return(800));
    EXPECT_CALL(motor, SetPower(800));
    EXPECT_CALL(ui, StartClock());
    microwave.HandleEvent(EV_START); // Start heating

    // Now handle the time-up event
    EXPECT_CALL(light, Off());
    EXPECT_CALL(motor, SetPower(0));
    EXPECT_CALL(system, SetTimer(0));
    EXPECT_CALL(ui, StopClock());
    EXPECT_CALL(ui, Ping());

    microwave.HandleEvent(EV_TIME_UP); // Call the method
    EXPECT_EQ(STATE_IDLE, microwave.GetCurrentState()); // Check the state afterwards
}

TEST_F(MicrowaveTest, test_door_open_when_heating_event)
{
    // Start heating first
    EXPECT_CALL(ui, GetRequestedPower()).WillOnce(Return(800));
    EXPECT_CALL(motor, SetPower(800));
    EXPECT_CALL(ui, StartClock());
    microwave.HandleEvent(EV_START); // Start heating

    // Open the door
    EXPECT_CALL(light, On());
    EXPECT_CALL(motor, SetPower(0));
    EXPECT_CALL(ui, StopClock());

    microwave.HandleEvent(EV_DOOR_OPEN); // Call the method
    EXPECT_EQ(STATE_PAUSED, microwave.GetCurrentState()); // Check the state afterwards
}

TEST_F(MicrowaveTest, test_door_close_when_paused_event)
{
    // Start heating first
    EXPECT_CALL(ui, GetRequestedPower()).WillOnce(Return(800));
    EXPECT_CALL(motor, SetPower(800));
    EXPECT_CALL(ui, StartClock());
    microwave.HandleEvent(EV_START); // Start heating

    // Open the door
    EXPECT_CALL(light, On());
    EXPECT_CALL(motor, SetPower(0));
    EXPECT_CALL(ui, StopClock());
    microwave.HandleEvent(EV_DOOR_OPEN); // Call the method
    EXPECT_EQ(STATE_PAUSED, microwave.GetCurrentState()); // Check the state afterwards

    // Close the door
    EXPECT_CALL(light, On());
    EXPECT_CALL(ui, GetRequestedPower()).WillOnce(Return(800));
    EXPECT_CALL(motor, SetPower(800)); // Resume heating with the requested power
    EXPECT_CALL(ui, StartClock());

    microwave.HandleEvent(EV_DOOR_CLOSED); // Call the method
    EXPECT_EQ(STATE_HEATING, microwave.GetCurrentState()); // Check the state afterwards
}

TEST_F(MicrowaveTest, test_power_change_when_heating)
{
    // Start heating first
    EXPECT_CALL(ui, GetRequestedPower()).WillOnce(Return(800));
    EXPECT_CALL(motor, SetPower(800));
    EXPECT_CALL(ui, StartClock());
    microwave.HandleEvent(EV_START); // Start heating

    // Change power during heating
    EXPECT_CALL(ui, GetRequestedPower()).WillOnce(Return(500));
    EXPECT_CALL(motor, SetPower(500));

    microwave.HandleEvent(EV_POWER_CHANGED); // Call the method
    EXPECT_EQ(STATE_HEATING, microwave.GetCurrentState()); // State should remain heating
}





