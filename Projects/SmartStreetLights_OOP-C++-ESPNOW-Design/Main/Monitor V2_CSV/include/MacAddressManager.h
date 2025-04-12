#ifndef MACADDRESSMANAGER_H
#define MACADDRESSMANAGER_H

#include "iMacAddressManager.h"
#include "MacAddress.h"
#include <vector>

class MacAddressManager : public iMacAddressManager {

public:
MacAddressManager();
int AddMacAddress(Mac_Address, int) override;
int RemoveMacAddress(int) override;
std::vector<Mac_Address> GetVector() override;
PositionMac GetPeers(Mac_Address) override;

private:
void ChangeVectorWithFile() override;
void ChangeFileWithVector() override;

const std::string csvFilePath = "/mac_addresses.csv";
Mac_Address monitor = {0x7C, 0x9E, 0xBD, 0xF3, 0xDE, 0x0C};
std::vector<Mac_Address> vectorMAs = {
    // {0xC8, 0xF0, 0x9E, 0x4E, 0x50, 0x64}, // Veselin
    {0xA0, 0xB7, 0x65, 0xDC, 0x34, 0xF0}, // Lisa
    {0x40, 0x22, 0xD8, 0x3B, 0xED, 0x38}, // Jovan
    {0x94, 0xB9, 0x7E, 0xC0, 0x08, 0x6C}, // Marco
    // {0xCC, 0xDB, 0xA7, 0x3F, 0xC9, 0x50}, // Feng
    // {0x7C, 0x9E, 0xBD, 0xF4, 0x26, 0x94}, // Feng
    // {0x24, 0x0A, 0xC4, 0x60, 0xE3, 0xC4}, // Jovan
    };
    
};

#endif