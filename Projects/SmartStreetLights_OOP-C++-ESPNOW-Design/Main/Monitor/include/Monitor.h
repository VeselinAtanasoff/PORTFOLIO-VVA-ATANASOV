#ifndef MONITOR_H
#define MONITOR_H

#include <iostream>
#include <stdint.h>
#include <WiFi.h>
#include <esp_now.h>

#include <Arduino.h>

#include "IMonitor.h"

constexpr int POS_OF_SPACE = 17;
constexpr int POS_OF_COLON = 2;
constexpr int LENGHT_OF_MAC = 17;


class Monitor : public IMonitor {

    public:

    int checkReceived(String, Mac_Address*, int*);
    bool charIsCorrectInt(char) override;
    void addMacAddress(MacAddresses*) override;
    void removeMacAddress(MacAddresses*) override;
    void sendMacAddresses(MacAddresses*) override;


    private:

    int checkMacAddress(String, Mac_Address*);
    bool charIsCorrectHexFormat(char) override;
    int convertHexstringToInt(String);

};

#endif