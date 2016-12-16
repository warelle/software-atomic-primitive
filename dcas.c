#include "dcas.h"
#include <stdlib.h>


// [attention]
//   IS_DCSS_DESC macro heavily depends on address alignment
//   DCSS can be only applied to rewrite address such as int* and (struct node)*
int dcas(void **a1, void *o1, void *n1, void **a2, void *o2, void *n2){
  int r;
  dcas_descriptor *dcd;

  dcd = (dcas_descriptor*)malloc(sizeof(dcas_descriptor));
  dcd->descriptor = DCAS;
  dcd->status = UNDECIDED;
  dcd->a1 = a1;
  dcd->o1 = o1;
  dcd->n1 = n1;
  dcd->a2 = a2;
  dcd->o2 = o2;
  dcd->n2 = n2;

  r = dcas_exec(SET_DCAS_DESC(dcd));
  free(dcd);

  return r;
}

int dcas_exec(dcas_descriptor *dcd){
  dcas_descriptor *dcdc = CLEAR_DCAS_DESC(dcd);
  if(dcdc->status == UNDECIDED){
    word_t status = SUCCEEDED;
retry1:;
    void *val  = dcss(dcdc->a1, dcdc->o1, (void*)dcd, &dcdc->status, UNDECIDED);
    if(IS_DCAS_DESC(val)){
      if(val != dcd){
        dcas_exec(val);
        goto retry1;
      }
    }else if(val != dcdc->o1){
      status = FAILED;
    }
retry2:;
    if(status == SUCCEEDED){
      val = dcss(dcdc->a2, dcdc->o2, (void*)dcd, &dcdc->status, UNDECIDED);
      if(IS_DCAS_DESC(val)){
        if(val != dcd){
          dcas_exec(val);
          goto retry2;
        }
      }else if(val != dcdc->o2){
        status = FAILED;
      }
    }

    CAS(&dcdc->status, UNDECIDED, status);
  }

  // retrievement
  int suc = (dcdc->status == SUCCEEDED);
  CAS(dcdc->a1, dcd, suc ? dcdc->n1 : dcdc->o1);
  CAS(dcdc->a2, dcd, suc ? dcdc->n2 : dcdc->o2);

  return suc;
}

void *dcas_read(void *addr){
  void *r = NULL;
  do{
    r = dcss_read(addr);
    if(IS_DCAS_DESC(r)){
      dcas_exec(r);
    }
  }while(IS_DCAS_DESC(r));
  return r;
}

