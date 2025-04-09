#ifndef __MYQUE__
#define __MYQUE__

#include "MyStack.h"
#include <cstdlib>

class MyQueue {
	MyStack *stackIn;
	MyStack *stackOut;
	std::size_t itemSize;
public:
/* Create a queue */
	MyQueue(std::size_t itemsize);
	MyQueue() = delete;
/* Destroy all dynamic memory allocated by the queue */
	~MyQueue(void);
/* Enqueue an element from *obj, return 0 when success, otherwise -1 */
	int myQueueEnqueue(void *obj);
/* Dequeue an element to *obj, return 0 when success, otherwise -1 
 * Caller of this API is responsible for allocating memory for obj */
	int myQueueDequeue(void *obj);
};

#endif
