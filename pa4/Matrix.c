/*
Ko-Wei Chang
kochang
pa4
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Matrix.h"
#include "List.h"

//private struct

typedef struct EntryObj{
	int col;
	double val;
} EntryObj;

typedef EntryObj* Entry;

Entry newEntry(int n, double d){
	Entry e = malloc(sizeof(EntryObj));
	e->col = n;
	e->val = d;
	return e;
}

void freeEntry(Entry* pE){
	if (pE != NULL && *pE != NULL){
		free(*pE);
		*pE = NULL;
	}
}

typedef struct MatrixObj{
	List* rows;
	int size;
	int nnz;
} MatrixObj;

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
	Matrix m = malloc(sizeof(MatrixObj));
	m->size = n;
	m->nnz = 0;
	m->rows = malloc(sizeof(List)*n);
	for (int i = 0; i < n; ++i)
	{
		m->rows[i] = newList();
	}
	return m;
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
	if (pM != NULL && *pM != NULL){
		makeZero(*pM);
		for (int i = 0; i < (*pM)->size; ++i)
		{
			freeList(&((*pM)->rows[i]));
		}
		free((*pM)->rows);
		free(*pM);
		*pM = NULL;
	}
}

// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M){
	if (M == NULL){
		printf("Matrix Error: calling size() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	return M->size;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
	if (M == NULL){
		printf("Matrix Error: calling NNZ() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	return M->nnz;
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
	if( A==NULL || B==NULL ){
        printf("Matrix Error: calling equals() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    if (A->size != B->size){
    	return 0;
    }

   	for (int i = 0; i < A->size; ++i)
   	{
   		List aL = A->rows[i];
   		List bL = B->rows[i];

	    if ( length(aL) != length(bL) ){
	    	return 0;
	    }
	    moveFront(aL);
	    moveFront(bL);
	    while(index(aL)!=-1){
	    	Entry ae = (Entry)get(aL);
	    	Entry be = (Entry)get(bL);
			if (ae->val != be->val){
				return 0;
			}
			if (ae->col != be->col){
				return 0;
			}
	    	moveNext(aL);
	    	moveNext(bL);
	    }
   	}
   return 1;
}

// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M){
	if (M == NULL){
		printf("Matrix Error: calling makeZero() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	M->nnz = 0;
	for (int i = 0; i < M->size; ++i)
	{
		List L = M->rows[i];
		moveFront(L);
		while(index(L) != -1){
			Entry E = (Entry)get(L);
			freeEntry(&E);
			moveNext(L);
		}
		clear(L);
	}
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
	if (M == NULL){
		printf("Matrix Error: calling changeEntry() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	List L = M->rows[i-1];
	if (1 > i || i > size(M) || 1 > j || j > size(M)){
		printf("Matrix Error: calling changeEntry() on invalid precondition\n");
		exit(EXIT_FAILURE);
	} 
	if (x != 0){
		if (length(L) == 0){
			append(L, newEntry(j, x));
			M->nnz++;
		} else {
			moveFront(L);
			while(index(L) != -1 && ((Entry)get(L))->col < j){
				moveNext(L);
			}
			if(index(L) == -1){
				append(L, newEntry(j, x));
				M->nnz++;
			} else if (((Entry)get(L))->col == j){
				((Entry)get(L))->val = x;
			} else{
				insertBefore(L, newEntry(j, x));
				M->nnz++;
			}
		}
	} else {
		moveFront(L);
		while(index(L) != -1 && ((Entry)get(L))->col < j){
			moveNext(L);
		}
		if(index(L) != -1){
			Entry E = (Entry)get(L);
			freeEntry(&E);
			delete(L);
			M->nnz--;
		}
	}
}
// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
	if (A == NULL){
		printf("Matrix Error: calling copy() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	Matrix M = newMatrix(A->size);
	M->nnz = A->nnz;
	for (int i = 0; i < A->size; ++i)
	{
		List L = A->rows[i];
		moveFront(L);
		while(index(L) != -1){
			Entry E = (Entry)get(L);
			append(M->rows[i], newEntry(E->col, E->val));
			moveNext(L);
		}
	}
	return M;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
	if (A == NULL){
		printf("Matrix Error: calling transpose() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	Matrix M = newMatrix(A->size);
	M->nnz = A->nnz;
	for (int i = 0; i < A->size; ++i)
	{
		List L = A->rows[i];
		moveFront(L);
		while(index(L) != -1){
			Entry E = (Entry)get(L);
			append(M->rows[E->col - 1], newEntry(i+1, E->val));
			moveNext(L);
		}
	}
	return M;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
	if (A == NULL){
		printf("Matrix Error: calling scalarMult() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	Matrix M = copy(A);
	if (x == 0){
		makeZero(M);
	} else {
		for (int i = 0; i < A->size; ++i)
		{
			List L = M->rows[i];
			moveFront(L);
			while(index(L) != -1){
				((Entry)get(L))->val *= x;
				moveNext(L);
			}
		}
	}
	return M;
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
	if (A == NULL || B == NULL){
		printf("Matrix Error: calling sum() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if (A->size != B->size){
		printf("Matrix Error: calling sum() on invalid precondition\n");
		exit(EXIT_FAILURE);
	}
	if (A == B){
		return (scalarMult(2, A));
	}
	Matrix M = newMatrix(A->size);
	for (int i = 0; i < A->size; ++i)
	{
		List aL = A->rows[i];
		List bL = B->rows[i];
		List mL = M->rows[i];
		moveFront(aL);
		moveFront(bL);
		while(index(aL) != -1 &&index(bL) != -1){
			Entry aE = (Entry)get(aL);
			Entry bE = (Entry)get(bL);
			if (aE->col > bE->col){
				append(mL, newEntry(bE->col, bE->val));
				M->nnz++;
				moveNext(bL);
			} else if (aE->col < bE->col){
				append(mL, newEntry(aE->col, aE->val));
				M->nnz++;
				moveNext(aL);
			} else {
				if (aE->val + bE->val != 0){
					append(mL, newEntry(aE->col, aE->val + bE->val));
					M->nnz++;
				}
				moveNext(aL);
				moveNext(bL);
			}
		}
		while(index(aL) != -1){
			Entry aE = (Entry)get(aL);
			append(mL, newEntry(aE->col, aE->val));
			M->nnz++;
			moveNext(aL);
		}
		while(index(bL) != -1){
			Entry bE = (Entry)get(bL);
			append(mL, newEntry(bE->col, bE->val));
			M->nnz++;
			moveNext(bL);
		}
	}
	return M;
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
	if (A == NULL || B == NULL){
		printf("Matrix Error: calling diff() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if (A->size != B->size){
		printf("Matrix Error: calling diff() on invalid precondition\n");
		exit(EXIT_FAILURE);
	}
	Matrix M, neg;
	neg = scalarMult(-1, B);
	M = sum(neg, A);
	freeMatrix(&neg);
	return M;
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
	if (A == NULL || B == NULL){
		printf("Matrix Error: calling product() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if (A->size != B->size){
		printf("Matrix Error: calling product() on invalid precondition\n");
		exit(EXIT_FAILURE);
	}
	Matrix T = transpose(B);
	Matrix M = newMatrix(A->size);
	for (int i = 0; i < A->size; ++i)
	{
		List aL = A->rows[i];
		if (length(aL) != 0){
			for (int j = 0; j < B->size; ++j)
			{
				List bL = T->rows[j];
				int prod = 0;
				moveFront(aL);
				moveFront(bL);
				while(index(aL) != -1 &&index(bL) != -1){
					Entry aE = (Entry)get(aL);
					Entry bE = (Entry)get(bL);
					if (aE->col > bE->col){
						moveNext(bL);
					} else if (aE->col < bE->col){
						moveNext(aL);
					} else {
						prod += aE->val * bE->val;
						moveNext(aL);
						moveNext(bL);
					}
				}
				if(prod != 0){
					append(M->rows[i], newEntry(j+1, prod));
					M->nnz++;
				}
			}
		}
	}
	freeMatrix(&T);
	return M;
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
	if (M == NULL){
		printf("Matrix Error: calling printMatrix() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < M->size; ++i)
	{
		List L = M->rows[i];
		if(length(L) > 0){
			fprintf(out, "%d:", i+1);
			moveFront(L);
			while(index(L) != -1){
				Entry E = (Entry)get(L);
				fprintf(out, " (%d, %0.1f)", E->col, E->val);
				moveNext(L);
			}
			fprintf(out, "\n");
		}
	}
}
