#ifndef UI_H
#define UI_H

constexpr int VALID_INT_SIZE = 10;
constexpr int VALID_HEX_SIZE = 22;

// Helper
#include <vector>
#include <iostream>
#include <string>
#include <bits/stdc++.h>

// Enum
#include "eUserErrorCode.h"

// Struct
#include "MacAddress.h"

// Class
#include "iDisplay.h"
#include "iMonitorConnection.h"
#include "iMacAddressManager.h"

class Ui {

public:
    Ui(iDisplay &display, iMonitorConnection &monitorConnection, iMacAddressManager &macAddressManager);

    virtual void Instructions(int);
    virtual int HandleAddMacAddress(char*);
    virtual int HandleRemoveMacAddress(char*);
    virtual void HandleSendMacAddresses(iMonitorConnection&, Mac_Address);
    virtual std::vector<Mac_Address> GetVector();

    void OnDataRecv(const uint8_t*, const uint8_t*);

private:
    int StringToInt(char*, int);
    int StringToMacAddress(char*, int, Mac_Address*);
    int HexstringToInt(char*, int);
    int LengthOf(char*);

    char validInt[VALID_INT_SIZE] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char validHexValue[VALID_HEX_SIZE] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                                          'A', 'a', 'B', 'b', 'C', 'c', 'D', 'd', 'E', 'e', 'F', 'f'};
    iDisplay &display;
    iMacAddressManager &macAddressManager;
    iMonitorConnection &monitorConnection;

};

#endif