#include "Item.h"
#include <iostream>

using namespace std;

Item::Item() : Item(0,NULL) {}

Item::Item(int value) : Item(value, NULL) {}

Item::Item(int value, Item* next)
{
	this->value = value;
	this->next = next;
}

int Item::getValue()
{
	return value;
}

void Item::setNext(Item* next)
{
	this->next = next;
}

Item* Item::getNext()
{
	return next;
}
