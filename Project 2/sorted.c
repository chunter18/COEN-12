
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "set.h"

//put in best guess of bigO for each function

struct set { //defining the struct
	int count; //how many elements in the set
	int length; //length of array in the set
	char* *elts; //array of pointers to hold the strings
};

int findElement(SET *sp, char *elt, bool *found);

//O(1)
SET *createSet(int maxElts)
{
	SET *sp;
	sp = (SET*)malloc(sizeof(SET)); //allocating memory for the set
	assert(sp != NULL); //gives error if sp is null aka malloc failed
	// initalizing set as empty
	sp->count = 0;
	sp->length = maxElts; 
	sp->elts = (char**)malloc(sizeof(char*)*maxElts);  //array of pointers to ( casted to char**)
	assert(sp->elts != NULL);
	return(sp); //return pointer to set
}

//O(n)
void destroySet(SET *sp)
{
	assert(sp != NULL);
	int i;
	for (i = 0; i < sp->count; i++)
		free(sp->elts[i]); //frees all the memory of the array holding the strings (erases the strings!)
	free(sp->elts); // frees the array that holds the pointers freed above
	free(sp); // destroying the pointer to the set
}

//O(1)
int numElements(SET *sp)
{
	return(sp->count); //count member holds the number of elements at all times.
}

//O(logn)
bool hasElement(SET *sp, char *elt)
{
	//instructed to use a private function to do the search
	bool found; 
	findElement(sp, elt, &found); // finding element, found changed by reference
	return(found); //found is either true or false
}

//O(logn)
int findElement(SET *sp, char *elt, bool *found)
{
	assert(sp != NULL); 
	int lo, mid, hi; //variables to hold indexes
	lo = 0;
	hi = (sp->count-1);
	int strComp; //var to hold value of comparisons
	*found = true; //intially true, this will change if the loop doesnt find the string
	while(lo<=hi)
	{
		mid = (lo+hi)/2; //setting the midpoint, aka the pivot
		strComp = strcmp(sp->elts[mid], elt); //only one comparison
		if(strComp  == 0)
			return(mid); //found the string
		if(strComp > 0)
			hi = mid-1; //string is in the lower half of elements
		else
			lo = mid+1; //string is in the upper half of elements
	}
	*found = false; // not found
	return(lo); // returns position of low, also where elt should go but that index is full
}

//O(n)
bool addElement(SET *sp, char *elts)
{
	assert(sp != NULL);
	assert(elts != NULL);
	if ((sp->count) == (sp->length))
		return(false); //array of elements is full

	int index;
	bool found;
	index = findElement(sp, elts, &found);
	if(found)
		return(false); // if element is found, no need to add it
	else
	{
		for(int i = (sp->count); i > index; i--) // start at end of array, work in to index
			sp->elts[i] = sp->elts[i-1]; // shifting all the elements to make room for elt
		sp->elts[index] = strdup(elts); // put element in new free spot
		(sp->count)++;
		return(true);
	}
}

//O(n)
bool removeElement(SET *sp, char *elts)
{
	assert(sp != NULL);
	assert(elts != NULL);
	int index = 0;
	bool found;
	index = findElement(sp, elts, &found); //finding index of element to remove
	if (found == false)
		return(false); //not found, cant remove
	if ((sp->count) == 1) // only one element dont need to change array positions
	{
		free(sp->elts[index]); //free allocated memory
		(sp->count)--;
		return(true);
	}

	free(sp->elts[index]); //free a spot
	for(int i = index; i < (sp->count)-1; i++) //start from index and work to end
		sp->elts[i] = sp->elts[i+1];   //shifting all elements to not have an empty space in pointer array
	(sp->count)--;
	return(true);
}

