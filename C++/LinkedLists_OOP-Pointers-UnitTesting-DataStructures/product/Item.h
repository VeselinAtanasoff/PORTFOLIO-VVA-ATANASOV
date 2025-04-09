#ifndef __ITEMH__
#define __ITEMH__

class Item
{
public:
    Item();
    Item(int value);
    Item(int valie, Item* next);
    
    int getValue();
    void setNext(Item* next);
    Item* getNext();

private:
    int value=0;
    Item *next;
    static int counter;
};

#endif

