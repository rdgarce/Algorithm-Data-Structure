#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void printArray(int *A, int len);
void ring_composer_bt(int N, int *partial_solution, int sol_size, bool *visited);
void construct_candidates(int N, int *partial_solution, int sol_size, bool *visited, int *candidates, int *c_size);
bool is_prime(int n);
void ringComposer(int N);

int main()
{
    char buffer[64];
    int N;
    while (fgets(buffer,64,stdin) != NULL && buffer[0] != '\n')
    {
        sscanf(buffer,"%d",&N);
        ringComposer(N);
    }
    

}

void ringComposer(int N)
{
    int *partial_solution = malloc(sizeof(int)*N);
    bool *visited = calloc(1,sizeof(int)*N);
    if (!partial_solution || !visited)
        return;

    partial_solution[0] = 1;
    visited[0] = true;
    ring_composer_bt(N,partial_solution,1,visited);

    free(partial_solution);
    free(visited);
}

void ring_composer_bt(int N, int *partial_solution, int sol_size, bool *visited)
{
    if (sol_size == N)
    {
        printArray(partial_solution, sol_size);
    }

    int *candidates = malloc(sizeof(int)*N);
    int c_size;
    construct_candidates(N, partial_solution, sol_size, visited, candidates, &c_size);

    for (int i = 0; i < c_size; i++)
    {
        partial_solution[sol_size] = candidates[i];
        visited[candidates[i]-1] = true;
        ring_composer_bt(N, partial_solution, sol_size+1, visited);
        visited[candidates[i]-1] = false;
    }
    
    free(candidates);

}

void construct_candidates(int N, int *partial_solution, int sol_size, bool *visited, int *candidates, int *c_size)
{
    int count = 0;

    if (sol_size == N-1)
    {
        for (int i = 0; i < N; i++)
        {
            if (visited[i] == false && is_prime(partial_solution[sol_size-1] + (i+1)) && is_prime(1 + (i+1)))
            {
                candidates[count] = i+1;
                count++;
            }
        }
    }
    else
    {
        for (int i = 0; i < N; i++)
        {
            if (visited[i] == false && is_prime(partial_solution[sol_size-1] + (i+1)))
            {
                candidates[count] = i+1;
                count++;
            }
        }
    }
    
    *c_size = count;
}

bool is_prime(int n)
{
    return (n == 2)  || 
           (n == 3)  || 
           (n == 5)  || 
           (n == 7)  ||
           (n == 11) ||
           (n == 13) ||
           (n == 17) ||
           (n == 19) ||
           (n == 23) ||
           (n == 29) ||
           (n == 31);
}

void printArray(int *A, int len)
{
    
    for (int i = 0; i < len; i++)
    {
        printf("%d ",A[i]);
    }
    printf("\n");
    
}