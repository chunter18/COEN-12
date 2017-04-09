#include <cassert>
#include "deque.h"

//all calls of malloc and related tasks are replaced by new
//all calls to free are replaced by delete
//the head and tail are in the namespace, and do not require a pointer
// to the list to be used
//aka dp->head->next becomes head->next

struct Node{
	int data;
	Node *next;
	Node *prev;
};

//O(1)
Deque::Deque()
{
	count = 0;
	head = new Node;
	assert(head != NULL);

	head->next = head;
	head->prev = head;	
}

//O(n)
Deque::~Deque()
{
	Node *p;
	p = head;
	while(count > 0)
		removeFirst();
	delete p;
}


//O(1)
int Deque::size()
{
	return count;
}

//O(1)
void Deque::addFirst(int x)
{
	Node *node = new Node;
	assert(node != NULL);

	node->data = x;

	node->next = head->next;
	node->prev = head;
	head->next->prev = node;
	head->next = node;
	count++;
	
}

//O(1)
void Deque::addLast(int x)
{
	Node *node = new Node;
	assert(node != NULL);

	node->data = x;
	node->prev = head->prev;
	node->next = head;
	head->prev->next = node;
	head->prev = node;	
	count++;	
}

//O(1)
int Deque::removeFirst()
{
	assert(count > 0);
	Node *p;

	p = head->next;
	int data = p->data;
	head->next = p->next;
	head->next->prev = head;
	delete p;
	count--;
	return data; 
}

//O(1)
int Deque::removeLast()
{
	assert(count > 0);
	Node *p;
	p = head->prev;
	int data = p->data;
	head->prev = p->prev;
	head->prev->next = head;
	delete p;
	count--;
	return data;
}

//O(1)
int Deque::getFirst()
{
	return head->next->data;

}

//O(1)
int Deque::getLast()
{
	return head->prev->data;
}

