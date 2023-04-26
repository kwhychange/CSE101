/*
Ko-Wei Chang
kochang
pa3
*/

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
	Graph X = newGraph(8);
	printf("checkorder %d\n", getOrder(X));
	addArc(X, 5, 1);
	addArc(X, 2, 6);
	addArc(X, 3, 7);
	addArc(X, 8, 8);
	addArc(X, 7, 4);
	addArc(X, 1, 2);
	addArc(X, 4, 3);
	addArc(X, 6, 7);
	addArc(X, 3, 4);
	addArc(X, 2, 3);

	printGraph(stdout, X);
	Graph A = transpose(X);
	printf("checkorder %d\n", getOrder(X));
	printGraph(stdout, A);
	Graph B = copyGraph(X);
	printf("checkorder %d\n", getOrder(X));
	printGraph(stdout, B);

	List l1 = newList();
	List l2 = newList();
	for(int i = 1; i <= getOrder(A); ++i){
		append(l1, i);
		append(l2, i);
	}

	DFS(X, l1);
	DFS(A, l2);
	printList(stdout, l1);
	printf("\n\n");
	printList(stdout, l2);
	printf("\n\n");

	//graphclient 
	printf("graphclient\n");
	int i, n=8;
   List S = newList();
   Graph G = newGraph(n);
   Graph T=NULL, C=NULL;

   for(i=1; i<=n; i++) append(S, i);

   addArc(G, 1,2);
   addArc(G, 1,5);
   addArc(G, 2,5);
   addArc(G, 2,6);
   addArc(G, 3,2);
   addArc(G, 3,4);
   addArc(G, 3,6);
   addArc(G, 3,7);
   addArc(G, 3,8);
   addArc(G, 6,5);
   addArc(G, 6,7);
   addArc(G, 8,4);
   addArc(G, 8,7);
   printGraph(stdout, G);

   DFS(G, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   T = transpose(G);
   C = copyGraph(G);
   fprintf(stdout, "\n");
   printGraph(stdout, C);
   fprintf(stdout, "\n");
   printGraph(stdout, T);
   fprintf(stdout, "\n");

   DFS(T, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   freeList(&S);
   freeList(&l1);
   freeList(&l2);
   freeGraph(&G);
   freeGraph(&T);
   freeGraph(&C);
   freeGraph(&A);
   freeGraph(&B);
   freeGraph(&X);

	return 0;
}