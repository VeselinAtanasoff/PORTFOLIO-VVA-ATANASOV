#ifndef CONNECTIONCLASS_H
#define CONNECTIONCLASS_H

#include <iostream>
#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

enum msgType
{
    LDR, PWR, ERR
};

struct Message
{
    msgType messageType;
    uint16_t data;
};

class Connection
{
public:
    Connection(uint8_t *peerMAC, void (*OnDataRecv)(const uint8_t *mac, const uint8_t *data, int data_len));
    void SendData(Message message);
    bool GetSentStatus();

private:
    uint8_t peerMAC[6];
    esp_now_peer_info_t peerInfo;

    static void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
};

#endif