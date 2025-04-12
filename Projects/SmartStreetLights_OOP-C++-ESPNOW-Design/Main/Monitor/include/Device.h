#ifndef DEVICE_H
#define DEVICE_H

// Struct
#include "MacAddress.h"
#include "Message.h"

struct Device {
    uint8_t macAdress[SIZE_MACADDRRESS];
    Message message;
};

#endif