#include "dcss.h"
#include <stdio.h>
#include <stdlib.h>

// [attention]
//   IS_DCSS_DESC macro heavily depends on address alignment
//   DCSS can be only applied to rewrite address such as int* and (struct node)*

void *dcss(void **a, void *o, void *n, void **ca, void *co){
  void *r;
  dcss_descriptor *dd;

  dd = (dcss_descriptor*)malloc(sizeof(dcss_descriptor));
  dd->a  = a;
  dd->o  = o;
  dd->n  = n;
  dd->ca = ca;
  dd->co = co;

  r = dcss_exec(SET_DCSS_DESC(dd));
  free(dd);

  return r;
}

void *dcss_exec(dcss_descriptor *dd){
  void *r;
  dcss_descriptor *ddc = CLEAR_DCSS_DESC(dd);
  do{
    r = (void*)CAS(ddc->a,ddc->o,dd);
    if(IS_DCSS_DESC(r)){
      dcss_write((dcss_descriptor*)r);
    }
  }while(IS_DCSS_DESC(r));
  if(r == ddc->o){
    dcss_write(dd);
  }
  return r;
}

// void *addr
//  -> return real data with type (void*)
void *dcss_read(void *addr){
  void *r;
  do{
    r = addr;
    if(IS_DCSS_DESC(r))
      dcss_write(r);
  }while(IS_DCSS_DESC(r));
  return r;
}

void dcss_write(dcss_descriptor *dd){
  dcss_descriptor *ddc = CLEAR_DCSS_DESC(dd);
  void *val = *(ddc->ca);
  if(val == (ddc->co)){
    CAS((ddc->a), dd, (ddc->n));
  }else{
    CAS((ddc->a), dd, (ddc->o));
  }
}
