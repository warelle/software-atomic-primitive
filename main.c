#include <stdio.h>
#include "dcss.h"

#define DSIZE 16

int main(){
  int data[DSIZE];
  int *p1, *p2;

  p1 = data;
  p2 = data+4;

  for(int i=0; i<DSIZE; i++)
    printf("[%d] %p\n", i,data+i);

  printf("----------------\n");
  printf("p1:%p\n", p1);
  printf("p2:%p\n", p2);

  dcss((void**)&p1, (void*)data, (void*)(data+2), (void**)&p2, (void*)(data+4));

  printf("----------------\n");
  printf("p1:%p\n", p1);
  printf("p2:%p\n", p2);
  printf("----------------\n");

  return 0;
}
