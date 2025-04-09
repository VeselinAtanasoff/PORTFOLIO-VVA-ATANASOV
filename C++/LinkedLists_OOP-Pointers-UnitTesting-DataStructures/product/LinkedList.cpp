#include "LinkedList.h"
#include <iostream>

using namespace std;

LinkedList::LinkedList()
	: head(nullptr)
	, tail(nullptr)
{
}

int LinkedList::addFirst(int value)
 {
	Item *it = new Item(value);
	//check if it == nullptr
	if(head == nullptr)
	{
		head = it;
		tail = it;
	}
	else
	{
		it->setNext(head);
		head = it;
	}
	
	return 0;
}

int LinkedList::addLast(int value)
{
	Item *it = new Item(value);
	if(head == NULL)
	{
		head = it;
		tail = it;
	}
	else
	{
		tail->setNext(it);
		tail = it;
	}
	
	return 0;
}

int LinkedList::addAfter(int c_value, int value)
{
	Item *it = new Item(value);
	if(head == NULL)
	{
		head = it;
		tail = it;
	}
	else
	{
		Item *current = head;
		while(current != NULL)
		{
			if(current->getValue() == c_value)
			{
				// do here the new
				it->setNext(current->getNext());
				current->setNext(it);
				if(current == tail)
				{
					tail = it;
				}
				return 0;
			}
			current = current->getNext();
		}
	}
	
	return -1;
}

int LinkedList::removeFirst()
{
	if(head == NULL)
	{
		return -1;
	}
	
	Item *temp = head;
	head = head->getNext();
	delete temp;
	
	return 0;
}

int LinkedList::removeLast()
{
	if(head == NULL)
	{
		return -1;
	}
	
	if(head == tail)
	{
		delete head;
		head = NULL;
		tail = NULL;
	}
	else
	{
		Item *current = head;
		while(current->getNext() != tail)
		{
			current = current->getNext();
		}
		delete tail;
		tail = current;
		tail->setNext(NULL);
	}
	
	return 0;
}

int LinkedList::removeAfter(int c_value)
{
	if(head == NULL)
	{
		return -1;
	}
	
	Item *current = head;
	while(current != NULL)
	{
		if(current->getValue() == c_value)
		{
			if(current->getNext() == NULL)
			{
				return -1;
			}
			Item *temp = current->getNext();
			current->setNext(temp->getNext());
			delete temp;
			return 0;
		}
		current = current->getNext();
	}
	
	return -1;
}
	
void LinkedList::showList()
{
	cout << "List elements are \n";
	
	for(Item *it=head; it!=NULL; it=it->getNext() )
	{
		cout << it->getValue() << endl;
	}
}

int LinkedList::getHeadValue()
{
	if (head == NULL) return 0;

	return head->getValue();
}

int LinkedList::getTailValue()
{
	if (tail == NULL) return 0;
	
	return tail->getValue();
}
