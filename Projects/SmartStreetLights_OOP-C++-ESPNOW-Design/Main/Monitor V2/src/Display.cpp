#include "Display.h"
#include <Arduino.h>
#include <ui.h>
#include <eUserErrorCode.h>
#include "MacAddress.h"

Display::Display(){
}

void Display::showAllMacAddresses(std::vector<Mac_Address> macAddresses){
    for (int i = 0; i < macAddresses.size(); i++) {
        Serial.print("Index ");
        Serial.print(i);
        Serial.print(": ");
        showMacAddress(macAddresses.at(i));
    }
}

void Display::showMacAddress(Mac_Address macAddress) {
    for (int i = 0; i < SIZE_MACADDRESS; i++) {
        if (macAddress.MA[i] >= 0 && macAddress.MA[i] <= 15) {
        Serial.print("0");
        }

        Serial.print(String(macAddress.MA[i], HEX));
        Serial.print(" ");
    }
    Serial.println();
    Serial.println("--------------------------------");
    Serial.println();
}

void Display::showInstructionMainMenu() {
  Serial.print("Enter ");
  Serial.print(ADD_MAC_ADDRESS);
  Serial.print(" to Add a Mac Address, enter ");
  Serial.print(REMOVE_MAC_ADDRESS);
  Serial.print(" to Remove a Mac Address, enter ");
  Serial.print(SEND_MAC_ADDRESSES);
  Serial.print(" to Send all Mac Addresses, enter ");
  Serial.print(SHOW_LIST);
  Serial.print(" to show all the Mac Addresses or enter ");
  Serial.print(GO_BACK);
  Serial.println(" to go back to the Main Menu.");
}

void Display::showInstructionAddMacAddress() {
  Serial.print("Enter the Mac Address and Index that you want to add. Enter ");
  Serial.print(GO_BACK);
  Serial.println(" once you want to return to main.");
  Serial.println("Example: 0A:1B:2C:3D:4E:5F 2");
  Serial.println();
}

void Display::showResultAddMacAddress(int result) {
    switch(result) {
        case CORRECT:
        Serial.println("The Mac Address has been added at the given index.");
        break;

        case INCORRECT_STRING_TO_INT:
        Serial.println("The string is not converted to int properly.");
        break;

        case INCORRECT_HEXSTRING_TO_INT:
        Serial.println("The hex string is not converted to int properly.");
        break;

        case INVALID_POSITION:
        Serial.println("Please enter a valid index.");
        break;

        case DUPLICATE_MAC_ADDRESS:
        Serial.println("This Mac Address already exists.");
        break;

        Serial.println();
    }
}

void Display::showInstructionRemoveMacAddress() {
  Serial.print("Enter the Index of the Mac Address you want to remove. Enter ");
  Serial.print(GO_BACK);
  Serial.println(" once you want to return to main.");
  Serial.println();
}

void Display::showResultRemoveMacAddress(int result) {
    switch(result) {
        case CORRECT:
        Serial.println("The Mac Address with the given index has been removed.");
        break;

        case INVALID_POSITION:
        Serial.println("Invalid index or no Mac Addresses found.");
        break;

        

        Serial.println();
    }
}

void Display::showResultSendMacAddresses(Mac_Address mac) {
  Serial.println("Peers sent to: ");
  showMacAddress(mac);
}

void Display::showErrorCode(Device device) {
    if (device.message.messageType == ERR) {
    Serial.println("********************************");
    Serial.print("WARNING: Error detected at Mac Address ");
    showMacAddress(device.macAddress);

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