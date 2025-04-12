#ifndef IMONITOR_H
#define IMONITOR_H

#include <iostream>
#include <stdint.h>
#include <WiFi.h>
#include <esp_now.h>

// Classes
#include "MacAddresses.h"
#include "MonitorUi.h"
#include "MonitorConnection.h"

class IMonitor {

    public:

    virtual bool charIsCorrectInt(char) = 0;
    virtual void addMacAddress(MacAddresses*) = 0;
    virtual void removeMacAddress(MacAddresses*) = 0;
    virtual void sendMacAddresses(MacAddresses*) = 0;


    private:

    virtual bool charIsCorrectHexFormat(char) = 0;

};

#endif