#ifndef MACADDRESS_H
#define MACADDRESS_H

#include <stdint.h>

constexpr int SIZE_MACADDRRESS = 6;

struct Mac_Address {
    uint8_t MA[SIZE_MACADDRRESS];
};

#endif