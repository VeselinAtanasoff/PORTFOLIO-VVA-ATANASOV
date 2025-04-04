#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "fileManager.h"
#include "encoder.h"
#include "transmissionChannel.h"

bool encodeFile(const char inputFileName[], const char outputFileName[], uint8_t *parityTableArray)
{
    FILE *inputFile=fopen(inputFileName, "r");
    FILE *outputFile=fopen(outputFileName, "wb");
    bool actionComplete = false;
    uint8_t encodedByteLow;
    uint8_t encodedByteHigh;
    char c;

    if (inputFile == NULL || outputFile == NULL || parityTableArray==NULL)
    {
        
    }
    else
    {
        while ( (c = fgetc(inputFile)) != EOF)
        {
            if (encodeByte(c, parityTableArray, &encodedByteLow, &encodedByteHigh))
            {
                fputc(encodedByteHigh, outputFile);
                fputc(encodedByteLow, outputFile);
            }
            
            else
            {
                fclose(inputFile);
                fclose(outputFile);
                return actionComplete;
            }
            
        }
        actionComplete = true;
    }
    fclose(inputFile);
    fclose(outputFile);

    return actionComplete;
    
}

bool decodeFile(const char inputFileName[], const char outputFileName[], uint8_t *parityTableArray)
{
    FILE *inputFile = fopen(inputFileName, "rb");
    FILE *outputFile = fopen(outputFileName, "w"); // Note: "w" is correct for writing text files
    bool actionComplete = false;
    if (inputFile == NULL || outputFile == NULL || parityTableArray == NULL)
    {
       
    }
    else
    {
        int inputCharHigh;
        int inputCharLow;

        while ((inputCharHigh = fgetc(inputFile)) != EOF && (inputCharLow = fgetc(inputFile)) != EOF)
        {
            uint8_t encodedByteHigh = (uint8_t)inputCharHigh;
            uint8_t encodedByteLow = (uint8_t)inputCharLow;

            uint8_t decodedByte;

            if (decodeByte(encodedByteHigh, encodedByteLow, parityTableArray, &decodedByte))
            {
                fputc(decodedByte, outputFile);
            }
            else
            {
                fclose(inputFile);
                fclose(outputFile);
                return actionComplete;
            }
        }
        actionComplete = true;
    }
    fclose(inputFile);
    fclose(outputFile);
    return actionComplete;
}

bool compareFiles(const char file1Name[], const char file2Name[])
{
    FILE *file1=fopen(file1Name, "r");
    FILE *file2=fopen(file2Name, "r");
    bool filesAreEqual = false;
    char c1;
    char c2;
    if (file1 == NULL || file2 == NULL)
    {
        
    }
    else
    {
        while ( (c1 = fgetc(file1)) != EOF && (c2 = fgetc(file2)) != EOF)
        {
            if (c1 != c2)
            {
                
                filesAreEqual = false;
                fclose(file1);
                fclose(file2);
                return filesAreEqual;
            }
        }
        filesAreEqual = true;
    }
    fclose(file1);
    fclose(file2);
    return filesAreEqual;
}

bool transmitFile(const char inputFileName[], const char outputFileName[])
{
    FILE *inputFile = fopen(inputFileName, "rb");
    FILE *outputFile = fopen(outputFileName, "wb");
    bool actionComplete = false;
    if (inputFile == NULL || outputFile == NULL)
    {
        
    }
    else
    {
        uint8_t flipPosition = 0;
        int inputChar;
        while ((inputChar = fgetc(inputFile)) != EOF)
        { 
            uint8_t byte = (uint8_t)inputChar;
            if(transmitByte(&byte, flipPosition)){
                fputc(byte, outputFile);
            }else{
                fclose(inputFile);
                fclose(outputFile);
                return actionComplete;
            }
            flipPosition++;
            if(flipPosition == 8){
                flipPosition = 0;
            }
        }
        actionComplete = true;
    }
    fclose(inputFile);
    fclose(outputFile);
    return actionComplete;
}