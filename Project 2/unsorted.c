
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "set.h"

struct set { //defining the struct
	int count; //how many elements in the set
	int length; //length of array in the set
	char* *elts; //array of pointers to hold the strings
};

int findElement(SET *sp, char *elt); //prototype for findElement, gets rid of implicit definition warning

//O(1)
SET *createSet(int maxElts)
{
	SET *sp;
	sp = (SET*)malloc(sizeof(SET)); //allocating memory for the set
	assert(sp != NULL); //gives error if sp is null aka malloc failed
	// initalizing set as empty
	sp->count = 0;
	sp->length = maxElts; 
	sp->elts = (char**)malloc(sizeof(char*)*maxElts); //array of pointers 
	assert(sp->elts != NULL);
	return(sp); //return pointer to set
}

//O(n)
void destroySet(SET *sp)
{
	assert(sp != NULL);
	int i;
	for (i = 0; i < sp->count; i++)
		free(sp->elts[i]); //frees all the memory where the strings are
	free(sp->elts); //frees the memory of the array that held the string arrays
	free(sp); // destroying the pointer to the set
}

//O(1)
int numElements(SET *sp)
{
	return(sp->count); //count member holds the number of elements at all times.
}

//O(n)
bool hasElement(SET *sp, char *elt)
{
	//instructed to use a private function to do the search
	int found = 0;
	found = findElement(sp, elt); // finding element, returns -1 if failed to find
	if (found == -1)
		return(false); // not found
	else
		return(true); //found
}
 //O(n)
int findElement(SET *sp, char *elt)
{
	assert(sp != NULL);
	int i;
	for (i = 0; i<sp->count; i++)
	{
		//going through all elements and comparing the strings
		if (strcmp(sp->elts[i], elt) == 0) 
			return(i); //match, return index
	}
	return(-1); // notfound
}


//O(n)
bool addElement(SET *sp, char *elts)
{
	char *elt;
	assert(sp != NULL);
	assert(elts != NULL);
	if ((sp->count) == (sp->length))
		return(false); //array of elements is full
	if (hasElement(sp, elts) == true)
		return(false); //element to be added is in array, no duplication
	elt = strdup(elts); //we were instructed to use the strdup function
	assert(elts != NULL); //making sure adding didnt fail
	sp->elts[(sp->count)++] = elt; // adding the element
	return(true); //success
}

//O(n)
bool removeElement(SET *sp, char *elts)
{
	assert(sp != NULL);
	assert(elts != NULL);
	int index = 0;
	index = findElement(sp, elts); //finding index of element to remove
	if (index == -1)
		return(false); //not found
	if ((sp->count) == 1) // only one element dont need to change array positions
	{
		free(sp->elts[index]); //freeing the memory from strdup call
		(sp->count)--;
		return(true);
	}

	free(sp->elts[index]); //frees the space
	sp->elts[index] =  sp->elts[sp->count - 1]; //moving elements down to new position
	(sp->count)--; //coorecting the element count
	return(true);

}

