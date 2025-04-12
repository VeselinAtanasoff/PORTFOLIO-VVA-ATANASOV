#ifndef POSITIONMAC_H
#define POSITIONMAC_H

// Struct
#include "MacAddress.h"

struct PositionMac {
    uint8_t most_left[SIZE_MACADDRRESS];
    uint8_t left[SIZE_MACADDRRESS];
    uint8_t right[SIZE_MACADDRRESS];
    uint8_t most_right[SIZE_MACADDRRESS];
};

#endif