#include <Arduino.h>
#include "connection.h"

Connection *connection;
uint8_t peerAddress[] = {0x94, 0xB9, 0x7E, 0xC0, 0x08, 0x6C};
//uint8_t peerAddress[] = {0xC8, 0xF0, 0x9E, 0x4E, 0x50, 0x64};
Message receivedMessage;
Message sendMessage;

void OnDataRecv(const uint8_t *mac, const uint8_t *data, int data_len)
{
  memcpy(&receivedMessage, data, sizeof(receivedMessage));
  Serial.println(receivedMessage.messageType);
  Serial.println(receivedMessage.data);
}

void setup()
{
  Serial.begin(115200);
  connection = new Connection(peerAddress, OnDataRecv);
}

void loop()
{
  sendMessage.messageType = LDR;
  sendMessage.data = 420;
  connection->SendData(sendMessage);
  Serial.println(connection->GetSentStatus());
  delay(500);
}
