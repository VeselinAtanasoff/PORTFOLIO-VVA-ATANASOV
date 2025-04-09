#include "FreeList.h"

void FreeList::add(int addr, int size) {
    if(findBlockByAddr(addr)) {
        return;
    }
    MList::add(addr, size);
    mergeBlocks();
}

void FreeList::mergeBlocks() {
    ITEM* current = head;
    while (current) {
        ITEM* next = current->next;
        if (next && current->_addr + current->_size == next->_addr) {
            current->_size += next->_size;
            current->next = next->next;
            delete next;
        } else {
            current = next;
        }
    }
}

ITEM* FreeList::findBlockBySize(int size) {
    ITEM* current = head;
    while (current) {
        if (current->_size >= size) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

ITEM FreeList::giveBlockToClaim(int size) {
    ITEM* block = findBlockBySize(size);
    if (block) {
        ITEM result = ITEM(block->_addr, size);
        if(block->_size == size) {
            remove(result._addr);
            return result;
        }
        block->_addr += size;
        block->_size -= size;
        if (block->_size == 0) {
            remove(result._addr);
        }
        return result;
    }
    return ITEM(-1, -1);
}
