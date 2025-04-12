#include <Arduino.h>
#include "Ui.h"
#include "Display.h"
#include "MonitorConnection.h"
#include "MacAddressManager.h"

#include "MacAddress.h"

#include <string>
#include <stdlib.h>
#include <FS.h>
#include <LittleFS.h>

const char *csvFilePath = "/mac_addresses.csv";

enum State
{
    MAIN_MENU,
    ADD_MAC,
    REMOVE_MAC,
    SEND_MAC,
    SHOW_LIST_MAC
};
State UserState = MAIN_MENU;
Display display;

void dataReceivedHandler(const uint8_t *mac, const uint8_t *data, int data_len) {}

MonitorConnection *connection;
// MacAddressManager macAddressManager;
MacAddressManager *macAddressManager;

// buffer
char userInput[256];
int inputLength = 0;

bool instructionDisplayed = false;
 //   Ui ui(display, *connection, macAddressManager);
 Ui* ui;

void setup()
{
    delay(1000);
    Serial.begin(115200);
    if (!LittleFS.begin())
    { // Change to SPIFFS.begin() if using SPIFFS
        Serial.println("Failed to mount file system.");
        return;
    }
    Serial.println("LightCity Monitor");
    connection = new MonitorConnection(dataReceivedHandler);
    macAddressManager = new MacAddressManager();
    ui = new Ui(display, *connection, *macAddressManager);
}

void printFileContent(const char *filePath)
{
    File file = LittleFS.open(filePath, "r");
    if (!file)
    {
        Serial.println("Failed to open file for reading.");
        return;
    }

    Serial.println("File content:");
    while (file.available())
    {
        Serial.write(file.read());
    }
    file.close();
    Serial.println(); // Add a newline after printing the file
}

void loop()
{
    switch (UserState)
    {
    case MAIN_MENU:
        if (!instructionDisplayed)
        {
            display.showInstructionMainMenu();
            instructionDisplayed = true;
        }

        if (Serial.available())
        {
            inputLength = Serial.readBytesUntil('\n', userInput, sizeof(userInput) - 1);
            userInput[inputLength] = '\0'; // Null-terminate the string

            if (strcmp(userInput, "1") == 0)
            {
                UserState = ADD_MAC;
                instructionDisplayed = false;
            }
            else if (strcmp(userInput, "2") == 0)
            {
                UserState = REMOVE_MAC;
                instructionDisplayed = false;
            }
            else if (strcmp(userInput, "3") == 0)
            {
                UserState = SEND_MAC;
                instructionDisplayed = false;
            }
            else if (strcmp(userInput, "4") == 0)
            {
                UserState = SHOW_LIST_MAC;
                instructionDisplayed = false;
            }
            else
            {
                Serial.println("Invalid input. Try again.");
            }
        }

        break;

    case ADD_MAC:
        if (!instructionDisplayed)
        {
            ui->Instructions(ADD_MAC_ADDRESS);

            instructionDisplayed = true;
        }

        if (Serial.available())
        {
            inputLength = Serial.readBytesUntil('\n', userInput, sizeof(userInput) - 1);
            userInput[inputLength] = '\0';
            int result = ui->HandleAddMacAddress(userInput);

            switch (result)
            {
            case BACK:
                UserState = MAIN_MENU;
                instructionDisplayed = false;
                break;

            case CORRECT:
                instructionDisplayed = false;
                break;
            }
        }
        break;

    case REMOVE_MAC:
        if (!instructionDisplayed)
        {
            ui->Instructions(REMOVE_MAC_ADDRESS);
            display.showAllMacAddresses(ui->GetVector());
            instructionDisplayed = true;
        }

        if (Serial.available())
        {
            inputLength = Serial.readBytesUntil('\n', userInput, sizeof(userInput) - 1);
            userInput[inputLength] = '\0';

            int result = ui->HandleRemoveMacAddress(userInput);

            switch (result)
            {
            case BACK:
                UserState = MAIN_MENU;
                instructionDisplayed = false;
                break;

            case CORRECT:
                instructionDisplayed = false;
                break;
            }
        }
        break;

    case SEND_MAC:
        if (!instructionDisplayed)
        {
            std::vector<Mac_Address> vector = ui->GetVector();
            for (long unsigned int i = 0; i < vector.size(); i++)
            {
                Mac_Address MA = vector.at(i);
                uint8_t *mac = MA.MA;
                MonitorConnection *sender = new MonitorConnection(mac);
                ui->HandleSendMacAddresses(*sender, MA);
            }

            UserState = MAIN_MENU;
            instructionDisplayed = false;
        }
        break;

    case SHOW_LIST_MAC:

        display.showAllMacAddresses(ui->GetVector());
        printFileContent("/mac_addresses.csv");

        UserState = MAIN_MENU;

        break;

    default:
        UserState = MAIN_MENU;
        instructionDisplayed = false;
        break;
    }
}
