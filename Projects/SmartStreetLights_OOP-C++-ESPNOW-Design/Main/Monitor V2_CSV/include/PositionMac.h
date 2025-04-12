#ifndef POSITIONMAC_H
#define POSITIONMAC_H

// Struct
#include "MacAddress.h"

struct PositionMac {
    uint8_t left[SIZE_MACADDRESS];
    uint8_t right[SIZE_MACADDRESS];
};

#endif