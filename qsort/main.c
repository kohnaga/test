#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "quick_sort.h"

#define NUM (1000000)

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
    
    int array[NUM];
    
    srand((unsigned)time(NULL));
    for(i=0;i<NUM;i++)    array[i] = rand()%NUM;
    for(i=0; i <NUM; i++){
        printf("%d ", array[i] );
        if(i == NUM -1) printf("\n\n");
    }
    test_qsort(array, NUM, sizeof(int), compare_int);
    //quick(&array, 0, NUM - 1);
    for(i=0; i <NUM; i++){
        printf("%d ", array[i]);
        if(i == NUM -1) printf("\n");
    }
    
    return 0;
}
