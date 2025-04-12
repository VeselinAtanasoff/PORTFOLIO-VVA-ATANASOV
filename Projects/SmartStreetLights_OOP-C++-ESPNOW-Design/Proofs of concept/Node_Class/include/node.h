#ifndef NODECLASS_H
#define NODECLASS_H

#include <iostream>
#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "connection.h"
#include <vector>

#define MACADDRESSLENGTH 6

struct Mac_Address
{
    uint8_t mac_address[6];
};

class Node
{
public:
    Node(int myIndex);
    std::vector<Mac_Address> mac_address = {
        {0x7c, 0x9e, 0xbd, 0xf4, 0x26, 0x94},
        {0xcc, 0xdb, 0xa7, 0x3f, 0xc9, 0x50},
        {0x94, 0xB9, 0x7E, 0xC0, 0x08, 0x6C},
        {0xA0, 0xB7, 0x65, 0xDC, 0x34, 0xF0},
        };
    void printMacAddresses();
    uint8_t checkMacAddress();
    void leftPeerMac(int macIndex);
    void rightPeerMac(int macIndex);
    void mostLeftPeerMac(int macIndex);
    void mostRightPeerMac(int macIndex);

private:
    uint8_t peerLeftAddress[6];
    uint8_t peerAltLeftAddress[6];
    uint8_t peerRightAddress[6];
    uint8_t peerAltRightAddress[6];

};

#endif