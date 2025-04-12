#include <fstream>
#include <sstream>
#include <iostream>
#include "MacAddressManager.h"
#include <algorithm> // std::find
#include <iterator>  //  std::distance
#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>

MacAddressManager::MacAddressManager()
{
     Serial.println("Initializing MacAddressManager...");
    ChangeVectorWithFile();
     Serial.println("Initialization complete.");
}
int MacAddressManager::AddMacAddress(Mac_Address mac, int position)

{
    //ChangeVectorWithFile();

    if (position < 0 || position > static_cast<int>(vectorMAs.size()))
    {
        return INVALID_POSITION; // invalid position
    }

    // if the MAC address already exists or matches the monitor address
    for (const auto &existingMac : vectorMAs)
    {
        if (std::equal(std::begin(existingMac.MA), std::end(existingMac.MA), std::begin(mac.MA)) ||
            std::equal(std::begin(monitor.MA), std::end(monitor.MA), std::begin(mac.MA)))
        {
            return DUPLICATE_MAC_ADDRESS; // MAC address is duplicate or matches monitor
        }
    }
    vectorMAs.insert(vectorMAs.begin() + position, mac);
    ChangeFileWithVector();
    // Serial.println("CSV file updated successfully. ADD");

    return CORRECT; // success
}

int MacAddressManager::RemoveMacAddress(int position)
{
    if (position < 0 || position >= static_cast<int>(vectorMAs.size()))
    {
        return INVALID_POSITION;
    }
    vectorMAs.erase(vectorMAs.begin() + position);
    ChangeFileWithVector();
    // Serial.println("CSV file updated successfully. REM");

    return CORRECT;
}

std::vector<Mac_Address> MacAddressManager::GetVector()
{
    return vectorMAs;
}

PositionMac MacAddressManager::GetPeers(Mac_Address mac)
{
    PositionMac peers = {};

    // find the position
    auto it = std::find_if(vectorMAs.begin(), vectorMAs.end(), [&](const Mac_Address &addr)
                           { return std::equal(std::begin(addr.MA), std::end(addr.MA), std::begin(mac.MA)); });

    if (it == vectorMAs.end())
    {
        return peers;
    }

    int index = std::distance(vectorMAs.begin(), it);

    if (index > 0)
    {
        std::copy(std::begin(vectorMAs[index - 1].MA), std::end(vectorMAs[index - 1].MA), peers.left);
    }
    if (index < static_cast<int>(vectorMAs.size()) - 1)
    {
        std::copy(std::begin(vectorMAs[index + 1].MA), std::end(vectorMAs[index + 1].MA), peers.right);
    }
    /* if (!vectorMAs.empty())
     {
         std::copy(std::begin(vectorMAs.front().MA), std::end(vectorMAs.front().MA), peers.most_left);
         std::copy(std::begin(vectorMAs.back().MA), std::end(vectorMAs.back().MA), peers.most_right);
     }*/

    return peers;
}

void MacAddressManager::ChangeVectorWithFile()
{
    vectorMAs.clear(); // Clear the current vector


  if (!LittleFS.exists(csvFilePath.c_str())) {
        Serial.println("CSV file does not exist. Initializing with default MAC addresses.");
        return;
    }

    File file = LittleFS.open(csvFilePath.c_str(), "r"); // Change to SPIFFS.open if using SPIFFS
    if (!file)
    {
        Serial.println("Could not open CSV file. Using default MAC addresses.");
        return;
    }

    String line;
    while (file.available())
    {
        line = file.readStringUntil('\n');
        String byteStr;
        Mac_Address mac;
        int i = 0;

        for (int j = 0; j < line.length(); j++)
        {
            if (line[j] == ',' || j == line.length() - 1)
            {
                mac.MA[i++] = static_cast<uint8_t>(strtol(byteStr.c_str(), nullptr, 16));
                byteStr = "";
            }
            else
            {
                byteStr += line[j];
            }
        }

        if (i == 6)
        {
            vectorMAs.push_back(mac);
        }
    }

    file.close();
    Serial.println("Vector updated from file:");
    for (const auto& mac : vectorMAs) {
        for (int i = 0; i < 6; ++i) {
            Serial.printf("%02X", mac.MA[i]);
            if (i < 5) Serial.print(":");
        }
        Serial.println();
    }
}

void MacAddressManager::ChangeFileWithVector()
{
    File file = LittleFS.open(csvFilePath.c_str(), "w"); // Change to SPIFFS.open if using SPIFFS
    if (!file)
    {
        Serial.println("Could not open CSV file for writing.");
        return;
    }

    for (const auto &mac : vectorMAs)
    {
        for (int i = 0; i < 6; ++i)
        {
            file.printf("%02X", mac.MA[i]);
            if (i < 5)
                file.print(",");
        }
        file.println();
    }

    file.close();
}
