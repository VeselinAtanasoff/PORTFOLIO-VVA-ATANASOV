#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdint.h>

// Enum
#include "EMessageType.h"

struct Message {
  msgType messageType;
  uint16_t data;
}; 

#endif