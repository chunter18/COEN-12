
#include <stdio.h>
#define MAXLENGTH 60 //max length of file string for input

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("\nIncorrect number of arguments. Please type the file name as the second argument.");
		return(0);
	}
	else
	{	
		FILE *fp;
		if((fp = fopen(argv[1],"r")) == NULL) //opening file
		{	
			printf("There was an error opening this file."); //returns error if problem
			return(0);
		}

		int wordcount = 0;
		char oneword[MAXLENGTH]; //dummy word for fscanf

		while(feof(fp) != 1) //while not at the end of the file
		{
			if(fscanf(fp,"%s",oneword) == 1) //read a word, make sure not to add to count if eof is hit
				wordcount++; //add it to the count
		}	
		printf("\nThere was %d total words.\n" ,(wordcount));
		fclose(fp);
		return(0);
	}
}
