#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;


void* heap_top(Heap* pq){
  if (pq->size>0){
    return pq->heapArray[0].data;
  }
  return NULL;
}



void heap_push(Heap* pq, void* data, int priority){

  pq->size++;
  if(pq->size>=pq->capac){
    pq->capac = pq->capac*2 + 1;
    heapElem* newArray = (heapElem*)malloc(pq->capac * sizeof(heapElem));
    for (int i = 0; i<pq->size; i++){
      newArray[i]=pq->heapArray[i];
    }
    pq->heapArray = newArray;
  }
  int y =pq->size-1;
  pq->heapArray[y].data=data;
  pq->heapArray[y].priority=priority;
  while(1){
    if (pq->heapArray[(int)((y-1)/2)].priority < priority){
      pq->heapArray[y].data= pq->heapArray[(int)((y-1)/2)].data;
      pq->heapArray[y].priority= pq->heapArray[(int)((y-1)/2)].priority;
      pq->heapArray[(int)((y-1)/2)].data = data;
      pq->heapArray[(int)((y-1)/2)].priority = priority;
      y = ((y-1)/2);
      if (y<=0) break;
    }
    else break;
  }
}

void heap_pop(Heap* pq){
  pq->size--;
  pq->heapArray[0]=pq->heapArray[pq->size];
  pq->heapArray[pq->size].priority=0;
  int x = 0;
  void* data;
  int priority;
  while(x<pq->size && (x*2)+2 <pq->capac){
    if(pq->heapArray[x].priority < pq->heapArray[x*2 +1].priority || pq->heapArray[x].priority < pq->heapArray[x*2 +2].priority ){
      if (pq->heapArray[x*2 +1].priority > pq->heapArray[x*2 +2].priority){
        data = pq->heapArray[x*2 +1].data;
        priority = pq->heapArray[x*2 +1].priority;
        pq->heapArray[x*2 +1]= pq->heapArray[x];
        pq->heapArray[x].data = data;
        pq->heapArray[x].priority=priority;
        x = x*2 +1;
      }
      else{
        data = pq->heapArray[x*2 +2].data;
        priority = pq->heapArray[x*2 +2].priority;
        pq->heapArray[x*2 +2]= pq->heapArray[x];
        pq->heapArray[x].data = data;
        pq->heapArray[x].priority=priority;
        x = x*2 +2;
      }
    }
    else{
      break;
    }
  }
}

Heap* createHeap(){
  Heap* new = (Heap*)malloc(sizeof(Heap));
  new->heapArray = (heapElem*)malloc(3 * sizeof(heapElem));
  new->size = 0;
  new->capac = 3;
  return new;
}
