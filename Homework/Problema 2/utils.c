#include <limits.h>
#include <stdlib.h>
#include <string.h>

void merge(int *A, int start, int center,int end, int *num_op){

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

/*
* Applies merge sort to the [A] vector starting from the [start]
* index to the [end] index.
* Optionally, if [num_op] != NULL, it will return the number of exchanges
* in positions that took place while executing the algorithm 
*/
void merge_sort(int *A, int start, int end, int *num_op){
    
    if(start < end){
        
        int center = (start + end)/2;
        merge_sort(A,start,center, num_op);
        merge_sort(A, center+1,end, num_op);
        merge(A,start,center,end, num_op);
        
    }

}

/*
* Return the index of highest index copy of [elem] in the ordered [A] vector
* starting from the [start] index to the [end] index,
* or -1 if [elem] is not present in [A]
*/
int binary_search(int *A, int start, int end, int elem){

    int center = (start + end)/2;

    if (end == start && A[start] != elem)
        return -1;
    

    if (A[center] < elem)
        return binary_search(A,center+1,end,elem);
    
    else if(A[center] > elem)
        return binary_search(A,start,center-1,elem);
    
    else{

        if (A[center + 1] == elem)
            return binary_search(A,center+1,end,elem);
        else
            return center + 1; 
    }

}

/*
* Given an int vector [A] of size [size], returns a vector [B]
* such that for each [A[i]], [B[i]] is equals to the number
* of elements of [A] that are less or equal of [A[i]]
*/
int *algoritmo_v1(int *A, int size){

    int *A_copy = malloc(sizeof(int)*size);
    
    // Copy of A into A_copy => O(n)
    for (size_t i = 0; i < size; i++)
        A_copy[i] = A[i];

    // Merge sort of A_copy => O(nlog(n))
    merge_sort(A_copy,0,size-1,NULL);

    int *B = malloc(sizeof(int)*size);

    // Iteration over A and binary-search of each A[i] into A_copy => O(nlog(n))
    for (size_t i = 0; i < size; i++)
        B[i] = binary_search(A_copy,0,size-1,A[i]);

    return B;

    // Total cost T(n) = O(n + 2nlog(n)) = O(nlog(n))
        
}