#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

/*
* Apply mergesort on the int vector [A] starting 
* from the [start] index to the [end] index.
* If [num_op] != NULL, then the number of exchanges
* performed by the algorithm will be copied in [num_op]
*/
void mergeSort(int *A, int start, int end, int *num_op);
void _merge(int *A, int start, int center,int end, int *num_op);
void _merge_sort(int *A, int start, int end, int *num_op);
void printArray(int *A, int len);

void _merge(int *A, int start, int center,int end, int *num_op){
    

    int n1 = center-start+1;
    int n2 = end-center;
    int op_count = 0;
    
    int *L =malloc(sizeof(int)*(n1+1));
    int *R =malloc(sizeof(int)*(n2+1));

    for(int i = 0; i < n1; i++)
        L[i] = A[i + start];
    
    L[n1] = INT_MAX;
    
    for(int i = 0; i < n2; i++)
        R[i] = A[i + center+1];

    R[n2] = INT_MAX;

    int l_index = 0;
    int r_index = 0;
    for(int i=start;i <= end; i++){
        
        if(L[l_index] <= R[r_index]){
            A[i] = L[l_index];
            l_index++;
        }
        else{
            A[i] = R[r_index];
            r_index++;
            if(L[l_index] != INT_MAX)
                op_count += n1-l_index;
                
        }
        
    }
    

    if(num_op)
        *num_op += op_count;

    free(L);
    free(R);
}

void _merge_sort(int *A, int start, int end, int *num_op){
    
    if(start < end){
        
        int center = (start + end)/2;
        _merge_sort(A,start,center, num_op);
        _merge_sort(A, center+1,end, num_op);
        _merge(A,start,center,end, num_op);
        
    }

}

void mergeSort(int *A, int start, int end, int *num_op){
    int n_op = 0;
    _merge_sort(A,start,end,&n_op);
    if (num_op)
    {
        *num_op = n_op;
    }
    
}

void printArray(int *A, int len){
    
    printf("[ ");
    for (int i = 0; i < len; i++)
    {
        printf("%d ",A[i]);
    }
    printf("]\n");
    
}