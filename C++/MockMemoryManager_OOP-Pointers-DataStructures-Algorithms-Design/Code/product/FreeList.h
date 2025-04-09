#pragma once

#include "MList.h"

class FreeList : public MList
{
public:
    void add(int addr, int size) override;
    ITEM giveBlockToClaim(int size);

private:
    void mergeBlocks();
    ITEM *findBlockBySize(int size);
};