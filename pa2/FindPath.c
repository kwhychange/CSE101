/*
Ko-Wei Chang
kochang
pa2
*/

#include "Graph.h"
#include "List.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char* argv[]){
	FILE *infile, *outfile; //infile and outfile 

    //check only 2 command line args
    if(argc != 3){
    	fprintf(stderr, "Usage: ./FindPath <input file> <output file>\n");
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

    //scan the number of vertices in the graph
    int n = 0;
    fscanf(infile, "%d", &n);

    //make the graph 
    Graph g = newGraph(n);

    //scan the edges
    int a, b;
    a = b = 0;
    fscanf(infile, "%d %d", &a, &b);
    while (a != 0 && b != 0){
    	addEdge(g, a, b);
    	fscanf(infile, "%d %d", &a, &b);
    }
    //print graph
    printGraph(outfile, g);
    fprintf(outfile, "\n");

    //scan path to find and print
    fscanf(infile, "%d %d", &a, &b);
    while (a != 0 && b != 0){
    	BFS(g, a);
    	List L = newList();
    	getPath(L, g, b);
    	if(getDist(g, b) != INF){
    		fprintf(outfile, "The distance from %d to %d is %d\n", a, b, getDist(g, b));
    		fprintf(outfile, "A shortest %d-%d path is: ", a, b);
    		printList(outfile, L);
    		fprintf(outfile, "\n\n");
    	} else {
    		fprintf(outfile, "The distance from %d to %d is infinity\n", a, b);
    		fprintf(outfile, "No %d-%d path exists\n\n", a, b);
    	}
    	fscanf(infile, "%d %d", &a, &b);
    	freeList(&L);
    }

    //close and free
    freeGraph(&g);
    fclose(infile);
    fclose(outfile);

	return 0;
}