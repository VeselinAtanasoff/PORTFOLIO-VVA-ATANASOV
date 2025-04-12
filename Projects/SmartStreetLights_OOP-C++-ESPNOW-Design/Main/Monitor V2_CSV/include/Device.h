#ifndef DEVICE_H
#define DEVICE_H

// Struct
#include "MacAddress.h"
#include "Message.h"

struct Device {
    Mac_Address macAddress;
    Message message;
};

#endif