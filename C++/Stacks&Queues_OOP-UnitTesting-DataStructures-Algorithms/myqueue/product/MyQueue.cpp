#include "MyStack.h"
#include "MyQueue.h"

MyQueue::MyQueue(std::size_t itemsize)
{
	stackIn = new MyStack(itemsize);
	stackOut = new MyStack(itemsize);
	itemSize = itemsize;
}

MyQueue::~MyQueue()
{
	stackIn->myStackDestroy();
	stackOut->myStackDestroy();
	itemSize = 0;
}

int MyQueue::myQueueEnqueue(void *obj)
{
	if (stackIn->myStackPush(obj) == 1)
	{
		return 1;
	}

	return 0;
}

int MyQueue::myQueueDequeue(void *obj)
{
	if (stackOut->myStackNoOfElem() == 0)
	{
		while (stackIn->myStackNoOfElem() > 0)
		{
			void *temp = malloc(itemSize);
			if (stackIn->myStackPop(temp) == 1)
			{
				free(temp);
				return 1;
			}
			if (stackOut->myStackPush(temp) == 1)
			{
				free(temp);
				return 1;
			}
			free(temp);
		}
	}

	if (stackOut->myStackPop(obj) == 1)
	{
		return 1;
	}

	return 0;
}
