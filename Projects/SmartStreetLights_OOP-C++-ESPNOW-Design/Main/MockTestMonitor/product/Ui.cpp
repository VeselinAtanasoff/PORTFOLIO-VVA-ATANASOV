#include "Ui.h"

Ui::Ui(iDisplay &display, iMonitorConnection &monitorConnection, iMacAddressManager &macAddressManager)
: display(display), monitorConnection(monitorConnection), macAddressManager(macAddressManager)
{

}

void Ui::Instructions(int mode) {
    switch(mode) {
        case ADD_MAC_ADDRESS:
        display.showInstructionAddMacAddress();
        break;

        case REMOVE_MAC_ADDRESS:
        display.showInstructionRemoveMacAddress();
        break;
    }
}


int Ui::HandleAddMacAddress(char *str)
{

    if (std::atoi(str) == GO_BACK) {
        return BACK;
    }
    else {

    Mac_Address mac;

    const char *del = " ";
    char *hexstring = std::strtok(str, del);
    char *index = std::strtok(nullptr, del);
    int result;

    if (hexstring != nullptr && index != nullptr)
    {
        int sizeHexString = LengthOf(hexstring);
        int sizeIndex = LengthOf(index);

            int resultHexstring = StringToMacAddress(hexstring, sizeHexString, &mac);
            int resultIndex = StringToInt(index, sizeIndex);

        if (resultIndex != INCORRECT_STRING_TO_INT)
        {
            if (resultHexstring != INCORRECT_STRING_TO_MAC_ADDRESS)
            {
                result = macAddressManager.AddMacAddress(mac, resultIndex);
            }
            else
            {
                result = resultHexstring;
            }
        }
        else
        {
            result = resultIndex;
        }

            display.showResultAddMacAddress(result);
        }
        return result;
    }
}

int Ui::HandleRemoveMacAddress(char *str)
{

    if (std::atoi(str) == GO_BACK) {
        return BACK;
    }
        
    else {
        int size = LengthOf(str);
        int index = StringToInt(str, size);

        int result;

        if (index != INCORRECT_STRING_TO_INT) {
            result = macAddressManager.RemoveMacAddress(index);
            
        }
        else {
            result = index;
        }

        display.showResultRemoveMacAddress(result);

        return result;
    }
}

void Ui::HandleSendMacAddresses(iMonitorConnection &sender, Mac_Address MA)
{

    PositionMac posMac;
    
    posMac = macAddressManager.GetPeers(MA);
    sender.SendData(posMac);

    display.showResultSendMacAddresses(MA);

}

std::vector<Mac_Address> Ui::GetVector() {
    return macAddressManager.GetVector();
}

int Ui::StringToInt(char* str, int lenght) {
    bool isCorrectChar = false;

    for (int i = 0; i < lenght; i++) {

        isCorrectChar = false;
        for (int j = 0; j < VALID_INT_SIZE; j++) {

            if (str[i] == validInt[j]) {
                isCorrectChar = true;
                break;
            }
            else if(str[0] == '-') {
                isCorrectChar = true;
                break;
            }
        }

        if (!isCorrectChar) {
            break;
        }
    }

    if (isCorrectChar) {
        return std::atoi(str);
    }
    else {
        return INCORRECT_STRING_TO_INT;
    }

}

int Ui::StringToMacAddress(char* str, int lenght, Mac_Address* mac) {
    int result = INCORRECT_STRING_TO_MAC_ADDRESS;
    
    const char *del = ":";
    char* hexstring;
    int hex;
    int size;
    int arr_index = 0;

    for (int i = 0; i < lenght; i++) {
        hex = 0;
        size = 0;

        if (i == 0) {
            hexstring = std::strtok(str, del);

            if (hexstring == nullptr) {
                break;
            }

            size = LengthOf(hexstring);
            hex = HexstringToInt(hexstring, size);

            if (hex == INCORRECT_HEXSTRING_TO_INT) {
                break;
            }

            mac->MA[arr_index] = hex;
            

        }
        else if (i % 3 == 2) {
            hexstring = std::strtok(nullptr, del);
            
            if (hexstring == nullptr) {
                break;
            }

            size = LengthOf(hexstring);
            hex = HexstringToInt(hexstring, size);

            if (hex == INCORRECT_HEXSTRING_TO_INT) {
                break;
            }

            arr_index++;
            mac->MA[arr_index] = hex;
            if (arr_index == (SIZE_MACADDRESS - 1)) {
                result = CORRECT;
            }
        }

        if (arr_index >= 6) {
            result = INCORRECT_STRING_TO_MAC_ADDRESS;
            break;
        }
    }

    return result;
}

int Ui::HexstringToInt(char* str, int lenght) {
    bool isCorrectChar = false;
    if (lenght != 2) {
        return INCORRECT_HEXSTRING_TO_INT;
    }

    for (int i = 0; i < lenght; i++) {

        isCorrectChar = false;
        for (int j = 0; j < VALID_HEX_SIZE; j++) {

            if (str[i] == validHexValue[j]) {
                isCorrectChar = true;
                break;
            }
        }

        if (!isCorrectChar) {
            break;
        }
    }
    if (isCorrectChar) {
        return strtol( &str[0], NULL, 16);
    }
    else {
        return INCORRECT_HEXSTRING_TO_INT;
    }
}

int Ui::LengthOf(char* str) {
    int result = 0;
    while(str[result] != '\0') {
        result++;
    }

    return result;
}
