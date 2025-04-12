#include "MonitorConnection.h"

bool sentStatus;

MonitorConnection::MonitorConnection(void (*OnDataRecv)(const uint8_t *mac, const uint8_t *data, int data_len))
{
    WiFi.mode(WIFI_STA);
    
    esp_err_t initResult = esp_now_init();
    while (initResult != ESP_OK)
    {
        Serial.println("ESP-NOW initialization failed. Retrying...");
        delay(1000);
        initResult = esp_now_init();
    }

    esp_now_register_recv_cb(OnDataRecv);
    
}

MonitorConnection::MonitorConnection(uint8_t *peerMAC) {

    WiFi.mode(WIFI_STA);
    for (int i = 0; i < 6; i++)
    {
        this->peerMAC[i] = peerMAC[i];
    };
    
    esp_err_t initResult = esp_now_init();
    while (initResult != ESP_OK)
    {
        Serial.println("ESP-NOW initialization failed. Retrying...");
        delay(1000);
        initResult = esp_now_init();
    }
    esp_now_register_send_cb(OnDataSent);

    memset(&peerInfo, 0, sizeof(peerInfo)); // Zero out struct to ensure clean initialization
    memcpy(peerInfo.peer_addr, peerMAC, 6);
    peerInfo.channel = 1; // Set the Wi-Fi channel (use the correct channel here)
    peerInfo.encrypt = false;
    peerInfo.ifidx = (wifi_interface_t)ESP_IF_WIFI_STA; // Specify the interface
    try
    {
        esp_err_t addPeerResult = esp_now_add_peer(&peerInfo);

    }    
    catch(const std::exception& e)
    {    }
    
}

void MonitorConnection::OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    sentStatus = status;
}

void MonitorConnection::SendData(PositionMac message)
{
    esp_err_t result = esp_now_send(this->peerMAC, (uint8_t*)&message, sizeof(message));
}

