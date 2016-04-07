#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "quick_sort.h"

#define NUM (1800)

typedef struct test_struct{
    int end;
    int start;
}test_struct;


int compare_int(const void * a, const void * b){
    int a_int = *(int*)a;
    int b_int = *(int*)b;
    
    return a_int - b_int;
    
}

int compare_struct(const void * a, const void * b){
    test_struct a_struct = *(test_struct*)a;
    test_struct b_struct = *(test_struct*)b;
    
    return a_struct.start - b_struct.start;
    
}

int main(int argc, const char * argv[]) {
    int i;
    
    test_struct array[NUM];
    
    srand((unsigned)time(NULL));
    for(i=0;i<NUM;i++)    array[i].start = rand()%100;
    for(i=0; i <NUM; i++){
        printf("%d ", array[i].start );
        if(i == NUM -1) printf("\n\n");
    }
    test_qsort(array, NUM, sizeof(test_struct), compare_struct);
    for(i=0; i <NUM; i++){
        printf("%d ", array[i].start);
        if(i == NUM -1) printf("\n");
    }
    
    return 0;
}
