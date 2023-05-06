/*
Ko-Wei Chang
kochang
pa4
*/

#include "Matrix.h"
#include "List.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char* argv[]){
	FILE *infile, *outfile; //infile and outfile 

    //check only 2 command line args
    if(argc != 3){
    	fprintf(stderr, "Usage: ./Sparse <input file> <output file>\n");
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

    //scan matrix 
    int n, nza, nzb;
    n = nza = nzb = 0;
    fscanf(infile, "%d %d %d", &n, &nza, &nzb);

    //make matrix 
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);
    Matrix C, D, E, F, G, H, I, J;

    //scan the entries
    int r, c;
    double d;
    r = c = 0;
    d = 0.0;
    for (int i = 0; i < nza; ++i)
    {
    	fscanf(infile, "%d %d %lf", &r, &c, &d);
    	changeEntry(A, r, c, d);
    }
    for (int i = 0; i < nzb; ++i)
    {
    	fscanf(infile, "%d %d %lf", &r, &c, &d);
    	changeEntry(B, r, c, d);
    }

    //print stuff
    fprintf(outfile, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(outfile, A);

    fprintf(outfile, "\nB has %d non-zero entries:\n", NNZ(B));
    printMatrix(outfile, B);

    fprintf(outfile, "\n(1.5)*A =\n");
    C = scalarMult(1.5, A);
    printMatrix(outfile, C);

    fprintf(outfile, "\nA+B =\n");
    D = sum(A, B);
    printMatrix(outfile, D);

    fprintf(outfile, "\nA+A =\n");
    E = sum(A, A);
    printMatrix(outfile, E);

    fprintf(outfile, "\nB-A =\n");
    F = diff(B, A);
    printMatrix(outfile, F);

    fprintf(outfile, "\nA-A =\n");
    G = diff(A, A);
    printMatrix(outfile, G);

    fprintf(outfile, "\nTranspose(A) =\n");
    H = transpose(A);
    printMatrix(outfile, H);

    fprintf(outfile, "\nA*B =\n");
    I = product(A, B);
    printMatrix(outfile, I);

    fprintf(outfile, "\nB*B =\n");
    J = product(B, B);
    printMatrix(outfile, J);

    //close and free
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
    freeMatrix(&I);
    freeMatrix(&J);
    fclose(infile);
    fclose(outfile);

	return 0;
}