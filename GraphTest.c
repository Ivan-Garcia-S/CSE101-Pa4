/*********************************************************************************
 * * * Ivan Garcia-Sanchez, igarci33
 * * * 2020 Spring CSE101 PA4
 * * * GraphTest.c
 * * * *********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
   Graph A = newGraph(8);
   Graph B = newGraph(8);
   
   printf("order: %d\n", getOrder(A));
   addArc(A,1,2);
   addArc(A,2,5);
   addArc(A,2,3);
   addArc(A,2,6);
   addArc(A,3,4);
   addArc(A,3,7);
   addArc(A,4,3);
   addArc(A,4,8);
   addArc(A,5,6);
   addArc(A,6,7);
   addArc(A,7,6);
   addArc(A,7,8);
   addArc(A,8,8);
   printGraph(stdout,A);
   
   List dfsA = newList();
   for(int i = 1; i <= getOrder(A); i++){
      append(dfsA,i);
   }
   DFS(A,dfsA);
   printList(stdout,dfsA);
   printf("\n");
   //makeNull(A);
   
   addArc(B,1,2);
   addArc(B,1,5);
   addArc(B,2,5);
   addArc(B,2,6);
   addArc(B,3,2);
   addArc(B,3,6);
   addArc(B,3,7);
   addArc(B,3,8);
   addArc(B,3,4);
   addArc(B,6,7);
   addArc(B,8,4);
   addArc(B,8,7);
   printGraph(stdout,B);
   //makeNull(B);
   
   List dfsB = newList();
   for(int i = 1; i <= getOrder(B); i++){
      append(dfsB,i);
   }
   DFS(B,dfsB); 
   printList(stdout,dfsB);

   freeGraph(&A);
   freeGraph(&B);
   freeList(&dfsB);
   freeList(&dfsA);
 
   return (0);
}
