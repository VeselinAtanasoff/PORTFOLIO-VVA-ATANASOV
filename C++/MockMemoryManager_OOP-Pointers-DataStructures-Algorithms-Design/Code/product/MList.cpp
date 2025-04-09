#include <iostream>
#include "MList.h"

using namespace std;

/* Implementation of all your MList methods */

MList::MList(): head(nullptr), tail(nullptr) {
}

MList::~MList() {
    cleanList();
}

void MList::cleanList() {
    ITEM *temp = head;
    while (temp != 0) {
        ITEM *next = temp->next;
        delete temp;
        temp = next;
    }
    head = 0;
    tail = 0;
}

void MList::add(int addr, int size) {
    ITEM *newItem = new ITEM(addr, size);

    if (head == nullptr) {
        head = newItem;
        tail = newItem;
        return;
    }

    if (addr < head->_addr) {
        newItem->next = head;
        head = newItem;
        return;
    }

    ITEM *current = head;
    ITEM *prev = nullptr;

    while (current != nullptr && current->_addr < addr) {
        prev = current;
        current = current->next;
    }

    prev->next = newItem;
    newItem->next = current;

    if (current == nullptr) {
        tail = newItem;
    }
}


void MList::remove(int addr) {
    ITEM* current = head;
    ITEM* prev = nullptr;

    while (current) {
        if (current->_addr == addr) {
            if (prev) {
                prev->next = current->next;
            } else {
                head = current->next;
            }

            if (current == tail) {
                tail = prev;
            }

            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
    return;
}

ITEM* MList::findBlockByAddr(int addr) {
    ITEM* current = head;
    while (current) {
        if (current->_addr == addr) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}


