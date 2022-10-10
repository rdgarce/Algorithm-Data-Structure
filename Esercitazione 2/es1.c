#include <stdio.h>
#include <limits.h>

void algoritmo(int *A, int len, int *sum, int *start, int *end);

int main(){

    int array[] = {-7, 5, -1,-6,-1,6};
    int size = sizeof(array)/sizeof(array[0]);

    int sum;
    int start;
    int end;
    algoritmo(array,size, &sum, &start, &end);

    printf("Sottoarray con somma massima ha somma = %d e ha start = %d ed end = %d\n", sum, start, end);
}

void algoritmo(int *A, int len, int *sum, int *start, int *end){

    int definitive_sum = INT_MIN;
    int current_sum = 0;
    
    int negative_count = 0;
    int max_elem = INT_MIN;
    int max_elem_pos = -1;

    int my_start = 0;
    int my_end = 0;

    for (int i = 0; i < len; i++){

        my_end = i;
        
        if(A[i] < 0)
            negative_count++;
        
        if(A[i] > max_elem){
            max_elem = A[i];
            max_elem_pos = i;
        }

        current_sum += A[i];

        if (current_sum > definitive_sum)
            definitive_sum = current_sum;
        
        if (current_sum < 0){
            my_start = i+1;
            my_end = i+1;
            current_sum = 0;
        }

    }
    

    if (negative_count == len){
        *sum = max_elem;
        *start = *end = max_elem_pos;
        return;
    }
 
    *sum = definitive_sum;
    *start = my_start;
    *end = my_end;
    return;
    
}
