#include "encoder.h"
#include "parityManager.h"
#include "fileManager.h"
#include "decoder.h"
#include "transmissionChannel.h"
#include "unity.h"

uint8_t parityTable[NIBBLES];




void setUp(void)
{
    // To do: optionally add the code to be executed before each unit test

    
}

void tearDown(void)
{
    // To do: optionally add the code to be executed after each unit test
   
}

void test_fillParityTable(void)
{
    //arrange
    uint8_t expectedEncoded0 = 0b00000000;
    uint8_t expectedEncoded7 = 0b00111001;
    uint8_t expectedEncoded15 = 0b01111111;
    
    //act
    bool result = fillParityTable(parityTable);

    //assert
    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_EQUAL_INT(expectedEncoded0, parityTable[0]);
    TEST_ASSERT_EQUAL_INT(expectedEncoded7, parityTable[7]);
    TEST_ASSERT_EQUAL_INT(expectedEncoded15, parityTable[15]);
}                                                           

void test_encodeByte1(void)
{
    //arrange
    uint8_t encodedByteLow;
    uint8_t encodedByteHigh;
    uint8_t byte = 0b00000000;
    uint8_t expectedEncodedByteLow = 0b00000000;
    uint8_t expectedEncodedByteHigh = 0b00000000;

    //act
    bool result = encodeByte(byte, parityTable, &encodedByteLow, &encodedByteHigh);
   
    //assert
    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_EQUAL_INT(expectedEncodedByteLow, encodedByteLow);
    TEST_ASSERT_EQUAL_INT(expectedEncodedByteHigh, encodedByteHigh);
}

void test_encodeByte2(void)
{
    //arrange
    uint8_t encodedByteLow;
    uint8_t encodedByteHigh;
    uint8_t byte = 0b11001010;
    uint8_t expectedEncodedByteLow = 0b01010001;
    uint8_t expectedEncodedByteHigh = 0b01100011;

    //act
    bool result = encodeByte(byte, parityTable, &encodedByteLow, &encodedByteHigh);
   
    //assert
    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_EQUAL_INT(expectedEncodedByteLow, encodedByteLow);
    TEST_ASSERT_EQUAL_INT(expectedEncodedByteHigh, encodedByteHigh);
}

void test_encodeByte3(void)
{
    //arrange
    uint8_t nullTable[16];
    uint8_t encodedByteHigh;
    uint8_t byte = 0b11001010;

    //act
    bool result = encodeByte(byte, nullTable, NULL, &encodedByteHigh);

    //assert
    TEST_ASSERT_FALSE(result);  
}

void test_decodeByte1(void)
{
    //arrange
    uint8_t encodedByteLow = 0b01010001;
    uint8_t encodedByteHigh = 0b01100011;
    uint8_t decodedByte;
    uint8_t expectedDecodedByte = 0b11001010;

    //act
    bool result = decodeByte(encodedByteHigh, encodedByteLow, parityTable, &decodedByte);

    //assert
    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_EQUAL_INT(expectedDecodedByte, decodedByte);
}

void test_decodeByte2(void)
{
    //arrange
    uint8_t encodedByteLow = 0b01010001;
    uint8_t encodedByteHigh = 0b01100011;

    //act
    bool result = decodeByte(encodedByteHigh, encodedByteLow, parityTable, NULL);

    //assert
    TEST_ASSERT_FALSE(result);
}

void test_decodeByte3(void)
{
    //arrange
    uint8_t encodedByteLow = 0b01010001;
    uint8_t encodedByteHigh = 0b01100011;
    uint8_t decodedByte;

    //act
    bool result = decodeByte(encodedByteHigh, encodedByteLow, NULL, &decodedByte);

    //assert
    TEST_ASSERT_FALSE(result);
}

void test_decodeByte4(void)
{
    //arrange
    uint8_t encodedByteLow = 0b01010011;
    uint8_t encodedByteHigh = 0b01111010;
    uint8_t decodedByte;
    uint8_t expectedDecodedByte = 0b10111010;

    //act
    bool result = decodeByte(encodedByteHigh, encodedByteLow, parityTable, &decodedByte);

    //assert
    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_EQUAL_INT(expectedDecodedByte, decodedByte);
}

void test_transmitByte1(void)
{
    //arrange
    uint8_t byte = 0b00000000;
    uint8_t flipPosition = 0;
    uint8_t expectedByte = 0b00000001;

    //act
    bool result = transmitByte(&byte, flipPosition);

    //assert
    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_EQUAL_INT(expectedByte, byte);
}

void test_transmitByte2(void)
{
    //arrange
    uint8_t byte = 0b00000000;
    uint8_t flipPosition = 7;
    uint8_t expectedByte = 0b10000000;

    //act
    bool result = transmitByte(&byte, flipPosition);

    //assert
    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_EQUAL_INT(expectedByte, byte);
}

void test_transmitByte3(void)
{
    //arrange
    uint8_t byte = 0b00000000;
    uint8_t flipPosition = 8;

    //act
    bool result = transmitByte(&byte, flipPosition);

    //assert
    TEST_ASSERT_FALSE(result);
}

void test_transmitByte4(void)
{
    //arrange
    uint8_t flipPosition = 3;

    //act
    bool result = transmitByte(NULL, flipPosition);

    //assert
    TEST_ASSERT_FALSE(result);
}

int main(void)
{
    UnityBegin(0);

    // To do : add your unit tests
    RUN_TEST(test_fillParityTable);
    RUN_TEST(test_encodeByte1);
    RUN_TEST(test_encodeByte2);
    RUN_TEST(test_encodeByte3);
    RUN_TEST(test_decodeByte1);
    RUN_TEST(test_decodeByte2);
    RUN_TEST(test_decodeByte3);
    RUN_TEST(test_decodeByte4);
    RUN_TEST(test_transmitByte1);
    RUN_TEST(test_transmitByte2);
    RUN_TEST(test_transmitByte3);
    RUN_TEST(test_transmitByte4);

    return UnityEnd();
}

