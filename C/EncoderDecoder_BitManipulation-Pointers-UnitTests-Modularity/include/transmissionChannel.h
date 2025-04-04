#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef TRANSMISSIONCHANNEL_H
#define TRANSMISSIONCHANNEL_H

bool transmitByte(uint8_t* byte, uint8_t flipPosition);

#endif