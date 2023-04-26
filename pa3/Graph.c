/*
Ko-Wei Chang
kochang
pa3
*/

#include "Graph.h"
#include "List.h"

#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

typedef struct GraphObj
{
	int order;
	int size;
	int source;
	List* neighbors;
	int* parent;
	int* dist;
	int* color;
	int* fin;
	int* disc;
}GraphObj;

/*** Constructors-Destructors ***/
Graph newGraph(int n){
	if (n < 0){
		printf("Graph Error: cannot generate a graph of negative vertices in newGraph()\n");
		exit(EXIT_FAILURE);
	}
	Graph g = malloc(sizeof(GraphObj));

	g->order = n;
	g->size = 0;
	g->source = NIL;
	g->parent = calloc(n+1, sizeof(int));
	g->dist = calloc(n+1, sizeof(int));
	g->color = calloc(n+1, sizeof(int));
	g->neighbors = calloc(n+1, sizeof(List));
	g->fin = calloc(n+1, sizeof(int));
	g->disc = calloc(n+1, sizeof(int));

	for (int i = 1; i <= n; ++i)
	{
		g->neighbors[i] = newList();
		g->parent[i] = NIL;
		g->dist[i] = INF;
		g->color[i] = 0;
		//undiscovered white = 0, discovered gray = 1, finished black = 2
		g->fin[i] = UNDEF;
		g->disc[i] = UNDEF;
	}
	return g;
}
//Function newGraph() returns a Graph pointing to a newly created GraphObj representing a 
//graph having n vertices and no edges.
void freeGraph(Graph* pG){
	if (pG != NULL && *pG != NULL){
		for (int i = 1; i <= getOrder(*pG); ++i)
		{
			freeList(&((*pG)->neighbors[i]));
		}
		free((*pG)->neighbors);
		free((*pG)->color);
		free((*pG)->dist);
		free((*pG)->parent);
		free((*pG)->fin);
		free((*pG)->disc);
		free(*pG);
		*pG = NULL;
	}
}
//Function freeGraph() frees all heap memory associated with the Graph *pG,
//then sets the handle *pG to NULL.

/*** Access functions ***/
int getOrder(Graph G){
	if (G == NULL){
		printf("Graph Error: calling getOrder() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->order;
}

int getSize(Graph G){
	if (G == NULL){
		printf("Graph Error: calling getSize() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->size;
}
//Functions getOrder() and getSize() return the corresponding field values

int getSource(Graph G){
	if (G == NULL){
		printf("Graph Error: calling getSource() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->source;
}
//getSource() returns the source vertex most recently used in function BFS(), or NIL if
//BFS() has not yet been called.

//Functions getParent(), getDist() and getPath() all have the
//precondition 1 ≤ 𝑢 ≤ getOrder(𝐺).
int getParent(Graph G, int u){
	if (G == NULL){
		printf("Graph Error: calling getParent() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if (u < 1 || u > getOrder(G)){
		printf("Graph Error: calling getParent() on invalid precondition 1 <= u <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	/*
	if (G->source == NIL){
		return NIL;
	}
	*/
	return G->parent[u];
}
//Function getParent() will return the parent of vertex u in the BFS tree
//created by BFS(), or NIL if BFS() has not yet been called.

int getDist(Graph G, int u){
	if (G == NULL){
		printf("Graph Error: calling getDist() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if (u < 1 || u > getOrder(G)){
		printf("Graph Error: calling getDist() on invalid precondition 1 <= u <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	if (G->source == NIL){
		return INF;
	}
	return G->dist[u];
}
//Function getDist() returns the distance from
//the most recent BFS source to vertex u, or INF if BFS() has not yet been called

int getDiscover(Graph G, int u){
	if (G == NULL){
		printf("Graph Error: calling getDiscover() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if (u < 1 || u > getOrder(G)){
		printf("Graph Error: calling getDiscover() on invalid precondition 1 <= u <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	return G->disc[u];
}
/* Pre: 1<=u<=n=getOrder(G) */

int getFinish(Graph G, int u){
	if (G == NULL){
		printf("Graph Error: calling getFinish() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if (u < 1 || u > getOrder(G)){
		printf("Graph Error: calling getFinish() on invalid precondition 1 <= u <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	return G->fin[u];
}
/* Pre: 1<=u<=n=getOrder(G) */
//getDiscover(), and getFinish() return the appropriate field values for the given vertex.
//Note that the parent of a vertex may be NIL. 
//The discover and finish times of vertices will be undefined before DFS is called.

/* Given psuedocode
PrintPath(G,s,x)  pre: BFS(G,s) was run
   if x == s
        print(s)
   else if p[x] == nil 
        print(x," is not reachable from ",s)
   else
        PrintPath(G, s, p[x])
        print(x)
*/
void getPath(List L, Graph G, int u){
	if (G == NULL){
		printf("Graph Error: calling getPath() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if (u < 1 || u > getOrder(G)){
		printf("Graph Error: calling getPath() on invalid precondition 1 <= u <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	if (getSource(G) == NIL){
		printf("Graph Error: calling getPath() on NIL source\n");
		exit(EXIT_FAILURE);
	}
	if (G->source == u){
        append(L, u);
   	} else if (getParent(G, u) == NIL){
        append(L, NIL);
   	} else {
        getPath(L, G, getParent(G, u));
        append(L, u);
    }
}
//Function getPath() appends to the List L the vertices of a shortest path in G from 
//source to u, or appends to L the value NIL if no such path exists.
//getPath() has the precondition getSource(G)!=NIL, so BFS() must be called
//before getPath() is called

/*** Manipulation procedures ***/
void makeNull(Graph G){
	if (G == NULL){
		printf("Graph Error: calling makeNull() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 1; i <= getOrder(G); ++i)
	{
		G->parent[i] = NIL;
		G->dist[i] = INF;
		G->color[i] = 0;
		clear(G->neighbors[i]);
	}
	G->source = NIL;
	G->size = 0;
}
//Function makeNull() deletes all edges of G, restoring it to its
//original (no edge) state. (This is called a null graph in graph theory literature). 

//Both addEdge() and addArc() have the precondition that their two int arguments must lie
//in the range 1 to getOrder(G)
void addEdge(Graph G, int u, int v){
	if (G == NULL){
		printf("Graph Error: calling addEdge() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if (u < 1 || u > getOrder(G)){
		printf("Graph Error: calling addEdge() on invalid precondition 1 <= u <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	if (v < 1 || v > getOrder(G)){
		printf("Graph Error: calling addEdge() on invalid precondition 1 <= v <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	addArc(G, v, u);
	moveFront(G->neighbors[u]);
	if (index(G->neighbors[u]) >= 0){
		while (index(G->neighbors[u]) >= 0 && get(G->neighbors[u]) < v){
			moveNext(G->neighbors[u]);
		}
		if (index(G->neighbors[u]) == -1){
			append(G->neighbors[u], v);
		} else {
			insertBefore(G->neighbors[u], v);
		}
	} else {
		append(G->neighbors[u], v);
	}
}
//Function addEdge() inserts a new edge joining u to v, i.e. u is added to the adjacency 
//List of v, and v to the adjacency List of u.
//Your program is required to maintain these lists in sorted order by increasing labels.

void addArc(Graph G, int u, int v){
	if (G == NULL){
		printf("Graph Error: calling addArc() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if (u < 1 || u > getOrder(G)){
		printf("Graph Error: calling addArc() on invalid precondition 1 <= u <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	if (v < 1 || v > getOrder(G)){
		printf("Graph Error: calling addArc() on invalid precondition 1 <= v <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	moveFront(G->neighbors[u]);
	if (index(G->neighbors[u]) >= 0){
		while (index(G->neighbors[u]) >= 0 && get(G->neighbors[u]) < v){
			moveNext(G->neighbors[u]);
		}
		if (index(G->neighbors[u]) == -1){
			append(G->neighbors[u], v);
		} else {
			insertBefore(G->neighbors[u], v);
		}
	} else {
		append(G->neighbors[u], v);
	}
	G->size++;
}
//Function addArc() inserts a new directed edge from u to v, i.e. v is added 
//to the adjacency List of u (but not u to the adjacency List of v).

/* Given Pseudocode
BFS(G,s)
   for x in V(G)-{s}
        color[x] = white
        d[x] = inf
        p[x] = nil 
   color[s] = gray       // discover the source s
   d[s] = 0
   p[s] = nil 
   Q = { }               // construct a new empty queue
   Enqueue(Q,s)
   while Q ≠ { }
        x = Dequeue(Q) 
        for y in adj[x]
             if color[y] == white         // y is undiscovered
                  color[y] = gray         // discover y
                  d[y] = d[x]+1
                  p[y] = x
                  Enqueue(Q,y)
        color[x] = black                  // finish x
*/

void BFS(Graph G, int s){
	if (G == NULL){
		printf("Graph Error: calling BFS() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if (s < 1 || s > getOrder(G)){
		printf("Graph Error: calling BFS() on invalid precondition 1 <= s <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 1; i <= getOrder(G); ++i)
	{
		G->parent[i] = NIL;
		G->dist[i] = INF;
		G->color[i] = 0;
	}
	G->source = s;
	G->color[s] = 1;
	G->dist[s] = 0;
	G->parent[s] = NIL;
	List temp = newList();
	append(temp, s);
	moveFront(temp);
	while (length(temp) != 0){
		int x = front(temp);
		moveFront(G->neighbors[x]);
		while (index(G->neighbors[x]) != -1){
			int y = get(G->neighbors[x]);
        	if (G->color[y] == 0){
        		G->color[y] = 1;
        		G->dist[y] = G->dist[x] + 1;
        		G->parent[y] = x;
        		append(temp, y);
        	}
        	moveNext(G->neighbors[x]);
    	}
    	G->color[x] = 2;
    	deleteFront(temp);
	}
	freeList(&temp);
}
//Function BFS() runs the BFS algorithm on the Graph G with source s,
//setting the color, distance, parent, and source fields of G accordingly.

/* Given pseudocode
Visit(x)
   d[x] = (++time)          // discover x
   color[x] = gray            
   for all y in adj[x]
      if color[y] == white 
         p[y] = x
         Visit(y)
   color[x] = black 
   f[x] = (++time)          // finish x
*/
void Visit(Graph G, List S, int x, int* time){
	G->disc[x] = ++(*time);
	G->color[x] = 1;
	moveFront(G->neighbors[x]);
	while(index(G->neighbors[x]) != -1){
		if(G->color[get(G->neighbors[x])] == 0)
		{
			G->parent[get(G->neighbors[x])] = x;
			Visit(G, S, get(G->neighbors[x]), time);
		}
		moveNext(G->neighbors[x]);
	}
	G->color[x] = 2;
	G->fin[x] = ++(*time);
	prepend(S, x);
}

/* Given psuedocode
DFS(G)
   for all x in V(G)
      color[x] = white 
      p[x] = nil 
   time = 0
   for all x in V(G)  // main loop of DFS
      if color[x] == white 
         Visit(x)
*/
void DFS(Graph G, List S){
	if (G == NULL){
		printf("Graph Error: calling DFS() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if (length(S) != getOrder(G)){
		printf("Graph Error: calling DFS() on invalid precondition length(s) == getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i <= getOrder(G); ++i){
		G->color[i] = 0;
		G->parent[i] = NIL;
		G->fin[i] = UNDEF;
		G->disc[i] = UNDEF;
	}
	int time = 0;
	List cs = copyList(S);
	clear(S);
	moveFront(cs);
	while(index(cs) != -1){
		if(G->color[get(cs)] == 0){
			Visit(G, S, get(cs), &time);
		}
		moveNext(cs);
	}
	freeList(&cs);
} 
/* Pre: length(S)==getOrder(G) */
//Recall DFS() calls the recursive algorithm Visit() (referred to as DFS-Visit() in the text), and uses a variable
//called time that is static over all recursive calls to Visit()

/*** Other operations ***/
void printGraph(FILE* out, Graph G){
	if (G == NULL){
		printf("Graph Error: calling printGraph() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 1; i <= getOrder(G); ++i)
	{
		fprintf(out, "%d: ", i);
		printList(out, G->neighbors[i]);
		fprintf(out, "\n");
	}
}
//Finally, function printGraph() prints the adjacency list representation of G to the 
//file pointed to by out. The format of this representation should match the above 
//examples, so all that is required by the client is a single call to printGraph().

Graph transpose(Graph G){
	if (G == NULL){
		printf("Graph Error: calling transpose() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	Graph ng = newGraph(getOrder(G));
	for (int i = 1; i <= getOrder(G); ++i)
	{
		moveFront(G->neighbors[i]);
		while(index(G->neighbors[i]) != -1){
			addArc(ng, get(G->neighbors[i]), i);
			moveNext(G->neighbors[i]);
		}
	}
	return ng;
}
//Function transpose() returns a reference to a new graph object representing the transpose of G

Graph copyGraph(Graph G){
	if (G == NULL){
		printf("Graph Error: calling copyGraph() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	Graph ng = newGraph(getOrder(G));
	for (int i = 1; i <= getOrder(G); ++i)
	{
		moveFront(G->neighbors[i]);
		while(index(G->neighbors[i]) != -1){
			addArc(ng, i, get(G->neighbors[i]));
			moveNext(G->neighbors[i]);
		}
	}
	return ng;
}
//copyGraph() returns a reference to a new graph that is a copy of G
//Both transpose() and copyGraph() may be considered constructors since they create new graph objects