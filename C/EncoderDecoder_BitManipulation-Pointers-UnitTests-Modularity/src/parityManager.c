#include "parityManager.h"

bool fillParityTable(uint8_t *parityTableArray)
{
    bool actionComplete = false;
    if (parityTableArray == NULL)
    {
    }
    else
    {
        uint8_t parityBit0;
        uint8_t parityBit1;
        uint8_t parityBit2;
        for (uint8_t i = 0; i < NIBBLES; i++)
        {
            parityBit0 = (i & 0b0001) ^ ((i & 0b0010) >> 1) ^ ((i & 0b0100) >> 2);
            parityBit1 = (i & 0b0001) ^ ((i & 0b0010) >> 1) ^ ((i & 0b1000) >> 3);
            parityBit2 = ((i & 0b0010) >> 1) ^ ((i & 0b0100) >> 2) ^ ((i & 0b1000) >> 3);
            *parityTableArray = (i << 3) | (parityBit2 << 2) | (parityBit1 << 1) | parityBit0;
            parityTableArray++;
            
        }
        actionComplete = true;
    }
    return actionComplete;
}
