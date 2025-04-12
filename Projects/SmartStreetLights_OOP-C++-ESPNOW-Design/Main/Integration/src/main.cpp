#include <Arduino.h>
#include <node.h>
#include <Light.h>
#include <ldr.h>
#include <rotEn.h>
#include <potm.h>
#include <MovementSensor.h>

constexpr int BAUDRATE = 115200;
constexpr int LIGHT_PIN = 2;
constexpr int LIGHT_READ_PIN = 34;
constexpr int LDR_PIN = 4;
constexpr int TRIG_PIN = 5;
constexpr int ECHO_PIN = 18;

/*
0x7C, 0x9E, 0xBD, 0xF3, 0xDE, 0x0C (M/Monitor)
0x94, 0xB9, 0x7E, 0xC0, 0x08, 0x6C (M)
0xA0, 0xB7, 0x65, 0xDC, 0x34, 0xF0 (L)
0x7c, 0x9e, 0xbd, 0xf4, 0x26, 0x94 (F)
0xcc, 0xdb, 0xa7, 0x3f, 0xc9, 0x50 (F)
0xC8, 0xF0, 0x9E, 0x4E, 0x50, 0x64 (V)
0x24,0x0A,0xC4,0x60,0xE3,0xC4 (J)
0xc8,0xf0,0x9e,0x4d,0x10, 0x48(Myky)
*/

<<<<<<< Updated upstream
uint8_t mostLeftPeer[MACADDRESSLENGTH] = {0xA0, 0xB7, 0x65, 0xDC, 0x34, 0xF0};
uint8_t leftPeer[MACADDRESSLENGTH] = {0xcc, 0xdb, 0xa7, 0x3f, 0xc9, 0x50};
uint8_t rightPeer[MACADDRESSLENGTH] = {0xC8, 0xF0, 0x9E, 0x4E, 0x50, 0x64};
uint8_t mostRightPeer[MACADDRESSLENGTH] = {0x24, 0x0A, 0xC4, 0x60, 0xE3, 0xC4};
=======
uint8_t mostLeftPeer[MACADDRESSLENGTH] = {0};
uint8_t leftPeer[MACADDRESSLENGTH] = {0};
uint8_t rightPeer[MACADDRESSLENGTH] = {0xcc, 0xdb, 0xa7, 0x3f, 0xc9, 0x50};
uint8_t mostRightPeer[MACADDRESSLENGTH] = {0x94, 0xB9, 0x7E, 0xC0, 0x08, 0x6C};
>>>>>>> Stashed changes
uint8_t monitor[MACADDRESSLENGTH] = {0x7C, 0x9E, 0xBD, 0xF3, 0xDE, 0x0C};

void initialiseMACAddresses(PositionMac *paramPeerMACs)
{
    memcpy((paramPeerMACs->most_left), mostLeftPeer, sizeof(paramPeerMACs->most_left));
    memcpy((paramPeerMACs->left), leftPeer, sizeof(paramPeerMACs->left));
    memcpy((paramPeerMACs->right), rightPeer, sizeof(paramPeerMACs->right));
    memcpy((paramPeerMACs->most_right), mostRightPeer, sizeof(paramPeerMACs->most_right));
    memcpy((paramPeerMACs->monitor), monitor, sizeof(paramPeerMACs->monitor));
}

PositionMac *peerMACs = new PositionMac();
Node *node;
Light *light = new Light(LIGHT_PIN, LIGHT_READ_PIN);
Potm* ldr = new Potm();
MovementSensor *movementSensor = new MovementSensor(TRIG_PIN, ECHO_PIN);

void setup()
{
    Serial.begin(BAUDRATE);
    initialiseMACAddresses(peerMACs);
    node = new Node(peerMACs, light, ldr, movementSensor);
}

void loop()
{
    node->HandleStates();
}