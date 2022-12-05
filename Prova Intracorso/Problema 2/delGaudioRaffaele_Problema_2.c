/*
* La complessità si ricava dal numero di chiamate che vengono fatte ad ogni livello dell'albero e
* sono dipendenti dal numero di numeri primi compresi tra l'ultimo elemento della soluzione parziale ed S
* In linea generale, essendo un'esplorazione di simil-permutazioni di n elementi mi aspetto una complessità O(2^n).
*/
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void findAllSequences(int S, int N, int P);
void find_all_sequences(int S, int N, int P, int *partial_solution, int sol_size);
void construct_candidates(int *partial_solution, int sol_size, int P, int S, int *array_of_candidates, int *n_candidates);
bool is_prime(int N);
bool check_sum(int *A, int A_size, int sum);
void printArray(int *A, int len);

int main()
{
    int n_tests;
    int S, N, P;
    scanf("%d",&n_tests);

    for (int i = 0; i < n_tests; i++)
    {
        scanf("%d",&S);
        scanf("%d",&N);
        scanf("%d",&P);
        printf("CASO DI TEST %d\n",i+1);
        findAllSequences(S,N,P);
    }

}

void findAllSequences(int S, int N, int P)
{
    int *partial_solution = malloc(sizeof(int)*N);
    if (!partial_solution)
    {
        exit(-1);
    }
    
    find_all_sequences(S,N,P,partial_solution,0);
}

void find_all_sequences(int S, int N, int P, int *partial_solution, int sol_size)
{

    // Controllo se è una soluzione
    if (sol_size >= N)
    {
        if (check_sum(partial_solution,sol_size,S))
        {
            printArray(partial_solution,sol_size);
        }
        return;
    }
    
    int *candidates = malloc(sizeof(int)*S);
    if (!candidates)
    {
        exit(-1);
    }

    int n_candidates;
    construct_candidates(partial_solution,sol_size,P,S,candidates,&n_candidates);

    for (int i = 0; i < n_candidates; i++)
    {
        partial_solution[sol_size] = candidates[i];
        find_all_sequences(S,N,P,partial_solution,sol_size+1);
    }
    free(candidates);

}

void construct_candidates(int *partial_solution, int sol_size, int P, int S, int *array_of_candidates, int *n_candidates)
{
    int count = 0;
    
    if (sol_size == 0)
    {
        for (int i = P+1; i <= S; i++)
        {
            if (is_prime(i))
            {
                array_of_candidates[count] = i;
                count++;
            }
            
        }
    }
    else
    {
        for (int i = partial_solution[sol_size-1]+1; i <= S; i++)
        {
            if (is_prime(i))
            {
                array_of_candidates[count] = i;
                count++;
            }
        }
    }
    *n_candidates = count;
}

bool is_prime(int N)
{
    int c;
    for ( c = 2 ; c <= N - 1 ; c++)
    {
        if ( N%c == 0 )
        return false;
    }
    return true;
}

bool check_sum(int *A, int A_size, int sum)
{
    int my_sum = 0;
    
    for (int i = 0; i < A_size; i++)
        my_sum = my_sum + A[i];

    return my_sum == sum ? true : false;
}

void printArray(int *A, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%d ",A[i]);
    }
    printf("\n");
}