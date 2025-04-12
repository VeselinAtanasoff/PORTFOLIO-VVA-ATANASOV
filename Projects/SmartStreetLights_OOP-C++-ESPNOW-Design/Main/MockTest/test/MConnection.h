#ifndef MCONNECTION_H
#define MCONNECTION_H

#include <IConnection.h>
#include <gmock/gmock.h>

class MConnection : public IConnection
{
public:
    MOCK_METHOD1(SendData, void(Message));
    MOCK_METHOD0(GetSentStatus, bool());
};

#endif