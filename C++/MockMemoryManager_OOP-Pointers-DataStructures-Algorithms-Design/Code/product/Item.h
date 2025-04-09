#pragma once 

typedef struct ITEM
{
    struct ITEM *next=0;
    int _addr;
    int _size;
    ITEM(int addr,int size) {_addr=addr; _size=size;}
}ITEM;
