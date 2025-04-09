#pragma once 

#include "Item.h"

class MList {
protected: 
    //todo: add the two memstart and size fields here... Forget to copy them..
    ITEM *head=0;
    ITEM *tail=0;

public:
    /* all MList methods should come here */
    MList();
    virtual ~MList();
	void cleanList();
    virtual void add(int addr,int size);
    void remove(int addr);
    ITEM* findBlockByAddr(int addr);
    ITEM* getHead() { return head; }
};

