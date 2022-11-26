#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Max_Dim_t
{
    int  n_rows;
    int  n_cols;
    int  area;
    bool reverse;
}Max_Dim_t;

int max_sub_matrix_size(bool *matrix, int m_rows, int m_cols);
void printMaxDimMatrix(Max_Dim_t *A, int A_rows, int A_cols);
void printMaxDim(Max_Dim_t *m);

#define LEGAL_POS(m_rows, m_cols, position) ((position) >= 0 && (position) < (m_rows)*(m_cols))
#define SAME_ROW(m_rows, m_cols, position1, position2) ((position1)/(m_cols) == (position2)/(m_cols))
#define MAX(one, two) ((one) > (two) ? (one) : (two))
#define MIN(one, two) ((one) < (two) ? (one) : (two))

/*
1 0 0 1 
1 0 1 0
0 0 0 0
1 1 1 1
*/

int main()
{

    bool m[4][4]={
                    {1, 0, 0, 1},
                    {1, 0, 1, 0},
                    {0, 0, 0, 0},
                    {1, 1, 1, 1}
                };
    
    int res = max_sub_matrix_size(m,4,4);
    //printf("RES: %d\n",res);
}

int max_sub_matrix_size(bool *matrix, int m_rows, int m_cols)
{
    
    Max_Dim_t *(max_dims[3]) = calloc(m_rows*m_cols*3,sizeof(Max_Dim_t));
    if (!max_dims)
    {
        exit(-1);
    }

    int max_area = 0;

    Max_Dim_t top_dim, top_dim_reverse;
    Max_Dim_t left_dim, left_dim_reverse;
    Max_Dim_t new_max_dim_top, new_max_dim_left;
    Max_Dim_t *top_dim_reverse_ptr = NULL;
    Max_Dim_t *left_dim_reverse_ptr = NULL;

    for (int i = 0; i < m_rows*m_cols; i++)
    {
        // Se non trovo zero nella matrice vado avanti
        if (matrix[i] != 0)
            continue;

        // Caso base se c'è uno zero in prima posizione nella matrice
        if (i == 0)
        {
            max_dims[i].n_cols = 1;
            max_dims[i].n_rows = 1;
            max_dims[i].area = 1;
            max_dims[i].reverse = false;
        }

        // Caso di zero in prima riga
        if (!LEGAL_POS(m_rows,m_cols,i-m_cols) && SAME_ROW(m_rows,m_cols,i,i-1) && i != 0)
        {
            max_dims[i].n_cols = max_dims[i-1].n_cols + 1;
            max_dims[i].n_rows = 1;
            max_dims[i].area = max_dims[i-1].area + 1;
            max_dims[i].reverse = false;
        }

        // Caso di zero in prima colonna
        if (!SAME_ROW(m_rows,m_cols,i,i-1) && LEGAL_POS(m_rows,m_cols,i-m_cols) && i != 0)
        {
            max_dims[i].n_cols = 1;
            max_dims[i].n_rows = max_dims[i-m_cols].n_rows + 1;
            max_dims[i].area = max_dims[i-m_cols].area + 1;
            max_dims[i].reverse = false;
        }

        if (SAME_ROW(m_rows,m_cols,i,i-1) && LEGAL_POS(m_rows,m_cols,i-m_cols))
        {
            Max_Dim_t top_dim = max_dims[i-m_cols];
            Max_Dim_t left_dim = max_dims[i-1];
            
            // Calcolo condizionale dei reverse
            if (top_dim.reverse)
            {
                top_dim_reverse.n_cols = top_dim.n_rows;
                top_dim_reverse.n_rows = top_dim.n_cols;
                top_dim_reverse.area = top_dim.area;
                top_dim_reverse.reverse = top_dim.reverse;
                top_dim_reverse_ptr = &top_dim_reverse;
            }

            // Calcolo condizionale dei reverse
            if (left_dim.reverse)
            {
                left_dim_reverse.n_cols = left_dim.n_rows;
                left_dim_reverse.n_rows = left_dim.n_cols;
                left_dim_reverse.area = left_dim.area;
                left_dim_reverse.reverse = left_dim.reverse;
                left_dim_reverse_ptr = &left_dim_reverse;
            }
            
            // Calcolo del nuovo massimo considerando top e left
            new_max_dim_top.n_rows = top_dim.n_rows + 1;
            new_max_dim_top.n_cols = MIN(top_dim.n_cols,left_dim.n_cols + 1) == 0 ? 1 : MIN(top_dim.n_cols,left_dim.n_cols + 1);
            new_max_dim_top.area = new_max_dim_top.n_rows * new_max_dim_top.n_cols;
            new_max_dim_top.reverse = false;

            // Se esiste top_reverse e costruisce un'area maggiore, calcolo del nuovo massimo considerando top_reverse e left
            if (top_dim_reverse_ptr && ((top_dim_reverse.n_rows + 1) * MIN(top_dim_reverse.n_cols,left_dim.n_cols + 1)) > new_max_dim_top.area)
            {
                new_max_dim_top.n_rows = top_dim_reverse.n_rows + 1;
                new_max_dim_top.n_cols = MIN(top_dim_reverse.n_cols,left_dim.n_cols + 1);
                new_max_dim_top.area = new_max_dim_top.n_rows * new_max_dim_top.n_cols;
                new_max_dim_top.reverse = false;
            }

            // Calcolo del nuovo massimo considerando left e top
            new_max_dim_left.n_rows = MIN(left_dim.n_rows,top_dim.n_rows + 1) == 0 ? 1 : MIN(left_dim.n_rows,top_dim.n_rows + 1);
            new_max_dim_left.n_cols = left_dim.n_cols + 1;
            new_max_dim_left.area = new_max_dim_left.n_rows * new_max_dim_left.n_cols;
            new_max_dim_left.reverse = false;

            // Se esiste left_reverse e costruisce un'area maggiore, calcolo del nuovo massimo considerando left_reverse e top
            if (left_dim_reverse_ptr && ((left_dim_reverse.n_cols + 1) * MIN(left_dim_reverse.n_rows,top_dim.n_rows + 1)) > new_max_dim_left.area)
            {
                new_max_dim_left.n_rows = MIN(left_dim_reverse.n_rows,top_dim.n_rows + 1);
                new_max_dim_left.n_cols = left_dim_reverse.n_cols + 1;
                new_max_dim_left.area = new_max_dim_left.n_rows * new_max_dim_left.n_cols;
                new_max_dim_left.reverse = false;
            }

            // Calcolo e confronto tra top_reverse e left_reverse e viceversa
            if (top_dim_reverse_ptr && left_dim_reverse_ptr)
            {
                if (((top_dim_reverse.n_rows + 1) * MIN(top_dim_reverse.n_cols,left_dim_reverse.n_cols + 1)) > new_max_dim_top.area)
                {
                    new_max_dim_top.n_rows = top_dim_reverse.n_rows + 1;
                    new_max_dim_top.n_cols = MIN(top_dim_reverse.n_cols,left_dim_reverse.n_cols + 1);
                    new_max_dim_top.area = new_max_dim_top.n_rows * new_max_dim_top.n_cols;
                    new_max_dim_top.reverse = false;
                }

                if (((left_dim_reverse.n_cols + 1) * MIN(left_dim_reverse.n_rows,top_dim.n_rows + 1)) > new_max_dim_left.area)
                {
                    new_max_dim_left.n_rows = MIN(left_dim_reverse.n_rows,top_dim_reverse.n_rows + 1);
                    new_max_dim_left.n_cols = left_dim_reverse.n_cols + 1;
                    new_max_dim_left.area = new_max_dim_left.n_rows * new_max_dim_left.n_cols;
                    new_max_dim_left.reverse = false;
                } 
            }

            // Trovo l'area massima
            if (new_max_dim_top.area > new_max_dim_left.area)
            {
                max_dims[i] = new_max_dim_top;
            }
            else if(new_max_dim_top.area < new_max_dim_left.area)
            {
                max_dims[i] = new_max_dim_left;
            }
            else{
                max_dims[i] = new_max_dim_top;
                if (new_max_dim_top.n_cols == 1 || new_max_dim_top.n_rows == 1)
                {
                    max_dims[i].reverse = true;
                }
                
            }

        }
        
        if (max_dims[i].area > max_area)
        {
            max_area = max_dims[i].area;
        }

        // Reset a NULL dei puntatori per la prossima iterazione
        top_dim_reverse_ptr = NULL;
        left_dim_reverse_ptr = NULL;
    }

    printMaxDimMatrix(max_dims,m_rows,m_cols);

    return max_area;

}

void printMaxDim(Max_Dim_t *m)
{
    printf("(n_rows=%d, n_cols=%d, area=%d, reverse=%d)",m->n_rows,m->n_cols,m->area,m->reverse);
}

void printMaxDimMatrix(Max_Dim_t *A, int A_rows, int A_cols)
{
    for (int i = 0; i < A_rows; i++)
    {
        for (int j = 0; j < A_cols; j++)
        {
            printMaxDim(&A[i*A_cols + j]);
            printf(" ");
        }
        printf("\n");
    }
}