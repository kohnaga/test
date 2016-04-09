#include "quick_sort.h"

#define STACKSIZE (100)
#define DATA_SIZE (1024)
#define THRESHOLD (10)

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
    size_t i, j, left, right, p;
    size_t lstack[STACKSIZE], rstack[STACKSIZE];
    size_t pivot;
    size_t num;
    
    left = (size_t)data;
    right = (size_t)((char*)data + (data_cnt - 1) * data_size);
    p = 0;
    
    for( ; ; ){
        num = ((right - left)/data_size) + 1;
        if(num < THRESHOLD){
            if(p == 0) break;
            p--;
            left = lstack[p];
            right = rstack[p];
        }
        num = ((right - left)/data_size) + 1;
        pivot = (size_t)((char*)left + (num/2) * data_size);
        i = left; j = right;
        for( ; ; ){
            while (func((const void *)i, (const void * )pivot) < 0) i += data_size;
            while (func((const void *)j, (const void * )pivot) > 0) j -= data_size;
            if(i >= j) break;
            my_memswap((void *)i, (void *)j, data_size);
            i += data_size;
            j -= data_size;
        }
        if(i - left > right - j){
            num = ((i - left)/data_size) + 1;
            if(num > THRESHOLD){
                lstack[p] = left;
                rstack[p] = i - data_size;
                p++;
            }
            left = j + data_size;
        }else{
            num = ((right - j)/data_size) + 1;
            if(num > THRESHOLD){
                lstack[p] = j + data_size;
                rstack[p] = right;
                p++;
            }
            right = i - data_size;
        }
    }
    my_insertsort(data, data_cnt, data_size, func);
}
