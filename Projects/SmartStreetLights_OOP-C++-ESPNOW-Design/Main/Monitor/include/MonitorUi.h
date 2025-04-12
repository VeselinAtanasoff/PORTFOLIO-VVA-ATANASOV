#ifndef MONITORUI_H
#define MONITORUI_H

#include <iostream>
#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

// Class
#include "MacAddresses.h"

// Struct
#include "Device.h"

// Enum
#include "EUserInput.h"
#include "EResultAddMacAddress.h"
#include "EErrorCode.h"

constexpr char GO_BACK[5] = "BACK";

class Ui {
    public:
    void showError(Device);
    void printInstructions();
    void printInstructionsAddMacAddress();
    void printInstructionsRemoveMacAddress();

    void printMacAddresses(MacAddresses*);
    void printMacAddress(uint8_t*);

    void showResult_checkReceived(int);
    void showResult_addMacAddress(bool);
    void showResult_removeMacAddress(int);
};


#endif