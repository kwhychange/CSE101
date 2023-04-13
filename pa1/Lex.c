/*
Ko-Wei Chang
kochang
pa1
*/

#include "List.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define MAX_LEN 1024

int main(int argc, char* argv[]){
    FILE *infile; //infile 
    FILE *outfile; //outfile 

    //check only 2 command line args
    if(argc != 3){
    	fprintf(stderr, "Usage: ./Lex <input file> <output file>\n");
    	exit(EXIT_FAILURE);
    }

	//count # of lines n in input file
    infile = fopen(argv[1], "r");
    outfile = fopen(argv[2], "w");
    if (infile == NULL){
    	printf("Unable to open input file: %s\n", argv[1]);
    	exit(EXIT_FAILURE);
    }
    if (outfile == NULL){
    	printf("Unable to open output file: %s\n", argv[2]);
    	exit(EXIT_FAILURE);
    }
    int n = 0;
    char buff[MAX_LEN];
    while(fgets(buff, MAX_LEN, infile) != NULL){
    	n++;
    }

	//create string array of length n
    char *sArray[n]; 

    //read in the lines of the file as strings
    rewind(infile);
    n = 0;
    while (fgets(buff, MAX_LEN, infile) != NULL){
    	sArray[n] = malloc(sizeof(buff) * sizeof(char));
    	strcpy(sArray[n], buff);
    	n++;
    }

    //create a list
    List L = newList();

    //add and sort
    for (int i = 0; i < n; ++i)
    {
    	moveFront(L);
    	while(index(L) != -1 && strcmp(sArray[i], sArray[get(L)]) > 0){
    		moveNext(L);
    	} 
    	if (index(L) == -1){
    		append(L, i);
    	} else {
    		insertBefore(L, i);
    	}
    }

    //print
    moveFront(L);
    while(index(L) != -1){
    	fprintf(outfile, "%s", sArray[get(L)]);
    	moveNext(L);
    }

    //free arrays
    for (int i = 0; i < n; ++i)
    {
    	free(sArray[i]);
    }

    //free list and files
    freeList(&L);
    fclose(infile);
    fclose(outfile);

	return(0);
}