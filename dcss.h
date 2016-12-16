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
typedef unsigned long descriptortag;
#define DCSS 0
#define DCAS 1

typedef unsigned long word_t;

typedef struct dcss_descriptor{
  descriptortag descriptor;
  void **a;
  void  *o;
  void  *n;
  word_t *ca;
  word_t  co;
} dcss_descriptor;

// dcss descriptor flag
//   address on 2nd bit from lower
#define IS_DCSS_DESC(i)     ((int)(((unsigned long)i) &  0x2L) && CLEAR_DCSS_DESC(i)->descriptor == DCSS)
#define SET_DCSS_DESC(i)    ((dcss_descriptor*)(( ((unsigned long)i) |  0x2L )))
#define CLEAR_DCSS_DESC(i)  ((dcss_descriptor*)(  ((unsigned long)i) & ~0x2L ))

void *dcss(void **a, void *o, void *n, word_t *ca, word_t co);
void *dcss_exec(dcss_descriptor *dd);
void *dcss_read(void *addr);
void  dcss_write(dcss_descriptor *dd);

#endif
