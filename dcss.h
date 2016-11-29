#ifndef DCSS_H_
#define DCSS_H_

/*
 * CAS(*a,b,c)
 *  atomic{
 *    oldval = *a
 *    if(*a == b){
 *      *a = c
 *    }
 *    return oldval
 *  }
 *
 */
#define CAS(a,b,c) (__sync_val_compare_and_swap(a,b,c))

/*
 * dcss
 *  atomic{
 *    if(**ca == *co){
 *      CAS(*a, *o, *n);
 *    }
 *  }
 *
 */
typedef struct dcss_descriptor{
  void **a;
  void  *o;
  void  *n;
  void **ca;
  void  *co;
} dcss_descriptor;

// dcss descriptor flag
//   address on 2nd bit from lower
#define IS_DCSS_DESC(i)     ((int)(((unsigned long)i) &  0x2L))
#define SET_DCSS_DESC(i)    ((dcss_descriptor*)(( ((unsigned long)i) |  0x2L )))
#define CLEAR_DCSS_DESC(i)  ((dcss_descriptor*)(  ((unsigned long)i) & ~0x2L ))

void *dcss(void **a, void *o, void *n, void **ca, void *co);
void *dcss_exec(dcss_descriptor *dd);
void *dcss_read(void *addr);
void  dcss_write(dcss_descriptor *dd);

#endif
