#ifndef ICONNECTION_H
#define ICONNECTION_H

#include <stdint.h>
#include <iostream>

enum msgType
{
    LDR, PWR, ERR
};

struct Message
{
    msgType messageType;
    uint16_t data;
};

class IConnection
{
public:
    virtual ~IConnection(){};
    virtual void SendData(Message message) = 0;
    virtual bool GetSentStatus() = 0;

};

#endif