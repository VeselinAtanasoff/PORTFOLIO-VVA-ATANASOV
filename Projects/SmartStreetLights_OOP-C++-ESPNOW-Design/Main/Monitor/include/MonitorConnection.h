#ifndef MONITORCONNECTION_H
#define MONITORCONNECTION_H

#include <WiFi.h>
#include <esp_now.h>

#include "IMonitorConnection.h"

class MonitorConnection : public IMonitorConnection
{
public:
    MonitorConnection(uint8_t*);
    MonitorConnection( void (*OnDataRecv)(const uint8_t *mac, const uint8_t *data, int data_len));

    void SendData(PositionMac) override;

private:
    uint8_t peerMAC[6];
    esp_now_peer_info_t peerInfo;
    
    static void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
};

#endif