#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "encoder.h" 
#include "decoder.h"
#include "parityManager.h"
#include "fileManager.h"
#include "transmissionChannel.h"


int main(int argc, char const *argv[])
{
    if(argc != 5){
        printf("Not enough arguments\n");
        return 1;
    }
  
    uint8_t parityTable[NIBBLES];

    if(fillParityTable(parityTable)){
        printf("Parity table filled\n");
    }
    else{
        printf("Error filling parity table\n");
        return 1;
    }

    if(encodeFile(argv[1], argv[2], parityTable)){
        printf("File encoded\n");
    }
    else{
        printf("Error encoding file\n");
        return 1;
    }

    if(transmitFile(argv[2], argv[3])){
        printf("File transmitted\n");
    }
    else{
        printf("Error transmitting file\n");
        return 1;
    }

    if(decodeFile(argv[3], argv[4], parityTable)){
        printf("File decoded\n");
    }
    else{
        printf("Error decoding file\n");
        return 1;
    }

    if(compareFiles(argv[1], argv[4])){
        printf("Files are the same\n");
    }
    else{
        printf("Files are different\n");
    }


    return 0;
}
