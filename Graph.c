/*********************************************************************************
 * * Ivan Garcia-Sanchez, igarci33
 * * 2020 Spring CSE101 PA4
 * * Graph.c
 * *********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include <stdbool.h>
#include "Graph.h"

typedef struct GraphObj{
   List* neighbors;
   char* color;
   int* parent;
   int* discover;
   int* finish;
   int vertices;
   int edges;
} GraphObj;

typedef GraphObj* Graph;

Graph newGraph(int n){
   Graph G = malloc(sizeof(GraphObj));
   G->neighbors = calloc(n+1,sizeof(List));
   G->color = calloc(n+1,sizeof(char));
   G->parent = calloc(n+1,sizeof(int));
   G->discover = calloc(n+1,sizeof(int));
   G->finish = calloc(n+1,sizeof(int));
   G->vertices = n;
   G->edges = 0;

   for(int i = 1; i <= n; i++){
      G->neighbors[i] = newList();
   }
   for(int i = 1; i <= n; i++){
      G->color[i] = 'w';
   }
   for(int i = 1; i <= n; i++){
      G->parent[i] = NIL;
   }
   for(int i = 1; i <= n; i++){
      G->discover[i] = UNDEF;
   }
   for(int i = 1; i <= n; i++){
      G->finish[i] = UNDEF;
   }
   return G;
}

void freeGraph(Graph* pG){
   if(pG!=NULL && *pG!=NULL){
      for(int i = 1; i <= (*pG)->vertices; i++){
         freeList(&(*pG)->neighbors[i]);	
      }
      free((*pG)->neighbors);
      free((*pG)->color);
      free((*pG)->parent);
      free((*pG)->finish);
      free((*pG)->discover);
      (*pG)->neighbors = NULL;
      (*pG)->color = NULL;
      (*pG)->discover = NULL;
      (*pG)->finish = NULL;
      (*pG)->parent = NULL;
      free(*pG);
      *pG = NULL;
   }
}

int getOrder(Graph G){
   return G->vertices;
}

int getSize(Graph G){
   return G->edges;
}

int getParent(Graph G, int u){
   if(u < 1 || u > getOrder(G)){
      printf("Graph Error: calling getParent() on out of bounds vertex\n");
      exit(1);
   }
   return G->parent[u];
}

int getDiscover(Graph G, int u){
   if(u < 1 || u > getOrder(G)){
      printf("Graph Error: calling getDiscover() on out of bounds vertex\n");
      exit(1);
   }
   return G->discover[u];
}

int getFinish(Graph G, int u){
   if(u < 1 || u > getOrder(G)){
      printf("Graph Error: calling getFinish() on out of bounds vertex\n");
      exit(1);
   }
   return G->finish[u];
}


void addEdge(Graph G, int u, int v){
   if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
      printf("Graph Error: calling addEdge() on out of bounds vertex\n");
      exit(1);
   }
   G->edges++;
   //Adds v to U adjacency list
   if(length(G->neighbors[u]) == 0){
      append(G->neighbors[u],v);
   }
   else{
      moveFront(G->neighbors[u]);
      bool appU = false;
      while(index(G->neighbors[u]) != -1 && !appU){
         if(v < get(G->neighbors[u])){
            insertBefore(G->neighbors[u],v);
            appU = true;
         }
         else{
            moveNext(G->neighbors[u]);
         }
      }
      if(!appU){
         append(G->neighbors[u],v);
      }
   }
   //Adds u to V adjacency list
   if(length(G->neighbors[v]) == 0){
      append(G->neighbors[v],u);
   }
   else{
      moveFront(G->neighbors[v]);
      bool appV = false;
      while(index(G->neighbors[v]) != -1 && !appV){
         if(u < get(G->neighbors[v])){
            insertBefore(G->neighbors[v],u);
            appV = true;
         }
         else{
            moveNext(G->neighbors[v]);
         }
      }
      if(!appV){
         append(G->neighbors[v],u);
      }
   }
}

void addArc(Graph G, int u, int v){
   if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
      printf("Graph Error: calling addEdge() on out of bounds vertex\n");
      exit(1);
   }
   G->edges++;
   
   //Adds v to U adjacency list
   if(length(G->neighbors[u]) == 0){
      append(G->neighbors[u],v);
   }
   else{
      moveFront(G->neighbors[u]);
      bool appU = false;
      while(index(G->neighbors[u]) != -1 && !appU){
         if(v < get(G->neighbors[u])){
            insertBefore(G->neighbors[u],v);
            appU = true;
         }
         else{
            moveNext(G->neighbors[u]);
         }
      }
      if(!appU){
         append(G->neighbors[u],v);
      }
   }
}

void DFS(Graph G, List S){
   for(int i = 1; i <= getOrder(G); i++){
      G->color[i] = 'w';
      G->parent[i] = NIL;
   }   
   int time = 0;
   moveFront(S);
   while(index(S) != -1){
      if(G->color[get(S)] == 'w'){
         visit(G,S,&time,get(S));
      }
      moveNext(S);
   }
   for(int i = 1; i <= getOrder(G); i++){
      deleteFront(S);
   }
   /*for(int i = 1; i <= getOrder(G); i++){
      
      if(G->color[i] == 'w'){
         visit(G,time);
      }
   }*/
}

void visit(Graph G, List S,int *t,int x){
   G->discover[x] = ++(*t);
   G->color[x] = 'g';
   if(!isEmpty(G->neighbors[x])){
      moveFront(G->neighbors[x]);
      while(index(G->neighbors[x]) != -1){
         if(G->color[get(G->neighbors[x])] == 'w'){
            G->parent[get(G->neighbors[x])] = x;
            visit(G,S,t,get(G->neighbors[x]));
         }
         moveNext(G->neighbors[x]);
      }
   }
   G->color[x] = 'b';
   G->finish[x] = ++(*t);
   int place = get(S);
   moveFront(S);
   while(index(S) != getOrder(G) - 1){
      moveNext(S);
   }
   insertAfter(S,x);
   moveFront(S);
   while(get(S) != place){
      moveNext(S);
   }
}

Graph transpose(Graph G){
   Graph copyG = newGraph(getOrder(G));
   for(int i = 1; i <= getOrder(G); i++){
      if(!isEmpty(G->neighbors[i])){
         moveFront(G->neighbors[i]);
         while(index(G->neighbors[i]) != -1){
            addArc(copyG,get(G->neighbors[i]),i);
            moveNext(G->neighbors[i]);
         }
      }
   }
   copyG->vertices = getOrder(G);
   return copyG;
}

Graph copyGraph(Graph G){
   Graph copyG = newGraph(getOrder(G));
   for(int i = 1; i <= getOrder(copyG);i++){
      if(!isEmpty(G->neighbors[i])){
         moveFront(G->neighbors[i]);
         while(index(G->neighbors[i]) != -1){
            addArc(copyG,i,get(G->neighbors[i]));
            moveNext(G->neighbors[i]);
         }
      }
   }
   copyG->vertices = getOrder(G);
   return copyG;   
}

void printGraph(FILE* out, Graph G){
   for(int i = 1; i <= getOrder(G); i++){
      fprintf(out,"%d:",i);
      if(length(G->neighbors[i]) != 0){
         fprintf(out," ");
         moveFront(G->neighbors[i]);
         while(index(G->neighbors[i]) != -1){
            fprintf(out,"%d",get(G->neighbors[i]));
            moveNext(G->neighbors[i]);
            if(index(G->neighbors[i]) != -1){
               fprintf(out," ");
            }
            else{
               if(i != getOrder(G)) fprintf(out,"\n");
            }	
         }
      }
      else{
         fprintf(out,"\n");
      }
   }
   fprintf(out,"\n");
}

