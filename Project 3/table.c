#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "set.h"
#define EMPTY 2
#define FILLED 3
#define DELETED 4

//put in big 0 average AND worst case

struct set { //defining the struct
	int count; //how many elements in the set
	int length; //length of array in the set
	char* *elts; //array of pointers to hold the strings
	int *flags; //parallel array to array of string pointers to hold element status
};

//function prototypes
int findElement(SET *sp, char *elt, bool *found);
unsigned hashString(char *s);

//given hash function. O(n)
unsigned hashString(char *s)
{
	unsigned hash = 0;
	while(*s != '\0')
		hash = 31 * hash + *s++;
	return(hash);
}

//O(n)
SET *createSet(int maxElts)
{
	SET *sp;
	sp = (SET*)malloc(sizeof(SET)); //allocating memory for the set
	assert(sp != NULL); //gives error if sp is null aka malloc failed

	// initalizing set as empty
	sp->count = 0;
	sp->length = maxElts; 
	sp->elts = (char**)malloc(sizeof(char*)*maxElts);  //array of pointers to ( casted to char**)
	assert(sp->elts != NULL); //check for failure

	sp->flags = malloc(sizeof(int*)*maxElts);
	assert(sp->flags != NULL);

	for(int i = 0; i < maxElts; i++)
		sp->flags[i] = EMPTY; //initialize all flags to empty

	return(sp); //return pointer to set
}

//O(n)
void destroySet(SET *sp) //not every slot has data
{
	assert(sp != NULL);
	int i;
	for (i = 0; i < sp->length; i++)
	{
		if(sp->flags[i] == FILLED)
			free(sp->elts[i]); //frees all the memory of the array holding the strings (erases the strings!)
	}
	free(sp->elts); // frees the array that holds the pointers freed above
	free(sp->flags);
	free(sp); // destroying the pointer to the set
}

//O(1)
int numElements(SET *sp)
{
	return(sp->count); //count member holds the number of elements at all times.
}

//average O(1) worst case O(n)
bool hasElement(SET *sp, char *elt)
{
	//instructed to use a private function to do the search
	bool found; 
	findElement(sp, elt, &found); // finding element, found changed by reference
	return(found); //found is either true or false
}

//average is O(1), worst case O(m)
int findElement(SET *sp, char *elt, bool *found)
{
        //returns index of empty if not found or index of element if found
        assert(sp != NULL);

        int pos; //array index
        unsigned key;
        int firstdelete = 0;
        int remember; //variable to remember index of deleted slots for potiential return
        *found = false;

        key = hashString(elt);
        for(int i = 0; i < sp->length; i++)
        {
        //runs through whole tabel. wraps around if it hits end 
	       pos = (key+i)%(sp->length); //linear probe

		if(sp->flags[pos] == FILLED)
                {
                        if(strcmp(elt,sp->elts[pos]) == 0)
                        {
				*found = true;
                                return(pos);  //found it
                        }
                }

		if(sp->flags[pos] == DELETED)
                {
                        if(firstdelete == 0)
                        {
                                remember = pos; //remember spot
                                firstdelete = 1;
                        }
                }

                if(sp->flags[pos] == EMPTY)
                {
                        if(firstdelete == 1)
                        { 
			       return(remember);
				//didnt find element looking for
				//return the empty spot marked deleted
                        }
			return(pos); //first empty
                }

        }
        return(-1); //not found, no emptys
}


//average O(1) worst case O(n)
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
	if(index == -1) //findelt exit case
		return(false);
	
	sp->elts[index] = strdup(elts); // put element in new free spot
	(sp->count)++;
	(sp->flags[index]) = FILLED;
	return(true);
	
}

//average O(1) worst case O(n)
bool removeElement(SET *sp, char *elts)
{
	assert(sp != NULL);
	assert(elts != NULL);
	int index = 0;
	bool found;
	index = findElement(sp, elts, &found); //finding index of element to remove
	if (found == false)
		return(false); //not found, cant remove

	free(sp->elts[index]); //free a spot
	(sp->flags[index]) = DELETED;
	(sp->count)--;
	return(true);
}

