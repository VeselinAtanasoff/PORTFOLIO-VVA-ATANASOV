#include <Arduino.h>
#include "connection.h"

// 40:22:d8:3b:ed:38 *3
// 0xC8, 0xF0, 0x9E, 0x4E, 0x50, 0x64 *2
// 0x94, 0xB9, 0x7E, 0xC0, 0x08, 0x6C *1

uint8_t monitorMA[] = {0x7c, 0x9e, 0xbd, 0xf3, 0xde, 0x0c};
Connection* monitor;
PositionMac receivedMessage;
Message sendMessage;


void OnDataRecv(const uint8_t *mac, const uint8_t *data, int data_len)
{
  memcpy(&receivedMessage, data, sizeof(receivedMessage));

  for(int i = 0; i < 6; i++) {
    Serial.print(receivedMessage.most_left[i], HEX);
    Serial.print(";");
  }
  Serial.println();

  for(int i = 0; i < 6; i++) {
    Serial.print(receivedMessage.left[i], HEX);
    Serial.print(";");
  }
  Serial.println();

  if (receivedMessage.right == 0) {
    Serial.println("0");
  }
  else{
    for(int i = 0; i < 6; i++) {
      Serial.print(receivedMessage.right[i], HEX);
      Serial.print(";");
    }
    Serial.println();
  }

  for(int i = 0; i < 6; i++) {
    Serial.print(receivedMessage.most_right[i], HEX);
    Serial.print(";");
  }
  Serial.println();

  Serial.println();

}

void setup()
{
  Serial.begin(115200);
  monitor = new Connection(monitorMA, OnDataRecv);//Neighbour connections are initialized here
}

void loop()
{
  // sendMessage.messageType = ERR;
  // sendMessage.data = 0;

  // monitor->SendData(sendMessage);
}
