#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//Sono un update

void merge(int *A, int start, int center,int end, int *num_op);
void merge_sort(int *A, int start, int end, int *num_op);

void swap(int *A, int n, int m){
    
    int temp = A[n];
    A[n] = A[m];
    A[m] = temp;

}

void algoritmo(int *A, int len, int *num_op){
    
    int op_count = 0;
    
    for(int i=0;i<len;i++){
        
        for(int j=0;j<len-i-1;j++){
            
            if(A[j]>A[j+1]){
                
                swap(A,j,j+1);
                op_count++;
            }
        }
        
    }
    
    *num_op = op_count;
}

void algoritmo_merge_sort(int *A, int len, int *num_op){
    
    *num_op = 0;
    merge_sort(A,0,len-1,num_op);
    
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

void print_array(int *A, int len){
    printf("[");
    for(int i=0;i<len;i++)
        printf("%d ", A[i]);
    printf("]");
}

int main(void) {
 // your code goes here
 int input[]={15,9,1,0,5,4,7,8,3,1,2,0,3,2,4,6,0};
 int pointer = 0;
 
 while(input[pointer] != 0){
     
     int *array = malloc(sizeof(int)*input[pointer]);
     
     for(int i = 0;i<input[pointer];i++){
         
         array[i]=input[pointer+i+1];
         
     }
     int numero = 0;

     algoritmo_merge_sort(array,input[pointer],&numero);
     //algoritmo(array,input[pointer],&numero);
     printf("%d\n",numero);
     pointer += input[pointer]+1;
     
 }
 
 return 0;
}