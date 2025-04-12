#ifndef MMONITORCONNECTION_H
#define MMONITORCONNECTION_H

#include <iMonitorConnection.h>
#include <gmock/gmock.h>

class mMonitorConnection : public iMonitorConnection
{
public:
    MOCK_METHOD1(SendData, void(PositionMac));
};

#endif