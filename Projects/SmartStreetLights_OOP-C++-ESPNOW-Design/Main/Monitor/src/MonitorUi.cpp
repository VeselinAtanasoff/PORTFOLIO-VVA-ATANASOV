#include "MonitorUi.h"

void Ui::showError(Device device) {
  if (device.message.messageType == ERR) {
    Serial.println("********************************");
    Serial.print("WARNING: Error detected at Mac Address ");
    printMacAddress(device.macAdress);

    Serial.print("MESSAGE: ");

    switch(device.message.data) {
      case LEFT_ERROR_CODE:
        Serial.println("Node connection error at its left node.");
      break;

      case RIGHT_ERROR_CODE:
        Serial.println("Node connection error at its right node.");
      break;

      case HARDWARE_ERROR_CODE:
        Serial.println("Hardware error.");
      break;
    }
    Serial.println();
  }
}

void Ui::printInstructions() {
  Serial.println();
  Serial.printf("Press %d to add a Mac Address, %d to remove a Mac Address or %d to send all the Mac Address.\n\r", ADD_MAC_ADDRESS, REMOVE_MAC_ADDRESS, SEND_MAC_ADDRESSES);
  Serial.println();
}

void Ui::printInstructionsAddMacAddress() {
  Serial.printf("Type the Mac Adress followed by the position to send or type %s to go back.\n\r", GO_BACK);
  Serial.println("Layout: XX:XX:XX:XX:XX:XX X");
  Serial.println("Example: 7c:9e:bd:f3:de:0c 1");
  Serial.println();
}

void Ui::printInstructionsRemoveMacAddress() {
  Serial.printf("Type the index of the Mac Adress that you want to remove or type %s to go back.\n\r", GO_BACK);
  Serial.println();
}

void Ui::printMacAddresses(MacAddresses* macAddresses) {
  for (int i = 0; i < macAddresses->vectorMAs.size(); i++) {
    Serial.print("Index ");
    Serial.print(i);
    Serial.print(": ");
    uint8_t* MA = macAddresses->vectorMAs[i].MA;
    printMacAddress(MA);
  }
}

void Ui::printMacAddress(uint8_t* MA) {
  for (int i = 0; i < SIZE_MACADDRRESS; i++) {
    if (MA[i] >= 0 && MA[i] <= 15) {
      Serial.print("0");
    }

    Serial.print(String(MA[i], HEX));
    Serial.print(" ");
  }
  Serial.println();
  Serial.println("--------------------------------");
  Serial.println();
}

void Ui::showResult_checkReceived(int result) {
  switch(result) {
    case CORRECT:
    Serial.println("Mac Address and index are in the correct format.");
    break;

    case INCORRECT_LENGHT:
    Serial.println("Please enter a correct Mac Address and index.");
    Serial.println("Example: 7c:9e:bd:f3:de:0c 1"); 
    break;

    case INCORRECT_MAC_ADDRESS_FORMAT:
    case INCORRECT_COLON_MAC_ADDRESS:
    Serial.println("Please make sure that the Mac Address is formatted correctly.");
    Serial.println("Example: 7c:9e:bd:f3:de:0c 1");
    break;

    case INCORRECT_INT_FORMAT:
    Serial.println("Please make sure that the index is a number.");
    Serial.println("Example: 7c:9e:bd:f3:de:0c 1");
    break;

    Serial.println();
  }
}

void Ui::showResult_addMacAddress(bool result) {
  switch(result) {
    case true:
    Serial.println("The Mac Address has been added at the given index.");
    break;

    case false:
    Serial.println("The Mac Address already existed or is the monitor.");
    break;

    Serial.println();
  }
}

void Ui::showResult_removeMacAddress(int result) {
  switch(result) {
    case 1:
    Serial.println("The Mac Address with the given index has been removed.");
    break;

    case -1:
    Serial.println("Invalid index.");
    break;

    case 0:
    Serial.println("No Mac Addresses found.");
    break;

    Serial.println();
  }
}

