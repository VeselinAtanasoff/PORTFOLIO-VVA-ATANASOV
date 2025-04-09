#include "MyStack.h"
#include <cstdlib>
#include <cstring>
/* The stack is an abstract data type.
 * this means that the internal structures are
 * never exposed to the users of the library.
 */

/* Note: the stacks have no knowledge of what types
 * they are storing. This is not a concern of the stack
 */

MyStack::MyStack(std::size_t objsize)//always use initializer list
	: objSize(objsize)
	, top(nullptr)
	, numElem(0)
{
}

int MyStack::myStackPush(void *obj)
{
	if (obj == nullptr)
	{
		return 1;
	}
	// make copy here
	MyStackObject *object = new MyStackObject(obj, objSize, top);
	if (object == nullptr)
	{
		return 1;
	}
	top = object;
	numElem++;
	return 0;
}

int MyStack::myStackPop(void *obj)
{
	if (top == nullptr)
	{
		return 1;
	}

	memcpy(obj, top->getObject(), objSize);
	MyStackObject *oldTop = top;
	top = top->getNext();
	delete oldTop;
	numElem--;
	return 0;
}

MyStack::~MyStack()
{
	myStackDestroy();
	return;
}

std::size_t MyStack::myStackNoOfElem()
{
	return numElem;
}

void MyStack::myStackDestroy()
{
	while (top != nullptr)
	{
		MyStackObject *oldTop = top;
		top = top->getNext();
		delete oldTop; // Free each stack object.
	}
	numElem = 0;
}
