#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int civic_number(int *civics, int c_size);
void merge(int *A, int start, int center,int end, int *num_op);
void merge_sort(int *A, int start, int end, int *num_op);

// Errato poiché si doveva calcolare la mediana. Risolto.

int main(){

    int n_tests;
    int civic_size;
    int result;
    scanf("%d",&n_tests);
    for (int i = 0; i < n_tests; i++)
    {
        
        scanf("%d",&civic_size);
        int *civics = malloc(sizeof(int)*civic_size);

        for (int i = 0; i < civic_size; i++)
        {
            scanf("%d",&civics[i]);
        }
        
        result = civic_number(civics,civic_size);
        printf("%d\n",result);
        free(civics);
    }
    
}

int civic_number(int *civics, int c_size){

    
    merge_sort(civics,0,c_size-1,NULL);
    
    int median_civic = (c_size % 2) == 0 ? (civics[c_size/2 - 1] + civics[c_size/2])/2 : civics[c_size/2];

    int sum = 0;
    for (int i = 0; i < c_size; i++)
    {
        sum = sum + abs(median_civic-civics[i]);
    }

    return sum;

}

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

void merge_sort(int *A, int start, int end, int *num_op){
    
    if(start < end){
        
        int center = (start + end)/2;
        merge_sort(A,start,center, num_op);
        merge_sort(A, center+1,end, num_op);
        merge(A,start,center,end, num_op);
        
    }

}