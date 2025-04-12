#ifndef NODECLASS_H
#define NODECLASS_H

#include <Arduino.h>
#include <connection.h>
#include <ILight.h>
#include <ILdr.h>
#include <IConnection.h>
#include <IMovementSensor.h>
#include <eStates.h>
#include <eErrorCode.h>
#include <vector>

constexpr int MACADDRESSLENGTH = 6;
constexpr int ROTEN_PINA = 27;
constexpr int ROTEN_PINB = 26;
constexpr int LEVEL0 = 0;
constexpr int LEVEL1 = 10;
constexpr int LEVEL2 = 25;
constexpr int LEVEL3 = 50;
constexpr int LEVEL4 = 75;
constexpr int LEVEL5 = 100;
constexpr int LIGHT_THRESHOLD = 400;

struct PositionMac
{
    uint8_t most_left[MACADDRESSLENGTH];
    uint8_t left[MACADDRESSLENGTH];
    uint8_t right[MACADDRESSLENGTH];
    uint8_t most_right[MACADDRESSLENGTH];
    uint8_t monitor[MACADDRESSLENGTH];
};

class Node
{
public:
    Node(PositionMac *, ILight *, ILdr *, IMovementSensor*);
    void HandleDay();
    void HandleNight();
    void HandleConnectionErrorDetection();
    void HandleConnectionError();
    void HandleHardwareError();
    void HandleStates();

private:

    ILight *light;
    ILdr *ldr;
    IMovementSensor *movementSensor;

    Message lastMessage;
    States state = IDLE;
    States lastState = IDLE;

    bool leftConnectionStatus = true;
    bool rightConnectionStatus = true;
    bool mostLeftNode = false;
    bool mostRightNode = false;
};

#endif