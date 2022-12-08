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

void print_elephant(elephant_t elephant);
void print_array(elephant_t *A, int len);

void construct_candidates(elephant_t *A, int A_size, elephant_t *partial_solution, int sol_size,
                          elephant_t *candidates, int *n_candidates_found);
void max_elephant_sequence(elephant_t *A, int A_size, elephant_t *partial_solution, int sol_size,
                           int *best_solution, int *best_sol_size);
void print_int_array(int *A, int len);

#define MAX_LENGTH 1000

int main(){

    char buffer[12];

    elephant_t A[MAX_LENGTH];

    int A_size = 0;
    while ((fgets(buffer,sizeof(buffer),stdin) != NULL) && buffer[0] != '\n')
    {   
        sscanf(buffer,"%d %d",&A[A_size].size,&A[A_size].iq);
        A[A_size].index = A_size+1;
        A_size++;
    }

    elephant_t partial_solution[MAX_LENGTH];
    int R[MAX_LENGTH];
    int R_best[MAX_LENGTH];
    int R_best_size = 0;
    int R_size = 0;
    for (int i = 0; i < A_size; i++)
    {
        partial_solution[0] = A[i];
        max_elephant_sequence(A,A_size,partial_solution,1,R,&R_size);
        if (R_size > R_best_size)
        {
            for (int i = 0; i < R_size; i++)
            {
                R_best[i] = R[i];
            }
            R_best_size = R_size;
            
        }
        R_size = 0;
        
    }

    printf("%d\n",R_best_size);
    for (int i = 0; i < R_best_size; i++)
    {
        printf("%d\n",R_best[i]);
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

void print_int_array(int *A, int len){
    
    printf("[ ");
    for (int i = 0; i < len; i++)
    {
        printf("%d ",A[i]);
    }
    printf("]\n");
    
}

void max_elephant_sequence(elephant_t *A, int A_size, elephant_t *partial_solution, int sol_size, int *best_solution, int *best_sol_size){

    elephant_t *candidates = malloc(sizeof(elephant_t)*MAX_LENGTH);
    if (!candidates)
    {
        exit(-1);
    }
    int n_candidates;

    construct_candidates(A,A_size,partial_solution,sol_size,candidates,&n_candidates);
    if (n_candidates == 0 && sol_size > *best_sol_size)
    {
        *best_sol_size = sol_size;
        for (int i = 0; i < sol_size; i++)
        {
            best_solution[i] = partial_solution[i].index;
        }
        
    }

    for (int i = 0; i < n_candidates; i++)
    {
        partial_solution[sol_size] = candidates[i];
        max_elephant_sequence(A,A_size,partial_solution,sol_size+1,best_solution,best_sol_size);
    }

    free(candidates);
    
}

void construct_candidates(elephant_t *A, int A_size, elephant_t *partial_solution, int sol_size,
                          elephant_t *candidates, int *n_candidates_found){

    int count = 0;
    for (int i = 0; i < A_size; i++)
    {
        if (A[i].size > partial_solution[sol_size-1].size && A[i].iq < partial_solution[sol_size-1].iq)
        {
            candidates[count] = A[i];
            count++;
        }
        
    }

    *n_candidates_found = count;
    
}