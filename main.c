#include <stdio.h>
#include "dcss.h"
#include "dcas.h"

#define DSIZE 16

int main(){
  long data[DSIZE];
  int *p1, *p2, *p3, *p4;

  p1 = data;
  p2 = data+4;

  for(int i=0; i<DSIZE; i++){
    data[i] = i;
    printf("[%d] %p\n", i,data+i);
  }

  printf("----------------\n");
  printf("p1:%p\n", p1);
  printf("p2:%p\n", p2);

  dcss((void**)&p1, (void*)data, (void*)(data+2), p2, *p2);

  printf("----------------\n");
  printf("p1:%p\n", p1);
  printf("p2:%p\n", p2);
  printf("----------------\n");


  p3 = data+2;
  p4 = data+6;

  printf("----------------\n");
  printf("p3:%p\n", p3);
  printf("p4:%p\n", p4);
  printf("----------------\n");

  dcas((void**)&p3, (void*)(data+2), (void*)(data+5), (void**)&p4, (void*)(data+6), (void*)(data+9));

  printf("----------------\n");
  printf("p3:%p\n", p3);
  printf("p4:%p\n", p4);
  printf("----------------\n");


  return 0;
}
