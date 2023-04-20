/*
Ko-Wei Chang
kochang
pa2
*/

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){

   int x = 5;
   Graph A = newGraph(x);
   addEdge(A, 1, 2);
   addEdge(A, 3, 1);
   addEdge(A, 4, 1);
   addEdge(A, 4, 5);
   addEdge(A, 3, 5);

   printf("expected size = 5\nreal size = %d\n", getSize(A));
   printf("1: 2 3 4\n2: 1\n3: 1 5\n4: 1 5\n5: 3 4\n");
   printGraph(stdout, A);
   printf("-----\n");

   Graph B = newGraph(x);
   addArc(B, 1, 2);
   addArc(B, 3, 1);
   addArc(B, 4, 1);
   addArc(B, 4, 5);
   addArc(B, 3, 5);

   printf("expected size = 5\nreal size = %d\n", getSize(B));
   printf("1: 2\n2: \n3: 1 5\n4: 1 5\n5: \n");
   printGraph(stdout, B);
   printf("-----\n");

   printf("Order and size = %d, %d\n", getOrder(B), getSize(B));
   makeNull(B);
   printf("Order and size after makeNull= %d, %d\n", getOrder(B), getSize(B));
   printGraph(stdout, B);
   printf("-----\n");

   BFS(A, 1);
   printf("SOURCE: %d\n", getSource(A));
   List L = newList();
   getPath(L, A, 5);
   printf("expected path: 1 3 5 or 1 4 5\n");
   printList(stdout, L);
   printf("\n");
   clear(L);
   getPath(L, A, 4);
   printf("expected path: 1 4\n");
   printList(stdout, L);
   printf("\n-----\n");

   int i, s, max, min, d, n=35;
   List  C = newList(); // central vertices 
   List  P = newList(); // peripheral vertices 
   List  E = newList(); // eccentricities 
   Graph G = NULL;

   // Build graph G 
   G = newGraph(n);
   for(i=1; i<n; i++){
      if( i%7!=0 ) addEdge(G, i, i+1);
      if( i<=28  ) addEdge(G, i, i+7);
   }
   addEdge(G, 9, 31);
   addEdge(G, 17, 13);
   addEdge(G, 14, 33);

   // Print adjacency list representation of G
   printGraph(stdout, G);

   // Calculate the eccentricity of each vertex 
   for(s=1; s<=n; s++){
      BFS(G, s);
      max = getDist(G, 1);
      for(i=2; i<=n; i++){
         d = getDist(G, i);
         max = ( max<d ? d : max );
      }
      append(E, max);
   }

   // Determine the Radius and Diameter of G, as well as the Central and 
   // Peripheral vertices.
   append(C, 1);
   append(P, 1);
   min = max = front(E);
   moveFront(E);
   moveNext(E);
   for(i=2; i<=n; i++){
      d = get(E);
      if( d==min ){
         append(C, i);
      }else if( d<min ){
         min = d;
         clear(C);
         append(C, i);
      }
      if( d==max ){
         append(P, i);
      }else if( d>max ){
         max = d;
         clear(P);
         append(P, i);
      }
      moveNext(E);
   }

   // Print results 
   printf("\n");
   printf("Radius = %d\n", min);
   printf("Central vert%s: ", length(C)==1?"ex":"ices");
   printList(stdout, C);
   printf("\n");
   printf("Diameter = %d\n", max);
   printf("Peripheral vert%s: ", length(P)==1?"ex":"ices");
   printList(stdout, P);
   printf("\n");

   // Free objects 
   freeGraph(&A);
   freeGraph(&B);
   freeList(&C);
   freeList(&P);
   freeList(&E);
   freeList(&L);
   freeGraph(&G);

   return(0);
}
