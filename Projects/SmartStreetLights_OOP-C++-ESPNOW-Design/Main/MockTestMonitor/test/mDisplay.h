#ifndef MDISPLAY_H
#define MDISPLAY_H

#include <iDisplay.h>
#include <gmock/gmock.h>

class mDisplay : public iDisplay {

public:
    MOCK_METHOD1(showAllMacAddresses, void(std::vector<Mac_Address>));
    MOCK_METHOD1(showMacAddress, void(Mac_Address));
    MOCK_METHOD0(showInstructionMainMenu, void());
    MOCK_METHOD0(showInstructionAddMacAddress, void());
    MOCK_METHOD1(showResultAddMacAddress, void(int));
    MOCK_METHOD0(showInstructionRemoveMacAddress, void());
    MOCK_METHOD1(showResultRemoveMacAddress, void(int));
    MOCK_METHOD1(showResultSendMacAddresses, void(Mac_Address));
    MOCK_METHOD1(showErrorCode, void(Device));
};

#endif