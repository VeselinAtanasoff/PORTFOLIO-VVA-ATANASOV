#include <Arduino.h>
#include "connection.h"

uint8_t myPWR = 10;

// 40:22:d8:3b:ed:38 *3
// 0xC8, 0xF0, 0x9E, 0x4E, 0x50, 0x64 *2
// 0x94, 0xB9, 0x7E, 0xC0, 0x08, 0x6C *1

uint8_t peerAddressLeft[] = {0x40, 0x22, 0xD8, 0x3B, 0xED, 0x38};
uint8_t peerAddressRight[] = {0xC8, 0xF0, 0x9E, 0x4E, 0x50, 0x64};
Connection *leftPeerConnection;
Connection *rightPeerConnection;
Message receivedMessage;
Message sendMessage;

void OnDataRecv(const uint8_t *mac, const uint8_t *data, int data_len)
{
  memcpy(&receivedMessage, data, sizeof(receivedMessage));

  if ((receivedMessage.data) == 10)
  {
    myPWR = receivedMessage.data;
  }
  else if (receivedMessage.data >= myPWR)//The power is updated based on the message received, if the data of the message 
                                        //is less or equal to the current power, current power will not change
  {
    myPWR = (receivedMessage.data) - 25;
    sendMessage.data = myPWR;
    leftPeerConnection->SendData(sendMessage);
    rightPeerConnection->SendData(sendMessage);//This node also sends its power to the neighbouring nodes if a message is received
  }
}

void setup()
{
  Serial.begin(115200);
  leftPeerConnection = new Connection(peerAddressLeft, &OnDataRecv);//Neighbour connections are initialized here
  rightPeerConnection = new Connection(peerAddressRight, &OnDataRecv);
}

void loop()
{
  sendMessage.messageType = PWR;
  if (Serial.available())//The serial messages simulate power data in the talking skeleton
  {
    myPWR = Serial.parseInt();
    sendMessage.data = myPWR;
    if (myPWR != 10)
    {
      leftPeerConnection->SendData(sendMessage);
      rightPeerConnection->SendData(sendMessage);
    }
  }

  if (myPWR <= 10)
  {
    myPWR = 10;
  }

  Serial.printf("My brightness: %d\r", myPWR);
}
