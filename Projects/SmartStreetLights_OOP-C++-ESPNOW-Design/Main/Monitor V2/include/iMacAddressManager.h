#ifndef IMACADDRESSMANAGER_H
#define IMACADDRESSMANAGER_H

// Helper
#include <vector>

// Enum
#include "eUserErrorCode.h"

// Struct
#include "MacAddress.h"
#include "PositionMac.h"

class iMacAddressManager {

public:
virtual ~iMacAddressManager() {};

virtual int AddMacAddress(Mac_Address, int) = 0;
virtual int RemoveMacAddress(int) = 0;

virtual std::vector<Mac_Address> GetVector() = 0;
virtual PositionMac GetPeers(Mac_Address) = 0;

};

#endif