/*********************************************************************************
 * * Ivan Garcia-Sanchez, igarci33
 * * 2020 Spring CSE101 PA4
 * * Graph.h
 * * *********************************************************************************/

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

#include "List.h"
#define UNDEF -2
#define NIL -1

typedef struct GraphObj* Graph;

// Creates and returns a new empty Graph
Graph newGraph(int n);

// Frees all heap memory associated with *pG
void freeGraph(Graph* pG);

//Returns order of the graph
int getOrder(Graph G);

//Returns size of the graph
int getSize(Graph G);

// Returns the parent of vertex u in the BreadthFirst tree created by BFS(),
//or NIL if BFS() has not yet been called.
//Pre: 1 <= u <= getOrder(G) 
int getParent(Graph G, int u);

//Returns the discover time of the vertex u
//Pre: 1 <= u <= getOrder(G) 
int getDiscover(Graph G, int u);

//Returns the finish time of the vertex u
//Pre:  getSource(G) != NIL, 1 <= u <= getOrder(G) 
int getFinish(Graph G, int u);

// Inserts a new edge joining u to v, i.e.  i.e. u is added to the adjacency 
//List of v, and v to the adjacency List of u.
//Pre: 1 <=  u,v <= getOrder(G)
void addEdge(Graph G, int u, int v);

//Inserts a new directed edge from u to v, i.e. v is added to the adjacency 
//List of u (but not u to the adjacency List of v)
//Pre: 1 <=  u,v <= getOrder(G)
void addArc(Graph G, int u, int v);

//Runs the DFS algorithm on the Graph G with list s, setting the color, 
//discover, finish, and parent fields of G accordingly.
void DFS(Graph G, List S);

//Runs the recursive algorithim within DFS
void visit(Graph G, List S,int *time, int x);

//Returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G);

//Returns a reference to a new graph that is a copy of G
Graph copyGraph(Graph G);

//Prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G);

#endif
