#ifndef IMONITORCONNECTION_H
#define IMONITORCONNECTION_H

// Helper
#include <stdint.h>

// Struct
#include "PositionMac.h"
#include "MacAddress.h"

class iMonitorConnection
{
public:
    virtual ~iMonitorConnection() {};

    virtual void SendData(PositionMac) = 0;
};

#endif