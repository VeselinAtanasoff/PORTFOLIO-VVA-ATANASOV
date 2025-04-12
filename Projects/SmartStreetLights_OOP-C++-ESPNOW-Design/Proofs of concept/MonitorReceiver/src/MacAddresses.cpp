#include "MacAddresses.h"

bool MacAddresses::addMacAddress(Mac_Address newMacAddress, int index) {

  int MA_Size = mac_addresses.size();
  Mac_Address a = newMacAddress;

  for (int i = 0; i < MA_Size; i++) {
    Mac_Address b = mac_addresses.at(i);
    bool isEqual = std::equal(std::begin(a.mac_address), std::end(a.mac_address), std::begin(b.mac_address));
    if (isEqual) {
        return false;
    }
  }
  
  if (mac_addresses.size() <= index) {
    mac_addresses.push_back(newMacAddress);
  }

  else {
    if (index < 0) {
      index = 0;
    }

    for (int i = (MA_Size); i > index; i--) {
      if (i == MA_Size) {
        mac_addresses.push_back(mac_addresses.back());
      }
      else{
        mac_addresses.at(i) = mac_addresses.at(i-1);
      }
    }
    mac_addresses.at(index) = newMacAddress;
  }

  return true;
}

bool MacAddresses::removeMacAddress(int index) {
  if (index < 0 || index >= mac_addresses.size()) {
    return false;
  }

  for (int i = index; i < (mac_addresses.size()); i++) {
    if (i == (mac_addresses.size()-1)) {
      break;
    }
    else {
      mac_addresses.at(i) = mac_addresses.at(i+1);
    }
  }
  
  mac_addresses.pop_back();
  return true;
}

Mac_Address MacAddresses::getPeer(int index, NEIGHBOURING_NODE pos) {
  return mac_addresses.at(index + pos);
}