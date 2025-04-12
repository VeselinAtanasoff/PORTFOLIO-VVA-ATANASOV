#ifndef MACADDRESS_H
#define MACADDRESS_H

#include <stdint.h>
#include <vector>

constexpr int SIZE_MACADDRESS = 6;

struct Mac_Address {
    uint8_t MA[SIZE_MACADDRESS];
    
};

#endif