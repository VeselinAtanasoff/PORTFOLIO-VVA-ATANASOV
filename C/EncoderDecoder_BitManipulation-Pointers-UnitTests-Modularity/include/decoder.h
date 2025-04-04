#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#ifndef ENCODER_H
#define ENCODER_H

bool decodeByte(uint8_t transmittedByteHigh, uint8_t transmittedByteLow, uint8_t* parrityTableArray, uint8_t* decodedByte);
bool decodeNibble(uint8_t transmittedNibble, uint8_t *parityTableArray, uint8_t *decodedNibble);

#endif