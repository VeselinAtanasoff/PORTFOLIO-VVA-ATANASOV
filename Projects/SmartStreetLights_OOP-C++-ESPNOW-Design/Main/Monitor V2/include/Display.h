#ifndef DISPLAY_H
#define DISPLAY_H

#include "iDisplay.h"

class Display : public iDisplay {

public:
    Display();
    void showAllMacAddresses(std::vector<Mac_Address>) override;
    void showMacAddress(Mac_Address) override;
    void showInstructionMainMenu() override;
    void showInstructionAddMacAddress() override;
    void showResultAddMacAddress(int) override;
    void showInstructionRemoveMacAddress() override;
    void showResultRemoveMacAddress(int) override;
    void showResultSendMacAddresses(Mac_Address) override;
    void showErrorCode(Device) override;

};

#endif