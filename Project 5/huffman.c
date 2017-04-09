#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "tree.h"
#include "pack.h"

#define P(X) (((i)-1)/2) //parent of x in arr
#define R(X) (((i)*2)+2) //right sibling of x in arr
#define L(X) (((i)*2)+1) //left sibling of x in arr

void insert(struct tree *node);
void print(void);
void printEncoding(struct tree *node); 
struct tree *delete(void);

//global variables. these are acessed throught all functions
//instead of passing them around, global makes it easy
struct tree *leaves[257];
struct tree *heap[257];
int charFreq[257];
int heapCount = 0;



int main(int argc, char *argv[])
{
	//check if num arguments is correct
	if(argc != 3)
	{
		printf("\nincorect number of arguments.\n");
		printf("usage: ./huffman /path/uncompressed.txt /path/compressed.txt\n ");
		return(0);
	}
	
	FILE *fp; //file pointer, open file
	if( (fp = fopen(argv[1],"r")) == NULL)
	{
		printf("Error opening file. Check that it exists.\n");
		return(0);
	}
	
	
	for(int i = 0; i < 257; i++)
	{
		//initially setting everything to 0 for ease
		charFreq[i] = 0;
		leaves[i] = NULL;
		heap[i] = NULL;
 	}

	char c; //holds char for reading
	while(fscanf(fp, "%c", &c) == 1)
		charFreq[(int)c]++; //read file
	
	fclose(fp);

	//making node with frequency data
	//inseting into heap


	//EOF
	leaves[256] = createTree(0, NULL, NULL);
	insert(leaves[256]);
    
	for(int j = 0; j < 257; j++)
	{
		//if char freq is greater than 0, add to tree

		if(charFreq[j] != 0)
		{
			leaves[j] = createTree(charFreq[j], NULL, NULL); //create a node
			insert(leaves[j]); //insert into the heap
		}

	}

    	//dummy nodes to hold data for insertion into huffman tree
	struct tree *l;
	struct tree *r;
	struct tree *new;
    
    
    

	while(heapCount > 1)
	{
		//creating the huffman tree
		//go until only there is only one tree

		//get data from end as left and right (least frequently used/min values)
		l = delete();
		assert(l != NULL);

		r = delete();
		assert(r != NULL);

		
		//create a new node with the sum of their counts as data,
		new = createTree((getData(l)+getData(r)), l, r);

		//put the new node back into the heap/huffman tree
		insert(new);
	}


	print(); //print the char codes

	pack(argv[1], argv[2], leaves); //does the compression

	return(0);
}

void print(void)
{
    
	for(int i = 0; i < 257; i++)
	{
        	//go thru all nodes in the huffman tree
        
		if(leaves[i] != NULL)
		{
            		//if the character occured at least once ^
           
            
			if(isprint(i) != 0 ) //if its printable
				printf("'%c': ", (char)i); //print it
			else
				printf("'%o': ", i); //otherwise print octal val

			printf("count:%d ", getData(leaves[i])); //print occurence count
            
			printf("encoding:");
			printEncoding(leaves[i]); //call custom function to print encoding
            
			printf("\n");
		}
	}
}

void printEncoding(struct tree *node)
{
	//traverses tree to get the code (recursive)
	//if you go left, print 0
	//if you go right, print 1
	//starts at bottom, gets to top first

	if(getParent(node) == NULL)
  	      return;
    

	if(getLeft(getParent(node)) == node) //if you came back down on left
		printf("0");
    	else
		printf("1");
    
    	printEncoding(getParent(node));

}

void insert(struct tree *node)
{

	
	int i = 0;
	i = heapCount;
    
	struct tree *hold;

	heap[i] = node;
    	
	//puts the nodes in the right place to maintain min-heap
	while(i != 0)
	{	
		if(getData(heap[i]) < getData(heap[P(X)]))
        	{
			//position swap
        		hold = heap[P(X)];
            		heap[P(X)] = heap[i];
            		heap[i] = hold;
            		i = P(X); //go to parent
        	}
        
        	else
            		break;
		
	}
	
	heapCount++;
}

struct tree *delete(void)
{
	//deletes last item
    
	struct tree *delete;
	delete = heap[0]; //hold min value to be returned
    
	struct tree *hold;
    
	heap[0] = heap[heapCount-1]; //last itme becomes first
	heapCount--;
    
	int i = 0;
	while(L(X) < heapCount)
	{
        
        	if(heapCount > 1)
        	{
            		if(heap[R(X)] != NULL && getData(heap[L(X)]) > getData(heap[R(X)]))
                		i = R(X);
            		else
                		i = L(X);
            
            		if(getData(heap[P(X)]) > getData(heap[i]))
            		{
               			hold = heap[P(X)];
                		heap[P(X)] = heap[i];
                		heap[i] = hold;
            		}
            
            		else
                		break;
        	}
	}

	
	return delete; //return deleted elt
}
