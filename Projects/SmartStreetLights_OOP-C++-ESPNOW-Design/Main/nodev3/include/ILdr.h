#ifndef ILDR_H
#define ILDR_H

#include <Arduino.h>

class ILdr
{
public:
  virtual int ReadLightLevel() = 0;
};

#endif