/*
Ko-Wei Chang
kochang
pa3
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
    	fprintf(stderr, "Usage: ./FindComponents <input file> <output file>\n");
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
    	addArc(g, a, b);
    	fscanf(infile, "%d %d", &a, &b);
    }
    //print graph
    fprintf(outfile, "Adjacency list representation of G:\n");
    printGraph(outfile, g);
    fprintf(outfile, "\n");

    //Run DFS on 𝐺 and 𝐺t, processing the vertices in the second call by decreasing finish times from the first call
    //make list for DFS
    List s = newList();
    for(int i = 1; i <= getOrder(g); ++i){
        append(s, i);
    }

    DFS(g, s);
    Graph gt = transpose(g);
    DFS(gt, s);

    //Determine the strong components of G
    int comp = 0;
    moveFront(s);
    while(index(s) != -1){
        if (getParent(gt, get(s)) == NIL){
            comp++;
        }
        moveNext(s);
    }
    fprintf(outfile, "G contains %d strongly connected components:", comp);

    //Print the strong components of 𝐺 to the output file in topologically sorted order
    moveBack(s);
    for (int i = 1; i <= comp; ++i)
    {
        List cl = newList();
        while(getParent(gt, get(s)) != NIL){
            prepend(cl, get(s));
            movePrev(s);
        }
        prepend(cl, get(s));
        fprintf(outfile, "\nComponent %d: ", i);
        printList(outfile, cl);
        freeList(&cl);
        movePrev(s);
    }

    //close and free
    freeGraph(&g);
    freeGraph(&gt);
    freeList(&s);
    fclose(infile);
    fclose(outfile);

	return 0;
}