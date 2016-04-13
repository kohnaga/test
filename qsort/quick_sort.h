#ifndef quick_sort_h
#define quick_sort_h

#include <stdio.h>

void test_qsort(
           void * data,
           size_t data_cnt,
           size_t data_size,
           int( * func )( const void * , const void *)
           );

void quick(int a[], int left, int right);


#endif /* quick_sort_h */
