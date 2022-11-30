#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void allPermutations(int N);
void all_permutations_(int N, int *partial_solution, int sol_size, bool *visited);
void construct_candidates(int N, bool *visited, int *array_of_candidates, int *candidates_size);
void printArray(int *A, int len);

int main()
{
    allPermutations(4);
}

void allPermutations(int N)
{
    int *partial_solution = malloc(sizeof(int) * N);
    bool *visited = calloc(1,sizeof(bool) * N);
    if (!partial_solution || !visited)
        exit(-1);
    
    all_permutations_(N,partial_solution,0,visited);

    free(partial_solution);
    free(visited);
}

void all_permutations_(int N, int *partial_solution, int sol_size, bool *visited)
{
    if (sol_size == N)
        printArray(partial_solution,sol_size);

    int *candidates = malloc(sizeof(int) * (N-sol_size));
    int c_size = 0;
    if (!candidates)
        exit(-1);
    
    construct_candidates(N,visited,candidates,&c_size);

    for (int i = 0; i < c_size; i++)
    {
        partial_solution[sol_size] = candidates[i];
        visited[candidates[i]-1] = true;
        all_permutations_(N,partial_solution,sol_size+1,visited);
        visited[candidates[i]-1] = false;
    }

    free(candidates);
}

void construct_candidates(int N, bool *visited, int *array_of_candidates, int *candidates_size)
{
    int count = 0;

    for (int i = 0; i < N; i++)
    {
        if (visited[i] == false)
        {
            array_of_candidates[count] = i+1;
            count++;
        }
    }

    *candidates_size = count;
}

void printArray(int *A, int len)
{
    printf("[ ");
    for (int i = 0; i < len; i++)
    {
        printf("%d ",A[i]);
    }
    printf("]\n");
}