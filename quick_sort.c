#include "quick_sort.h"

#define STACK_DPT (100)
#define DATA_SIZE (1024)

static void my_memswap(void *x, void *y, size_t n)
{
    unsigned char  *a = (unsigned char *)x;
    unsigned char  *b = (unsigned char *)y;
    
    for ( ; n--; a++, b++) {
        unsigned char  c = *a;
        *a = *b;
        *b = c;
    }
}

static void my_memcpy(void *frm, void *to, size_t n)
{
    unsigned char  *a = (unsigned char *)frm;
    unsigned char  *b = (unsigned char *)to;
    unsigned char  c;
    for ( ; n--; a++, b++) {
        c = *a;
        *b = c;
    }
}

void insertion
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
        my_memcpy( (void*)(data + (data_size * (i))), (void*)tmp, data_size );
        j=i;
        while(j > 0){
            cmp = (size_t)(data + data_size * (j-1));
            rtn = func((const void *) cmp, (const void * )&tmp);
            if(rtn > 0){
                my_memcpy((data + data_size * (j-1)), (data + data_size * j), data_size );
            }
            else{
                break;
            }
            j--;
        }
        my_memcpy((void *)tmp, (data + data_size * j), data_size);
    }
}

void my_quick
(
    void * data,
    size_t data_cnt,
    size_t data_size,
    int( * func )( const void * , const void *)
)
{
    int  ptr = 0;
    size_t lstack[STACK_DPT];
    size_t rstack[STACK_DPT];
    size_t left;
    size_t right;
    size_t org_left;
    size_t org_right;

    size_t pivot;
    size_t num;
    
    left = (size_t)data;
    right = (size_t)(data + (data_cnt - 1) * data_size);
    
    
    lstack[ptr] = left;
    rstack[ptr] = right;
    ptr++;
    
    while (ptr-- > 0) {
        left  = org_left = lstack[ptr];
        right = org_right = rstack[ptr];
        num = ((right - left)/data_size) + 1;
        
        pivot = (size_t)(data + (num/2) * data_size);
        
        if (num <= 9)
            insertion(data, data_cnt, data_size, func);
        else {
            do {
                while (func((const void *) left, (const void * )pivot) < 0) left += data_size;
                while (func((const void *) right, (const void * )pivot) > 0) right -= data_size;
                if (left <= right) {
                    my_memswap((void *)left, (void *)right, data_size);
                    left  += data_size;
                    right -= data_size;
                }
            } while (left <= right);
            
            if (org_right - left < right - org_left) {
                my_memswap((void *)left, (void *)org_left, data_size);
                my_memswap((void *)right, (void *)org_right, data_size);
            }
            if (left < org_right) {
                lstack[ptr] = left;
                rstack[ptr] = org_right;
                ptr++;
            }
            if (org_left < right) {
                lstack[ptr] = org_left;
                rstack[ptr] = right;
                ptr++;
            }
        }
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
    my_quick(data,data_cnt, data_size, func);
}
