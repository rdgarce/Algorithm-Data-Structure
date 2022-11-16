#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct elephant_t 
{
    int index;
    int size;
    int iq;
}elephant_t;

elephant_t ELEPHANT_MAX = {
        .index = INT_MAX,
        .size = INT_MAX,
        .iq = INT_MAX
    };

/*
* Ordino gli elefanti in ordine crescente rispetto al peso e poi scorro l'array
* e individuo la sottostringa massima che contiene un iq descrescente
*/ 

void merge_sort_by_size(elephant_t *A, int start, int end, int *num_op);
void merge(elephant_t *A, int start, int center,int end, int *num_op);
void max_substring_of_elephants(elephant_t *A, int A_size, int *R, int *R_size);
void max_substring_of_elephants_v2(elephant_t *A, int A_size, int *R, int *R_size);

void print_elephant(elephant_t elephant);
void print_array(elephant_t *A, int len);

#define MAX_LENGTH 1000

int main(){

    char buffer[12];

    elephant_t array[MAX_LENGTH];
    int R[MAX_LENGTH];
    int size;


    int index = 0;
    while ((fgets(buffer,sizeof(buffer),stdin) != NULL))
    {   
        if (sscanf(buffer,"%d %d",&array[index].size,&array[index].iq) != 2)
            break;
        array[index].index = index+1;
        index++;
    }

    print_array(array,index);
    merge_sort_by_size(array,0,index-1,NULL);
    printf("\n");
    print_array(array,index);


    max_substring_of_elephants_v2(array,index,R,&size);

    for (int i = 0; i < size; i++)
    {
        printf("%d ",R[i]);
    }
    
    

}

void merge(elephant_t *A, int start, int center,int end, int *num_op){

    int n1 = center-start+1;
    int n2 = end-center;
    int op_count = 0;
    
    elephant_t *L =malloc(sizeof(elephant_t)*(n1+1));
    elephant_t *R =malloc(sizeof(elephant_t)*(n2+1));

    for(int i = 0; i < n1; i++)
        L[i] = A[i + start];
    
    L[n1] = ELEPHANT_MAX;
    
    for(int i = 0; i < n2; i++)
        R[i] = A[i + center+1];

    R[n2] = ELEPHANT_MAX;

    int l_index = 0;
    int r_index = 0;
    for(int i=start;i <= end; i++){
        
        if(L[l_index].size <= R[r_index].size){
            A[i] = L[l_index];
            l_index++;
        }
        else{
            A[i] = R[r_index];
            r_index++;
            if(L[l_index].size != ELEPHANT_MAX.size)
                op_count += n1-l_index;
                
        }
        
    }
    
    if(num_op)
        *num_op += op_count;

    free(L);
    free(R);
}

void merge_sort_by_size(elephant_t *A, int start, int end, int *num_op){
    
    if(start < end){
        
        int center = (start + end)/2;
        merge_sort_by_size(A,start,center, num_op);
        merge_sort_by_size(A, center+1,end, num_op);
        merge(A,start,center,end, num_op);
        
    }

}

void print_elephant(elephant_t elephant){
    printf("{index = %d, size = %d, iq = %d}",elephant.index,elephant.size, elephant.iq);
}

void print_array(elephant_t *A, int len){
    for (int i = 0; i < len; i++)
    {
        print_elephant(A[i]);
        printf(" ");
    }
    printf("\n");
    
}

/*
* Supposto A ordinato in base alla size, torna la sottolista che rispetta il vincolo sull'IQ
*/
void max_substring_of_elephants(elephant_t *A, int A_size, int *R, int *R_size){

    int start_index = 0;
    int current_index = 0;

    int best_start_index = 0;
    int best_current_index = 0;

    int size = 0;
    int best_size = 0;

    for (int i = 1; i < A_size; i++)
    {
        if (A[i].iq < A[current_index].iq)
        {
            printf("Sono su con i=%d e current_index=%d\n",i,current_index);
            current_index = i;
            continue;
        }
        
        if(A[i].iq >= A[current_index].iq || i == A_size-1)
        {   
            printf("Sono giu con i=%d e current_index=%d\n",i,current_index);
            size = current_index - start_index+1;
            if (size > best_size)
            {
                best_size = size;
                best_start_index = start_index;
                best_current_index = current_index;
            }
            start_index = i;
            current_index = i;
        }  
    }

    printf("(%d,%d)\n",best_start_index,best_current_index);

    for (int i = best_start_index; i <= best_current_index; i++)
    {
        R[i-best_start_index] = A[i].index;
    }

    *R_size = best_size;

}

/*
* V2: Supposto A ordinato in base alla size, torna la sottolista che rispetta il vincolo sull'IQ
*/
void max_substring_of_elephants_v2(elephant_t *A, int A_size, int *R, int *R_size){

    int r_current = 0;
    int a_current = 0;
    for (int i = 1; i < A_size; i++)
    {
        if (A[a_current].iq > A[i].iq && i != A_size - 1)
        {
            R[r_current] = A[a_current].index;
            r_current++;
            a_current = i;
            
        }
        else if (A[a_current].iq > A[i].iq && i == A_size - 1)
        {
            R[r_current] = A[a_current].index;
            r_current++;
            R[r_current] = A[i].index;
            r_current++;
        }
        else
        {
            a_current++;
        }

    }

    *R_size = r_current;

}