#ifndef __MYSTACK_H__
#define __MYSTACK_H__
#include <cstdlib>

/* The stack is an abstract data type.
 * this means that the internal structures are
 * never exposed to the users of the library.
 * 
 * The users are only allowed to use the stack API
 * that is defined below. 
 */

#include "MyStackObject.h"

// class MyStackObject {
// public:
// 	void* obj;
// 	MyStackObject *next;
// };

class MyStack {
public:
	/* Creates a stack of C++ objects of size objsize 
	*/
	MyStack(std::size_t objsize);

	/* Destroys all dynamic memory allocated in the stack */
	~MyStack(void);

	/* Pushes an object stored on obj pointer's address to the stack 
	* returns 0 on success and -1 on an error
	*/
	int myStackPush(void *obj);

	/* Pops an object from the stack to obj parameter
	* returns 0 on success and -1 on an error
	*/
	int myStackPop(void *obj);

	/* Returns the number of elements of the stack 
	*/
	std::size_t myStackNoOfElem(void);

	/*Free the memory allocated for the stack */
	void myStackDestroy(void);



private:
	std::size_t objSize;
    MyStackObject *top;
	std::size_t numElem;
	MyStack() = delete;//do if default constructor is not needed
};

#endif /* __MYSTACK_H__ */
