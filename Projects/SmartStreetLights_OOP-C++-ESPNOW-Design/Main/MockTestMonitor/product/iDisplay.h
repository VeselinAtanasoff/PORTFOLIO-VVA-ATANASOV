#ifndef IDISPLAY_H
#define IDISPLAY_H

// Helper
#include <vector>

// Struct
#include "Device.h"
#include "MacAddress.h"

// Enum
#include "eUserErrorCode.h"
#include "eErrorCode.h"


class iDisplay {

public:
    virtual ~iDisplay() {};

    virtual void showAllMacAddresses(std::vector<Mac_Address>) = 0;
    virtual void showMacAddress(Mac_Address) = 0;
    virtual void showInstructionMainMenu() = 0;
    virtual void showInstructionAddMacAddress() = 0;
    virtual void showResultAddMacAddress(int) = 0;
    virtual void showInstructionRemoveMacAddress() = 0;
    virtual void showResultRemoveMacAddress(int) = 0;
    virtual void showResultSendMacAddresses(Mac_Address) = 0;
    virtual void showErrorCode(Device) = 0;

};

#endif