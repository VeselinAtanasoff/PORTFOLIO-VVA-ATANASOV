#include "node.h"

Node::Node(int myIndex)
{
    int myMAC = myIndex;
}

/*
Prints all Mac Addresses
*/
void Node::printMacAddresses()
{
    Serial.println(mac_address.size());
    for (const auto &mac : mac_address)
    {
        for (size_t i = 0; i < 6; i++)
        {
            if (mac.mac_address[i] <= 0x0F)
            {
                Serial.print("0");
            }
            Serial.print(mac.mac_address[i], HEX);
            if (i < 5)
            {
                Serial.print(":");
            }
        }
        Serial.println();
    }
}

/*
Checks if MacAddress exist, if yes then gets the index
*/
uint8_t Node::checkMacAddress()
{
    int8_t found = -1;
    uint8_t lookMac[6];
    esp_read_mac(lookMac, ESP_MAC_WIFI_STA);

    for (int i = 0; i < mac_address.size(); i++)
    {
        for (int j = 0; j < MACADDRESSLENGTH; j++)
        {
            if (mac_address[i].mac_address[j] == lookMac[j])
            {
                found = i;
                break;
            }
            else
            {
                break;
            }
        }
    }

    if (found >= 0)
    {
        Serial.print("index: ");
        Serial.println(found);
        return found;
    }

    Serial.print("This address does not exist");
    return found;
}

/*
Find left peer
*/
void Node::leftPeerMac(int macIndex)
{

    for (int i = 0; i < MACADDRESSLENGTH; i++)
    {
        if (macIndex == 0) // The first index
        {
            Serial.println("no peers to the left");
            return;
        }

        Serial.print(mac_address[macIndex - 1].mac_address[i], HEX);
        if (i < 5)
        {
            Serial.print(":");
        }
    }
}

/*
Find right peer
*/
void Node::rightPeerMac(int macIndex)
{
    for (int i = 0; i < MACADDRESSLENGTH; i++)
    {
        if (macIndex == (mac_address.size() - 1))
        {
            Serial.println("no peers to the right");
            return;
        }

        Serial.print(mac_address[macIndex + 1].mac_address[i], HEX);
        if (i < 5)
        {
            Serial.print(":");
        }
    }
}

void Node::mostLeftPeerMac(int macIndex)
{
    for (int i = 0; i < MACADDRESSLENGTH; i++)
    {
        if (macIndex == 0 || macIndex == 1)
        {
            Serial.println("no peers to the right");
            return;
        }

        Serial.print(mac_address[macIndex + 1].mac_address[i], HEX);
        if (i < 5)
        {
            Serial.print(":");
        }
    }
}

void Node::mostRightPeerMac(int macIndex)
{
    for (int i = 0; i < MACADDRESSLENGTH; i++)
    {
        if (macIndex == (mac_address.size() - 1) || macIndex == (mac_address.size() - 2))
        {
            Serial.println("no peers to the right");
            return;
        }

        Serial.print(mac_address[macIndex + 1].mac_address[i], HEX);
        if (i < 5)
        {
            Serial.print(":");
        }
    }
}