#include "MacAddresses.h"

bool MacAddresses::addMacAddress(Mac_Address newMacAddress, int index) {

  int MA_Size = vectorMAs.size();
  Mac_Address a = newMacAddress;

  for (int i = 0; i < MA_Size; i++) {
    Mac_Address b = vectorMAs.at(i);
    bool isEqual = std::equal(std::begin(a.MA), std::end(a.MA), std::begin(b.MA));
    bool isMonitor = std::equal(std::begin(a.MA), std::end(a.MA), std::begin(monitor));
    if (isEqual || isMonitor) {
        return false;
    }
  }
  
  if (vectorMAs.size() <= index) {
    vectorMAs.push_back(newMacAddress);
  }

  else {
    if (index < 0) {
      index = 0;
    }

    for (int i = (MA_Size); i > index; i--) {
      if (i == MA_Size) {
        vectorMAs.push_back(vectorMAs.back());
      }
      else{
        vectorMAs.at(i) = vectorMAs.at(i-1);
      }
    }
    vectorMAs.at(index) = newMacAddress;
  }

  return true;
}

int MacAddresses::removeMacAddress(int index) {
  if (index < 0 || index >= vectorMAs.size()) {
    return 0;
  }

  for (int i = index; i < (vectorMAs.size()); i++) {
    if (i == (vectorMAs.size()-1)) {
      break;
    }
    else {
      vectorMAs.at(i) = vectorMAs.at(i+1);
    }
  }
  
  vectorMAs.pop_back();
  return 1;
}

  uint8_t MacAddresses::getPeer(NEIGHBOURING_NODE pos, int index, int hex) {
    uint8_t result = 0;

    if (index + pos >= 0 && index + pos < vectorMAs.size()) {
      result = vectorMAs.at(index+pos).MA[hex];
    }

    return result;
  }