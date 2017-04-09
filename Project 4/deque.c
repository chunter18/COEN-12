#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "deque.h"

typedef struct node{
	int data;
	struct node *next;
	struct node *prev;
}node;

struct deque{ //head struct
	int count; //count of nodes in the list
	node *head;
};

//O(1)
DEQUE *createDeque(void)
{
	DEQUE *dp;
	//decalaring pointer to new deque

	dp = malloc(sizeof(DEQUE));
	assert(dp != NULL); //make sure malloc worked

	dp->count = 0;
	dp->head = (node*)malloc(sizeof(node));
	assert(dp->head != NULL); //the head is a dummy and doesnt count towadrs the node counter

	dp->head->next = dp->head; //link the head to itself
	dp->head->prev = dp->head;
	return(dp); //return the poimter to the list
}

//O(n)
void destroyDeque(DEQUE *dp)
{
	assert(dp != NULL);
	while(dp->count > 0)
		removeFirst(dp); //free the first node

	free(dp->head); //destroy head (dummy) node
	free(dp); //free pointer to list
}

//O(1)
int numItems(DEQUE *dp)
{
	return(dp->count);
}

//O(1)
void addFirst(DEQUE *dp, int x)
{
	assert(dp != NULL);
	node *new; //pointer to new node
	new = (node*)malloc(sizeof(node));
	new->data = x; //assign the data

	//inserting new node in between other nodes in first position 
	new->next = dp->head->next; //after new comes the rest of the list
	new->prev = dp->head; //before new is the head
	//updateing nodes around new
	dp->head->next->prev = new; //list prev points to new
	dp->head->next = new; //head next points to new
	dp->count++; //list is 1 longer
}

//O(1)
void addLast(DEQUE *dp, int x)
{
	//all same as addFirst here
	assert(dp != NULL);
	node *new;
	new = (node*)malloc(sizeof(node));
	assert(new != NULL);
	new->data = x;
	
	//updating links
	new->prev = dp->head->prev; //new prev is the end of the list
	new->next = dp->head; //end of the list is start (head)
	dp->head->prev->next = new; //last node next is new
	dp->head->prev = new; //head prev is end which is now new

	dp->count++;
}

//O(1)
int removeFirst(DEQUE *dp)
{
	assert(dp != NULL);
	assert(dp->count > 0);
	node *position;
	
	position = dp->head->next; //pointer to first real node in list
	int data = position->data;
	dp->head->next = position->next; //head pointer points to node after position
	dp->head->next->prev = dp->head; //node after position points back to head

	free(position); //free the node at position
	dp->count--; //node deleted
	return(data); //return data of first node
}

//O(1)
int removeLast(DEQUE *dp)
{
	assert(dp != NULL);
	assert(dp->count > 0);
	node *position;

	position = dp->head->prev; //pointer to node to be deleted
	int data = position->data;
	dp->head->prev = position->prev; //prev skips position node
	dp->head->prev->next = dp->head; //node in the new last position points to head

	//same as removeFirst
	free(position);
	dp->count--;
	return(data);
}

//O(1)
int getFirst(DEQUE *dp)
{
	assert(dp != NULL);
	return(dp->head->next->data); //first node data
}

//O(1)
int getLast(DEQUE *dp)
{
	assert(dp != NULL);
	return(dp->head->prev->data); //last node data
}
