#ifndef MACADDRESSES_H
#define MACADDRESSES_H

#include <Arduino.h>
#include <vector>
#include <algorithm> 

#define SIZE_MACADDRRESS 6

enum NEIGHBOURING_NODE {
    MOST_LEFT = -2,
    LEFT = -1,
    RIGHT = 1,
    MOST_RIGHT = 2,
};

struct Mac_Address {
    uint8_t mac_address[SIZE_MACADDRRESS];
};

class MacAddresses
{
    public:
    
    bool addMacAddress(Mac_Address, int);
    bool removeMacAddress(int);

    Mac_Address getPeer(int, NEIGHBOURING_NODE);


    std::vector<Mac_Address> mac_addresses = {
    // {0x7C, 0x9E, 0xBD, 0xF3, 0xDE, 0x0C}, // Marco Monitor
    {0xA0, 0xB7, 0x65, 0xDC, 0x34, 0xF0}, // Lisa
    {0x7C, 0x9E, 0xBD, 0xF4, 0x26, 0x94}, // Feng
    {0xCC, 0xDB, 0xA7, 0x3F, 0xC9, 0x50}, // Feng
    {0x94, 0xB9, 0x7E, 0xC0, 0x08, 0x6C}, // Marco
    {0xC8, 0xF0, 0x9E, 0x4E, 0x50, 0x64}, // Veselin
    {0x40, 0x22, 0xD8, 0x3B, 0xED, 0x38}, // Jovan
    };

    private:



};


#endif
