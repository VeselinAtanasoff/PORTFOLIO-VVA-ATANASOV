#pragma once

#include "AllocList.h"
#include "FreeList.h"

class MemoryManager {
    public:
        const int memStart = 1000;
        const int maxSize = 100;
        AllocList *allocList;
        FreeList *freeList;
       
        MemoryManager();
        ~MemoryManager();
        int claimMemory(int size);
        int freeMemory(int addr);
     //   void freeMemoryManager();
};

