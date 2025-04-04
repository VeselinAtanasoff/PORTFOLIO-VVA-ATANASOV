#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef ENCODER_H

bool encodeByte(uint8_t byte, uint8_t* parityTableArray, uint8_t* encodedByteLow, uint8_t* encodedByteHigh);

#endif 
