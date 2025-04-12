#ifndef MMACADDRESSMANAGER_H
#define MMACADDRESSMANAGER_H

#include <iMacAddressManager.h>
#include <gmock/gmock.h>

class mMacAddressManager : public iMacAddressManager {

public:
MOCK_METHOD2(AddMacAddress, int(Mac_Address, int));
MOCK_METHOD1(RemoveMacAddress, int(int));

MOCK_METHOD0(GetVector, std::vector<Mac_Address>());
MOCK_METHOD1(GetPeers, PositionMac(Mac_Address));

};

#endif