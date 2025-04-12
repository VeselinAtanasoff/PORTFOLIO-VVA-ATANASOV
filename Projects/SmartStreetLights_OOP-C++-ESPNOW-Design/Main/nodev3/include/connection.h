#ifndef CONNECTIONCLASS_H
#define CONNECTIONCLASS_H

#include <Arduino.h>
#include <IConnection.h>
#include <WiFi.h>
#include <esp_now.h>

class Connection : public IConnection
{
public:
    Connection(uint8_t *peerMAC, void (*OnDataRecv)(const uint8_t *mac, const uint8_t *data, int data_len));
    void SendData(Message message) override;
    bool GetSentStatus() override;
    void RemovePeer();
    void AddPeer(const uint8_t *mac_addr);
private:
    uint8_t peerMAC[6];
    esp_now_peer_info_t peerInfo;

    static void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
};

#endif