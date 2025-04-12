#include <Arduino.h>
#include "node.h"

Node *node = new Node(0);

void setup()
{
  Serial.begin(115200);

  node->printMacAddresses();
  uint8_t macIndex = node->checkMacAddress();
  Serial.print("This is the left peer: ");
  node->leftPeerMac(macIndex);
  Serial.print("This is the right peer: ");
  node->rightPeerMac(macIndex);
}

void loop()
{
  // put your main code here, to run repeatedly:
}
