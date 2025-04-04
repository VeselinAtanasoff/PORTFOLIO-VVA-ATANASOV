#include <stdio.h>  
#include <stdbool.h>
#include <stdint.h>
#include "transmissionChannel.h"

bool transmitByte(uint8_t* byte, uint8_t flipPosition)
{
    bool actionComplete = false;
    if (byte == NULL)
    {
    }
    else
    {
        if (flipPosition < 8)
        {
            *byte = *byte ^ (1 << flipPosition);
            actionComplete = true;
        }
    }

    return actionComplete;
}