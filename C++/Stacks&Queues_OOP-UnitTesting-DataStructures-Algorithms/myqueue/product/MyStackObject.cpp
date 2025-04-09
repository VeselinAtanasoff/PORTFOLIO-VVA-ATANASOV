#include <cstdlib>
#include <cstring>
#include <exception>
using namespace std;

#include "MyStackObject.h"

MyStackObject::MyStackObject() : obj(nullptr), next(nullptr) {}

MyStackObject::MyStackObject(void *obj, size_t objSize) : MyStackObject()
{
	copyObject(obj, objSize);
};

MyStackObject::MyStackObject(void *obj, size_t objSize, MyStackObject *next)
{
	copyObject(obj, objSize);
	this->next = next;
}

MyStackObject::~MyStackObject()
{
	// TODO: please implement this method
	if (obj != nullptr)
	{
		delete (size_t *)obj;
	}
}

void MyStackObject::copyObject(void *obj, size_t objSize)
{
	// TODO: please implment this method
	void *newObjPointer = malloc(objSize);
	if (newObjPointer != nullptr)
	{
		memcpy(newObjPointer, obj, objSize);
		this->obj = newObjPointer;
	}
	else
		throw std::bad_alloc();
}

void *MyStackObject::getObject()
{
	return obj;
}

void MyStackObject::setNext(MyStackObject *next)
{
	this->next = next;
}

MyStackObject *MyStackObject::getNext()
{
	return next;
}