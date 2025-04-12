#ifndef IMACADDRESSES_H
#define IMACADDRESSES_H

#include <stdint.h>
#include <vector>

// Struct
#include "MacAddress.h"

// Class
#include "ENeighbouringNode.h"

class IMacAddresses
{
    public:
    
    virtual bool addMacAddress(Mac_Address, int) = 0;
    virtual int removeMacAddress(int) = 0;
    virtual uint8_t getPeer(NEIGHBOURING_NODE, int, int) = 0;

};


#endif
