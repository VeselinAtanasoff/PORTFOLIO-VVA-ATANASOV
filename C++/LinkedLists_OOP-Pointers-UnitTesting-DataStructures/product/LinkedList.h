#ifndef __LINKEDLISTH__
#define __LINKEDLISTH__

#include "Item.h"

class LinkedList
{
public:
    LinkedList();

    int addFirst(int value);
    int addLast(int value);
    int addAfter(int c_value, int value);
    int removeFirst();
    int removeLast();
    int removeAfter(int c_value);
    void showList();
    int getHeadValue();
    int getTailValue();

private:
    Item *head,*tail;
};

#endif

