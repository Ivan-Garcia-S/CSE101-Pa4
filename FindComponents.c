/*********************************************************************************
 * * * Ivan Garcia-Sanchez, igarci33
 * * * 2020 Spring CSE101 PA4
 * * * FindComponents.c
 * * * *********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#include"Graph.h"
#define MAX_LEN 160

int main(int argc, char * argv[]){
   FILE *in, *out;
   int num1;
   int num2;
   int count;

   if(argc != 3){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if(in == NULL){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if(out == NULL){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
    
   fscanf(in,"%d\n",&count);
   Graph G = newGraph(count);
   fscanf(in,"%d %d\n",&num1,&num2);

   while(num1 != 0 && num2 != 0){
      addArc(G,num1,num2);
      fscanf(in,"%d %d\n",&num1,&num2);
   }
   fprintf(out,"Adjacency list representation of G:\n");
   printGraph(out,G);
   fprintf(out,"\n");
   
   List listG = newList();
   for(int i = 1; i <= getOrder(G); i++){
      append(listG,i);
   }
   DFS(G,listG);
   Graph GT = transpose(G);
   DFS(GT,listG);
   fprintf(out,"\n");

   count = 0;
   moveBack(listG);
   while(index(listG) != -1){
      if(getParent(GT,get(listG)) == NIL){
         count++;
      }
      movePrev(listG);
   }
   fprintf(out,"G contains %d strongly connected components:\n",count);
   for(int i = 1; i <= count; i++){
      int nilNum = 0;
      bool found = false;
      fprintf(out,"Component %d:",i); 
      moveBack(listG);
      while(nilNum != i && !found){
         if(getParent(GT,get(listG)) == NIL){
            nilNum++;
            if(nilNum == i){
               fprintf(out, " %d",get(listG));
               moveNext(listG);
               found = true;
               while(index(listG) != -1 && getParent(GT,get(listG)) != NIL){
                  fprintf(out, " %d",get(listG));
                  moveNext(listG);
               }
            }
         }
         if(!found){
            movePrev(listG);
         }
      }
      if(i != count){
         fprintf(out,"\n");
      }
   }
   fclose(in);
   fclose(out);
   freeGraph(&G);
   freeGraph(&GT);
   freeList(&listG);
   return(0);
}
