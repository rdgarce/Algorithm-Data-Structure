#include <stdlib.h>
#include <stdio.h>

#define MAX_STRING_SIZE 1000

int max_pal_sub_seq(char *string, size_t s_size);
int max(int one, int two);
void printMatrix(int *M, int rows, int cols);

int main()
{
    char buf[] = "ciaoaic";
    printf("%d\n",max_pal_sub_seq(buf,sizeof(buf)-1));
}

int max_pal_sub_seq(char *string, size_t s_size)
{
    int (*memo)[s_size] = calloc(1,sizeof(int)*s_size*s_size);

    // Scrittura in memo dei casi base sulla diagonale
    for (int i = 0; i < s_size; i++)
        memo[i][i] = 1;

    for (int j = 1; j < s_size; j++)
    {
        for (int i = j-1; i >= 0; i--)
        {
            if (string[i] != string[j])
            {
                memo[i][j] = max(memo[i+1][j],memo[i][j-1]);
            }
            else if (string[i] == string[j] && j-i >= 2)
            {
                memo[i][j] = 2 + memo[i+1][j-1];
            }
            else
            {
                memo[i][j] = 2;
            }
        }
    }
    free(memo);
    return memo[0][s_size-1];
}

int max(int one, int two)
{
    return one >= two ? one : two;
}

void printMatrix(int *M, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d ",M[i*cols + j]);
        }
        printf("\n");
    }
    
}