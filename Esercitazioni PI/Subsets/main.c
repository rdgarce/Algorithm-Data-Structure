#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void printSolution(bool *A, int len);
void allSubsets(int N);
void all_subsets_(int N, bool *partial_solution, int sol_size);

int main()
{
    allSubsets(3);
}

void allSubsets(int N)
{
    bool *partial_solution = calloc(1,sizeof(bool)*N);
    if (!partial_solution)
        exit(-1);
    
    all_subsets_(N,partial_solution,0);
}

void all_subsets_(int N, bool *partial_solution, int sol_size)
{
    if (sol_size == N)
    {
        printSolution(partial_solution,sol_size);
        return;
    }

    partial_solution[sol_size] = true;
    all_subsets_(N,partial_solution, sol_size+1);
    partial_solution[sol_size] = false;
    all_subsets_(N,partial_solution, sol_size+1);
    
}

void printSolution(bool *A, int len)
{
    printf("[ ");
    for (int i = 0; i < len; i++)
    {
        if (A[i] == true)
            printf("%d ",i+1);
    }
    printf("]\n");
}