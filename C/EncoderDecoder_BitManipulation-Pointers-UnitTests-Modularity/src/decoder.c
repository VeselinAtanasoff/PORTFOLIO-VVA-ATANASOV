#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "decoder.h"

bool decodeByte(uint8_t transmittedByteHigh, uint8_t transmittedByteLow, uint8_t *parityTableArray, uint8_t *decodedByte)
{
    bool actionComplete = false;
    if (decodedByte == NULL || parityTableArray == NULL)
    {
    }
    else
    {
        uint8_t decodedNibbleHigh;
        uint8_t decodedNibbleLow;

        if (decodeNibble(transmittedByteHigh, parityTableArray, &decodedNibbleHigh) && decodeNibble(transmittedByteLow, parityTableArray, &decodedNibbleLow)){
            *decodedByte = (decodedNibbleHigh << 4) | decodedNibbleLow;
            actionComplete = true;
        }
    }

    return actionComplete;
}

bool decodeNibble(uint8_t transmittedNibble, uint8_t *parityTableArray, uint8_t *decodedNibble)
{
    bool actionComplete = false;
    if (decodedNibble == NULL || parityTableArray == NULL)
    {
    }
    else
    {
        uint8_t calculatedPb0 = parityTableArray[(transmittedNibble >> 3) & 0b1111] & 0b00000001;
        uint8_t calculatedPb1 = (parityTableArray[(transmittedNibble >> 3) & 0b1111] & 0b00000010) >> 1;
        uint8_t calculatedPb2 = (parityTableArray[(transmittedNibble >> 3) & 0b1111] & 0b00000100) >> 2;
        uint8_t receivedPb0 = transmittedNibble & 0b00000001;
        uint8_t receivedPb1 = (transmittedNibble & 0b00000010) >> 1;
        uint8_t receivedPb2 = (transmittedNibble & 0b00000100) >> 2;

        if ((transmittedNibble & 0b10000000) > 0)
        {
            *decodedNibble = (transmittedNibble ^ 0b10000000) >> 3;
        }
        else if (receivedPb0 == calculatedPb0 && receivedPb1 == calculatedPb1 && receivedPb2 == calculatedPb2)
        {
            *decodedNibble = transmittedNibble >> 3;
        }
        else if (receivedPb0 != calculatedPb0 && receivedPb1 != calculatedPb1 && receivedPb2 != calculatedPb2)
        {
            *decodedNibble = (transmittedNibble >> 3) ^ 0b00000010;
        }
        else if (receivedPb0 != calculatedPb0 && receivedPb1 != calculatedPb1)
        {
            *decodedNibble = (transmittedNibble >> 3) ^ 0b00000001;
        }
        else if (receivedPb0 != calculatedPb0 && receivedPb2 != calculatedPb2)
        {
            *decodedNibble = (transmittedNibble >> 3) ^ 0b00000100;
        }
        else if (receivedPb1 != calculatedPb1 && receivedPb2 != calculatedPb2)
        {
            *decodedNibble = (transmittedNibble >> 3) ^ 0b00001000;
        }
        else
        {
            *decodedNibble = transmittedNibble >> 3;
        }
        actionComplete = true;
    }
    return actionComplete;
}