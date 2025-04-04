#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "encoder.h"
#include "decoder.h"
#include "transmissionChannel.h"

#ifndef FILEMANAGER_H

bool encodeFile(const char inputFileName[], const char outputFileName[], uint8_t *parityTableArray);
bool decodeFile(const char inputFileName[], const char outputFileName[], uint8_t *parityTableArray);
bool compareFiles(const char file1Name[], const char file2Name[]);
bool transmitFile(const char inputFileName[], const char outputFileName[]);

#endif