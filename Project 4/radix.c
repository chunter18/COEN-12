#include <stdlib.h>
#include <stdio.h>
#include "deque.h"
#include <math.h>

void radixSort(DEQUE *numList, DEQUE *bins[10], int max);

int main(void)
{

		DEQUE *numList = createDeque(); //deque to hold all entered ints

		//array of bins to put numbers digits, each holds pointer to a deque
		DEQUE *bins[10]; //digits 0 to 9
		for(int i = 0; i < 10; i++)
			bins[i] = createDeque(); //creat deque in each index


		int x = 0; //stored the number read in from scanf
		int max = 0; //holds maximum value stored so far

		printf("\nEnter positive integers. CTRL-D to stop.\n");
		while(scanf("%d", &x) == 1)
		{
			if(x < 0)
			{
				printf("That isnt positive dummy. Try again. \n");
				continue;
			}
			if(x > max)
				max = x; //update maximum value for iteration count

			addLast(numList, x); //add it to the list, order doesnt matter

		}
	
		radixSort(numList, bins, max); //sorts, prints result, frees memory

		return(1);
}

void radixSort(DEQUE *numList, DEQUE *bins[10], int max)
{

	int round = ceil(log(max+1)/log(10)); //function of maximum iterations given to us
	int place = 1; //which place value you are currently sorting for, start with ones place
	int num; //index of bin

	while(round > 0)
	{
		while(numItems(numList) > 0)
		{
			//moving the numbers from numlist to bins
			int temp = removeFirst(numList); //stores data of first element in numlist
			num = (temp/place)%10;
			addLast(bins[num], temp); //add it as last entry in bins
		}
			
		for(int z = 0; z < 10; z++)
		{
			//moving (partially sorted) bin entries back to Numlist
			while(numItems(bins[z]) > 0)
			{
				int temp = removeFirst(bins[z]);
				addLast(numList, temp);
			} 
		}
	
		round--; //decrement loop counter
		place = place*10; //sort the next place value on next iteration
	}
	
	//printing out the sorted data
	printf("\nRESULTS:\n\n");
	while(numItems(numList) > 0)
		printf("%d\n", removeFirst(numList));
		
	//destroy deques, free their memory
	destroyDeque(numList);	
	for(int i =0; i < 10; i++)
		destroyDeque(bins[i]);
	return;
}
