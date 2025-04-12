#ifndef NODE_H
#define NODE_H

#include <stdint.h>
#include <cstring>
#include <IConnection.h>
#include <ILight.h>
#include <States.h>
#include <ILdr.h>
#include <IMovementSensor.h>
#include <ErrorCode.h>

#define MACADDRESSLENGTH 6
#define LIGHT_PIN 2
#define LIGHT_READ_PIN 34
#define LDR_PIN 4
#define ROTEN_PINA 27
#define ROTEN_PINB 26
#define LEVEL0 0
#define LEVEL1 10
#define LEVEL2 25
#define LEVEL3 50
#define LEVEL4 75
#define LEVEL5 100
#define LIGHT_THRESHOLD 400

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
    Node(PositionMac *peerMACs, IConnection &connection, ILight &light, ILdr &lightSensor, IMovementSensor &movementSensor);
    void HandleDay();
    void HandleNight();
    void HandleConnectionErrorDetection();
    void HandleConnectionError();
    void HandleHardwareError();
    States HandleStates();
    States state;
    bool mostLeftNode;
    bool mostRightNode;
    States lastState;

private:
    uint8_t peerLeftAddress[MACADDRESSLENGTH];
    uint8_t peerAltLeftAddress[MACADDRESSLENGTH];
    uint8_t peerRightAddress[MACADDRESSLENGTH];
    uint8_t peerAltRightAddress[MACADDRESSLENGTH];
    uint8_t monitorAddress[MACADDRESSLENGTH];
    Message lastMessage;
    Message message;
    uint8_t myPower;
    


    IConnection &connection;
    ILight &light;
    ILdr &lightSensor;
    IMovementSensor &movementSensor;
};

#endif