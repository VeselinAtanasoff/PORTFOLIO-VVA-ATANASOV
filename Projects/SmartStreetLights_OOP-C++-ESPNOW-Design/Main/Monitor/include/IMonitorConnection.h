#ifndef IMONITORCONNECTION_H
#define IMONITORCONNECTION_H

// Helper
#include <iostream>
#include <stdint.h>
#include <esp_now.h>
#include <vector>

// Struct
#include "PositionMac.h"
#include "MacAddress.h"

class IMonitorConnection
{
public:
    virtual void SendData(PositionMac);
};

#endif