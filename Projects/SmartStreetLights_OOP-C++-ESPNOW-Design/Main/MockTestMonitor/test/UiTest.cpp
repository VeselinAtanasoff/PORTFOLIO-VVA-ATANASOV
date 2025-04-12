#include <Ui.h>
#include <mDisplay.h>
#include <mMonitorConnection.h>
#include <mMacAddressManager.h>

#include "MacAddress.h"

using ::testing::_;
using ::testing::Return;

class UiTest : public ::testing::Test
{
protected:
    mDisplay display;
    mMonitorConnection monitorConnection;
    mMacAddressManager macAddressManager;

    Ui ui;
    UiTest()
        : ui(display, monitorConnection, macAddressManager)
    {
    }

    virtual ~UiTest() {}
};

TEST_F(UiTest, test_setup)
{
}

TEST_F(UiTest, HandleAddMacAddress_Correct)
{
    Mac_Address mac;
    char str[] = "12:34:56:78:9A:BC 1";
    int result = CORRECT;

    char testHexString[] = "12:34:56:78:9A:BC";
    char testIndex[] = "1";

    int testSizeHexString = ui.LengthOf(testHexString);
    int testSizeIndex = ui.LengthOf(testIndex);

    int testResultHexString = CORRECT;

    int testResultIndex = ui.StringToInt(testIndex, testSizeIndex);

    EXPECT_EQ(testSizeHexString, ui.LengthOf(testHexString));
    EXPECT_EQ(testSizeIndex, ui.LengthOf(testIndex));

    EXPECT_EQ(testResultHexString, ui.StringToMacAddress(testHexString, testSizeHexString, &mac));
    EXPECT_EQ(testResultIndex, ui.StringToInt(testIndex, testSizeIndex));

    EXPECT_CALL(macAddressManager, AddMacAddress(mac, testResultIndex)).Times(1);
    EXPECT_CALL(display, showResultAddMacAddress(result)).Times(1);

    ui.HandleAddMacAddress(str);
}

TEST_F(UiTest, HandleAddMacAddress_Incorrect)
{
    Mac_Address mac;
    char str[] = "12:34:56:78:9A:JK 1";
    int result = INCORRECT_STRING_TO_MAC_ADDRESS;

    char testHexString[] = "12:34:56:78:9A:JK";
    char testIndex[] = "1";

    int testSizeHexString = ui.LengthOf(testHexString);
    int testSizeIndex = ui.LengthOf(testIndex);

    int testResultHexString = INCORRECT_STRING_TO_MAC_ADDRESS;

    int testResultIndex = ui.StringToInt(testIndex, testSizeIndex);

    EXPECT_EQ(testSizeHexString, ui.LengthOf(testHexString));
    EXPECT_EQ(testSizeIndex, ui.LengthOf(testIndex));

    EXPECT_EQ(testResultHexString, ui.StringToMacAddress(testHexString, testSizeHexString, &mac));
    EXPECT_EQ(testResultIndex, ui.StringToInt(testIndex, testSizeIndex));

    EXPECT_CALL(macAddressManager, AddMacAddress(_, _)).Times(0);
    EXPECT_CALL(display, showResultAddMacAddress(result)).Times(1);

    ui.HandleAddMacAddress(str);
}

TEST_F(UiTest, HandleAddMacAddress_Back)
{
    char str[] = "-1";

    int index = INCORRECT_STRING_TO_INT;
    int result = index;

    int expected = BACK;
    int actual;

    EXPECT_CALL(macAddressManager, AddMacAddress(_, _)).Times(0);
    EXPECT_CALL(display, showResultAddMacAddress(result)).Times(0);

    actual = ui.HandleAddMacAddress(str);
    EXPECT_EQ(expected, actual);
}

TEST_F(UiTest, HandleRemoveMacAddress_CorrectFormat)
{
    char str[] = "2";
    int size = 1;
    int index = 2;
    int result = CORRECT;

    int expected = result;
    int actual;

    EXPECT_EQ(size, ui.LengthOf(str));
    EXPECT_EQ(index, ui.StringToInt(str, size));

    EXPECT_CALL(macAddressManager, RemoveMacAddress(index)).Times(1);
    EXPECT_CALL(display, showResultRemoveMacAddress(result)).Times(1);

    actual = ui.HandleRemoveMacAddress(str);
    EXPECT_EQ(expected, actual);
}

TEST_F(UiTest, HandleRemoveMacAddress_Incorrect_String_To_Int)
{
    char str[] = "a";
    int size = 1;
    int index = INCORRECT_STRING_TO_INT;
    int result = index;

    int expected = result;
    int actual;

    EXPECT_EQ(size, ui.LengthOf(str));
    EXPECT_EQ(index, ui.StringToInt(str, size));

    EXPECT_CALL(macAddressManager, RemoveMacAddress(_)).Times(0);
    EXPECT_CALL(display, showResultRemoveMacAddress(result)).Times(1);

    actual = ui.HandleRemoveMacAddress(str);
    EXPECT_EQ(expected, actual);
}

TEST_F(UiTest, HandleRemoveMacAddress_CorrectFormat_IncorrectIndex)
{
    char str[] = "-3";
    int size = 2;
    int index = -3;
    int result = INVALID_POSITION;

    int expected = result;
    int actual;

    EXPECT_EQ(size, ui.LengthOf(str));
    EXPECT_EQ(index, ui.StringToInt(str, size));

    EXPECT_CALL(macAddressManager, RemoveMacAddress(index)).Times(1).WillOnce(Return(INVALID_POSITION));
    EXPECT_CALL(display, showResultRemoveMacAddress(result)).Times(1);

    actual = ui.HandleRemoveMacAddress(str);
    EXPECT_EQ(expected, actual);
}

TEST_F(UiTest, HandleRemoveMacAddress_Back)
{
    char str[] = "-1";

    int index = INCORRECT_STRING_TO_INT;
    int result = index;

    int expected = BACK;
    int actual;

    EXPECT_CALL(macAddressManager, RemoveMacAddress(index)).Times(0);
    EXPECT_CALL(display, showResultRemoveMacAddress(result)).Times(0);

    actual = ui.HandleRemoveMacAddress(str);
    EXPECT_EQ(expected, actual);
}

TEST_F(UiTest, HandleSendMacAddresses_No_Mac_To_Send)
{
    EXPECT_CALL(macAddressManager, GetVector()).Times(1);
    EXPECT_CALL(macAddressManager, GetPeers(_)).Times(0);
    EXPECT_CALL(monitorConnection, SendData(_)).Times(0);
    EXPECT_CALL(display, showResultSendMacAddresses()).Times(1);
    ui.HandleSendMacAddresses();
}

TEST_F(UiTest, HandleSendMacAddresses)
{
    std::vector<Mac_Address> vector = {{0x7C, 0x9E, 0xBD, 0xF3, 0xDE, 0x0C},
                                       {0x94, 0xB9, 0x7E, 0xC0, 0x08, 0x6C}};

    EXPECT_CALL(macAddressManager, GetVector()).Times(1).WillOnce(Return(vector));
    EXPECT_CALL(macAddressManager, GetPeers(_)).Times(2);
    EXPECT_CALL(monitorConnection, SendData(_)).Times(2);
    EXPECT_CALL(display, showResultSendMacAddresses()).Times(1);
    ui.HandleSendMacAddresses();
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}