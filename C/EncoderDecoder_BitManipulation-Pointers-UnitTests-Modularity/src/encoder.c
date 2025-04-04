#include "encoder.h"

bool encodeByte(uint8_t byte, uint8_t *parityTableArray, uint8_t* encodedByteLow, uint8_t* encodedByteHigh)
{
    bool actionComplete = false;
    if (parityTableArray == NULL || encodedByteLow == NULL || encodedByteHigh == NULL)
    {
       
    }
    else
    {
        uint8_t lowNibble = byte & 0b00001111;
        uint8_t highNibble = ((byte & 0b11110000) >> 4);

        *encodedByteLow = parityTableArray[lowNibble];
        *encodedByteHigh = parityTableArray[highNibble];

        actionComplete = true;
    }

    return actionComplete;
}
