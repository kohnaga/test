#include "quick_sort.h"

#define STACKSIZE (100)
#define DATA_SIZE (1024)
#define THRESHOLD (10)


static void my_swap
(
    void * x,
    void * y
)
{
    size_t t;
    size_t *a = (size_t *)x;
    size_t *b = (size_t *)y;
    t = *a;
    *a = *b;
    *b = t;
}

static void my_memswap
(
    void *x,
    void *y,
    size_t n
)
{
    unsigned char  *a = (unsigned char *)x;
    unsigned char  *b = (unsigned char *)y;
    if(a == b) return;
    
    for ( ; n--; a++, b++) {
        unsigned char  c = *a;
        *a = *b;
        *b = c;
    }
}

static void my_memcpy
(
    void *frm,
    void *to,
    size_t n
)
{
    unsigned char  *a = (unsigned char *)frm;
    unsigned char  *b = (unsigned char *)to;
    unsigned char  c;
    if(a == b) return;
    
    for ( ; n--; a++, b++) {
        c = *a;
        *b = c;
    }
}

void my_insertsort
(
    void * data,
    size_t data_cnt,
    size_t data_size,
    int( * func )( const void * , const void *)
)
{
    int i, j;
    size_t cmp;
    int rtn;
    char tmp[DATA_SIZE];
    
    for(i = 1; i < data_cnt; i++){
        my_memcpy( (void*)((char*)data + (data_size * (i))), (void*)tmp, data_size );
        j=i;
        while(j > 0){
            cmp = (size_t)((char*)data + data_size * (j-1));
            rtn = func((const void *) cmp, (const void * )&tmp);
            if(rtn > 0){
                my_memcpy(((char*)data + data_size * (j-1)), ((char*)data + data_size * j), data_size );
            }
            else{
                break;
            }
            j--;
        }
        my_memcpy((void *)tmp, ((char*)data + data_size * j), data_size);
    }
}

void test_qsort
(
    void * data,
    size_t data_cnt,
    size_t data_size,
    int( * func )( const void * , const void *)
)
{
    int  ptr = 0;
    size_t lstack[STACKSIZE];
    size_t rstack[STACKSIZE];
    size_t left;
    size_t right;
    size_t pl;
    size_t pr;
    
    size_t pivot;
    size_t num;
    
    left = (size_t)data;
    right = (size_t)(data + (data_cnt - 1) * data_size);
    
    
    lstack[ptr] = left;
    rstack[ptr] = right;
    ptr++;
    
    while (ptr-- > 0) {
        left  = pl = lstack[ptr];
        right = pr = rstack[ptr];
        
        num = ((right - left)/data_size) + 1;
        pivot = (size_t)((char *)left + (num/2) * data_size);
        
        if (num <= THRESHOLD)
            my_insertsort((void*)left, num, data_size, func);
        else {
            do {
                while (
                       func((const void *) pl, (const void * )pivot) < 0
                       &&
                       pl + data_size <= right
                       )
                    pl += data_size;
                while (
                       func((const void *) pr, (const void * )pivot) > 0
                       &&
                       pr - data_size >= left
                       )
                    pr -= data_size;
                if (pl <= pr) {
                    my_memswap((void *)pl, (void *)pr, data_size);
                    pl += data_size;
                    pr -= data_size;
                }
            } while (pl <= pr);
            
            if (pr - left < right - pl) {
                my_swap(&left, &pl);
                my_swap(&right, &pr);
            }
            if (left < pr) {
                lstack[ptr] = left;
                rstack[ptr] = pr;
                ptr++;
            }
            if (pl < right) {
                lstack[ptr] = pl;
                rstack[ptr] = right;
                ptr++;
            }
        }
    }
}
