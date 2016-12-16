#ifndef NCAS_H_
#define NCAS_H_

#include "dcss.h"

#define UNDECIDED 0
#define FAILED    1
#define SUCCEEDED 2

/*
 * dcas
 *  atomic{
 *      CAS(a1, *(o1), *(n1));
 *      CAS(a2, *(o2), *(n2));
 *    }
 *  }
 *
 */


typedef struct dcas_descriptor{
  descriptortag descriptor;
  word_t status;
  void **a1;
  void *o1;
  void *n1;
  void **a2;
  void *o2;
  void *n2;
} dcas_descriptor;

// dcas descriptor flag
//   address on 2nd bit from lower
#define IS_DCAS_DESC(i)     ((int)(((unsigned long)i) &  0x2L) && CLEAR_DCAS_DESC(i)->descriptor == DCAS)
#define SET_DCAS_DESC(i)    ((dcas_descriptor*)(( ((unsigned long)i) |  0x2L )))
#define CLEAR_DCAS_DESC(i)  ((dcas_descriptor*)(  ((unsigned long)i) & ~0x2L ))


int   dcas(void **a1, void *o1, void *n1, void **a2, void *o2, void *n2);
int   dcas_exec(dcas_descriptor *dcd);
void *dcas_read(void *addr);


#endif
