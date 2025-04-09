#ifndef __MYSTACKOBJECT_H__
#define __MYSTACKOBJECT_H__
#include <cstdlib>

class MyStackObject {
public:
	MyStackObject();
	MyStackObject(void *obj, size_t objSize);
	MyStackObject(void *obj, size_t objSize, MyStackObject* next);


	virtual ~MyStackObject();

	void copyObject(void* obj, size_t objSize); //TODO: implement this method
	
	void* getObject();
	void setNext(MyStackObject* next);
	MyStackObject* getNext();

private:
	void* obj;
	MyStackObject *next;
};

#endif /* __MYSTACK_H__ */

