#include <iostream>
#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

// Class
#include "Monitor.h"

Ui ui
Monitor monitor;
MonitorConnection *connection;
Message receivedMessage;
MacAddresses macAddresses;

void OnDataRecv(const uint8_t*, const uint8_t*, int);

void setup()
{
  Serial.begin(115200);
  connection = new MonitorConnection(OnDataRecv);
}

void loop()
{
  ui.printInstructions();

  int choice = 0;
  while (choice == 0) {
    choice = Serial.parseInt();
  }

  switch(choice) {
    case ADD_MAC_ADDRESS: {
      monitor.addMacAddress(&macAddresses);
      break;
    }

    case REMOVE_MAC_ADDRESS: {
      monitor.removeMacAddress(&macAddresses);
      break;
    }
    
    case SEND_MAC_ADDRESSES: {
      monitor.sendMacAddresses(&macAddresses);
    }
    break;
  }
}

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *current_data, int data_len)
{
  memcpy(&receivedMessage, current_data, sizeof(receivedMessage));

  Device device;
  
  memcpy(device.macAdress, mac_addr, sizeof(device.macAdress));

  device.message.messageType = receivedMessage.messageType;
  device.message.data = receivedMessage.data;

  ui.showError(device);
}


