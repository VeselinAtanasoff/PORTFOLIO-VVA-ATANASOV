#ifndef EUSERERRORCODE_H
#define EUSERERRORCODE_H

constexpr int GO_BACK = -1;

constexpr int ADD_MAC_ADDRESS = 1;
constexpr int REMOVE_MAC_ADDRESS = 2;
constexpr int SEND_MAC_ADDRESSES = 3;

enum UserErrorCode
{
    BACK = 1,
    CORRECT = 0,
    INVALID_POSITION = -1,
    DUPLICATE_MAC_ADDRESS = -2,
    INCORRECT_STRING_TO_INT = -10,
    INCORRECT_HEXSTRING_TO_INT = -11,
    INCORRECT_STRING_TO_MAC_ADDRESS = -12,
};

#endif