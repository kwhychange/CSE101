/*
Ko-Wei Chang
kochang
pa2
*/

#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_
#include <stdio.h>
#include "List.h"

#define INF -1
#define NIL -2 

typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
//Function newGraph() returns a Graph pointing to a newly created GraphObj representing a 
//graph having n vertices and no edges.
void freeGraph(Graph* pG);
//Function freeGraph() frees all heap memory associated with the Graph *pG,
//then sets the handle *pG to NULL.

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
//Functions getOrder() and getSize() return the corresponding field
//values
int getSource(Graph G);
//getSource() returns the source vertex most recently used in function BFS(), or NIL if
//BFS() has not yet been called.

//Functions getParent(), getDist() and getPath() all have the
//precondition 1 ≤ 𝑢 ≤ getOrder(𝐺).
int getParent(Graph G, int u);
//Function getParent() will return the parent of vertex u in the BFS tree
//created by BFS(), or NIL if BFS() has not yet been called.
int getDist(Graph G, int u);
//Function getDist() returns the distance from
//the most recent BFS source to vertex u, or INF if BFS() has not yet been called
void getPath(List L, Graph G, int u);
//Function getPath() appends to the List L the vertices of a shortest path in G from 
//source to u, or appends to L the value NIL if no such path exists.
//getPath() has the precondition getSource(G)!=NIL, so BFS() must be called
//before getPath() is called

/*** Manipulation procedures ***/
//Both addEdge() and addArc() have the precondition that their two int arguments must lie
//in the range 1 to getOrder(G)
void makeNull(Graph G);
//Function makeNull() deletes all edges of G, restoring it to its
//original (no edge) state. (This is called a null graph in graph theory literature). 
void addEdge(Graph G, int u, int v);
//Function addEdge() inserts a new edge joining u to v, i.e. u is added to the adjacency 
//List of v, and v to the adjacency List of u.
//Your program is required to maintain these lists in sorted order by increasing labels.
void addArc(Graph G, int u, int v);
//Function addArc() inserts a new directed edge from u to v, i.e. v is added 
//to the adjacency List of u (but not u to the adjacency List of v).
void BFS(Graph G, int s);
//Function BFS() runs the BFS algorithm on the Graph G with source s,
//setting the color, distance, parent, and source fields of G accordingly.

/*** Other operations ***/
void printGraph(FILE* out, Graph G);
//Finally, function printGraph() prints the adjacency list representation of G to the 
//file pointed to by out. The format of this representation should match the above 
//examples, so all that is required by the client is a single call to printGraph().

#endif