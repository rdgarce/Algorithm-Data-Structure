#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Max_Dim_t
{
    int  n_rows;
    int  n_cols;
    int  area;
}Max_Dim_t;

int max_sub_matrix_size(bool *matrix, int m_rows, int m_cols);
void printMaxDimMatrix(Max_Dim_t (*A)[4], int A_rows, int A_cols);
void printMaxDim(Max_Dim_t *m);

#define LEGAL_POS(m_rows, m_cols, position) ((position) >= 0 && (position) < (m_rows)*(m_cols))
#define SAME_ROW(m_rows, m_cols, position1, position2) ((position1)/(m_cols) == (position2)/(m_cols))
#define MAX(one, two) ((one) > (two) ? (one) : (two))
#define MIN(one, two) ((one) < (two) ? (one) : (two))

/*
1,0,1,1,1,
0,0,0,1,1,
1,0,0,1,0,
1,0,1,1,1,
0,0,0,1,1,
0,0,0,0,1,
0,0,0,1,1
*/

int main(){
bool m[] = {
            1,0,1,1,1,
            0,0,0,1,1,
            1,0,0,1,0,
            1,0,1,1,1,
            0,0,0,1,1,
            0,0,0,0,1,
            0,0,0,1,1
            };
    
    int res = max_sub_matrix_size(m,7,5);
    printf("RES: %d\n",res);
}

int max_sub_matrix_size(bool *matrix, int m_rows, int m_cols)
{


}

void printMaxDim(Max_Dim_t *m)
{
    printf("(n_rows=%d, n_cols=%d, area=%d)",m->n_rows,m->n_cols,m->area);
}

void printMaxDimMatrix(Max_Dim_t (*A)[4], int A_rows, int A_cols)
{
    printf("-- Massime matrici riga --\n");
    for (int i = 0; i < A_rows*A_cols; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printMaxDim(&A[i][j]);
            printf(" ");
        }
        printf("\n");
    }
    
}