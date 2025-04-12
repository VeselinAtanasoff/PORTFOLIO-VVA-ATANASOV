#include "Monitor.h"

int Monitor::checkReceived(String received, Mac_Address *MA, int *index) {
  int posOfSpace = received.indexOf(" ");

  if (posOfSpace != POS_OF_SPACE) {
    return INCORRECT_LENGHT;
  }

  String macAdr = received.substring(0, posOfSpace);
  int result = checkMacAddress(macAdr, MA);
  if (result != CORRECT) {
    return result;
  }

  String str = received.substring((posOfSpace+1));
  for (int i = 0; i < str.length(); i++) {
    if (!charIsCorrectInt(str[i])) {
      return INCORRECT_INT_FORMAT;
    }
  }
  *index = str.toInt();

  return CORRECT;
}

bool Monitor::charIsCorrectInt(char ch) {
  char intValues[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':'};
  int arrayLenght = sizeof(intValues)/sizeof(intValues[0]);
  for (int i = 0; i < arrayLenght; i++) {
    if (ch == intValues[i]) {
      return true;
    }
  }
  return false;
}

void Monitor::addMacAddress(MacAddresses* macAddresses) {
  bool valid_answer = false;
  int index;
  Mac_Address ma;
  Ui ui;

  ui.printInstructionsAddMacAddress();

  while(!valid_answer) {

    String received = "";
    while(received == "") {
      received = Serial.readString();
    }

    if (received == GO_BACK) {
      break;
    } 

    int resultCheck = checkReceived(received, &ma, &index);
    ui.showResult_checkReceived(resultCheck);

    bool resultAdd = macAddresses->addMacAddress(ma, index);
    ui.showResult_addMacAddress(resultAdd);

    if (resultAdd) {
      valid_answer = true;
      ui.printMacAddresses(macAddresses);
    }
  }
}

void Monitor::removeMacAddress(MacAddresses* macAddresses) {
  Ui ui;
  bool valid_answer = false;

  if (macAddresses->vectorMAs.size() == 0) {
    ui.showResult_removeMacAddress(macAddresses->vectorMAs.size());
  }
  else {
    ui.printInstructionsRemoveMacAddress();
    ui.printMacAddresses(macAddresses);

    bool isInt = true;
    while(!valid_answer) {
      
      String received = "";
      while(received == "") {
        received = Serial.readString();
      }

      if (received == GO_BACK) {
        break;
      } 

      for (int i = 0; i < received.length(); i++) {
        if (!charIsCorrectInt(received[i])) {
          isInt = false;
        }
      }

      if (isInt) {
        int resultRemove = macAddresses->removeMacAddress(received.toInt());
        ui.showResult_removeMacAddress(resultRemove);
        if (resultRemove) {
          valid_answer = true;
        }
      }
      else {
        ui.showResult_removeMacAddress(isInt);
      }
    }
  }
}

void Monitor::sendMacAddresses(MacAddresses* macAddresses) {
  MonitorConnection *sendTo;
  Ui ui;

  for (int i = 0; i < macAddresses->vectorMAs.size(); i++) {
    uint8_t* MA = macAddresses->vectorMAs[i].MA;
    sendTo = new MonitorConnection(MA);

    PositionMac Mac;
    
    for (int j = 0; j < SIZE_MACADDRRESS; j++) {
      Mac.most_left[j] = macAddresses->getPeer(MOST_LEFT, i, j);
      Mac.left[j] = macAddresses->getPeer(LEFT, i, j);
      Mac.right[j] = macAddresses->getPeer(RIGHT, i, j);
      Mac.most_right[j] = macAddresses->getPeer(MOST_RIGHT, i, j);
    }
    
    ui.printMacAddress(MA);
    sendTo->SendData(Mac);
    delete(sendTo);
  }
}


int Monitor::checkMacAddress(String MAString, Mac_Address* mac) {
  for (int i = 0; i < LENGHT_OF_MAC; i++) {
    if (!charIsCorrectHexFormat(MAString[i])) {
      return INCORRECT_MAC_ADDRESS_FORMAT;
    }
  }

  for (int i = 0; i < (SIZE_MACADDRRESS-1); i++) {

    int posOfColon = MAString.indexOf(":");
    if (posOfColon != POS_OF_COLON) {
      return INCORRECT_COLON_MAC_ADDRESS;
    }

    String hexstring = MAString.substring(0, posOfColon);
    mac->MA[i] = convertHexstringToInt(hexstring);
    MAString = MAString.substring((posOfColon+1));

    if (i == (SIZE_MACADDRRESS-2)) {
      mac->MA[i+1] = convertHexstringToInt(MAString);
    }
  }

  return CORRECT;
}

bool Monitor::charIsCorrectHexFormat(char ch) {
  char hexValues[] = {'a', 'b', 'c', 'd', 'e', 'f', 'A', 'B', 'C', 'D', 'E', 'F', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':'};
  int arrayLenght = sizeof(hexValues)/sizeof(hexValues[0]);
  for (int i = 0; i < arrayLenght; i++) {
    if (ch == hexValues[i]) {
      return true;
    }
  }
  return false;
}

int Monitor::convertHexstringToInt(String hexstring) {
  int number = strtol( &hexstring[0], NULL, 16);
  return number;
}