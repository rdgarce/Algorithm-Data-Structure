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
void printMaxDimMatrix(Max_Dim_t (*A)[3], int A_rows, int A_cols);
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
    /*
    * In posizione 0 il massimo vettore riga, 
    * poi quello colonna e poi quello più grande 
    * in assoluto (che non sia una delle due precedenti)
    */ 
    Max_Dim_t (*max_dims)[3] = calloc(m_rows*m_cols*3,sizeof(Max_Dim_t));
    if (!max_dims)
    {
        exit(-1);
    }

    Max_Dim_t new_max_dim_top, new_max_dim_left;
    int max_area = 0;
    int temp;
    
    for (int i = 0; i < m_rows*m_cols; i++)
    {
        // Se non trovo zero nella matrice vado avanti
        if (matrix[i] != 0)
            continue;

        // Caso base se c'è uno zero in prima posizione nella matrice
        if (i == 0)
        {
            for (int j = 0; j < 3; j++)
            {
            max_dims[i][j].n_cols = 1;
            max_dims[i][j].n_rows = 1;
            max_dims[i][j].area = 1;
            }
        }

        // Caso di zero in prima riga
        if (!LEGAL_POS(m_rows,m_cols,i-m_cols) && SAME_ROW(m_rows,m_cols,i,i-1) && i != 0)
        {
            // Matrice riga
            max_dims[i][0].n_cols = max_dims[i-1][0].n_cols + 1;
            max_dims[i][0].n_rows = 1;
            max_dims[i][0].area = max_dims[i-1][0].area + 1;

            // Matrice colonna
            max_dims[i][1].n_cols = 1;
            max_dims[i][1].n_rows = 1;
            max_dims[i][1].area = 1;

            // Matrice massima
            max_dims[i][2].n_cols = max_dims[i-1][0].n_cols + 1;
            max_dims[i][2].n_rows = 1;
            max_dims[i][2].area = max_dims[i-1][0].area + 1;
        }

        // Caso di zero in prima colonna
        if (!SAME_ROW(m_rows,m_cols,i,i-1) && LEGAL_POS(m_rows,m_cols,i-m_cols) && i != 0)
        {
            // Matrice riga
            max_dims[i][0].n_cols = 1;
            max_dims[i][0].n_rows = 1;
            max_dims[i][0].area = 1;

            // Matrice colonna
            max_dims[i][1].n_cols = 1;
            max_dims[i][1].n_rows = max_dims[i-m_cols][1].n_rows + 1;
            max_dims[i][1].area = max_dims[i-m_cols][1].area + 1;

            // Matrice massima
            max_dims[i][2].n_cols = 1;
            max_dims[i][2].n_rows = max_dims[i-m_cols][1].n_rows + 1;
            max_dims[i][2].area = max_dims[i-m_cols][1].area + 1;
        }

        // Caso di zero centrale
        if (SAME_ROW(m_rows,m_cols,i,i-1) && LEGAL_POS(m_rows,m_cols,i-m_cols))
        {
            // Matrice riga
            max_dims[i][0].n_cols = max_dims[i-1][0].n_cols + 1;
            max_dims[i][0].n_rows = 1;
            max_dims[i][0].area = max_dims[i-1][0].area + 1;

            // Matrice colonna
            max_dims[i][1].n_cols = 1;
            max_dims[i][1].n_rows = max_dims[i-m_cols][1].n_rows + 1;
            max_dims[i][1].area = max_dims[i-m_cols][1].area + 1;

            Max_Dim_t temp_top;
            int temp_top_area = 0;
            // Confronto del top con i 3 left per trovare il migliore
            for (int l = 0; l < 3; l++)
            {
                // Matrice massima da sopra
                temp_top.n_rows = max_dims[i-m_cols][l].n_rows + 1;
                temp_top.n_cols = MIN(max_dims[i-m_cols][l].n_cols,max_dims[i-1][l].n_cols + 1) == 0 ? 1 : MIN(max_dims[i-m_cols][l].n_cols,max_dims[i-1][l].n_cols + 1);
                temp_top.area = temp_top.n_rows * temp_top.n_cols;
                
                if (temp_top.area > temp_top_area)
                {
                    new_max_dim_top = temp_top;
                    temp_top_area = temp_top.area;
                }
            }

            Max_Dim_t temp_left;
            int temp_left_area = 0;
            // Confronto del top con i 3 left per trovare il migliore
            for (int l = 0; l < 3; l++)
            {
                // Matrice massima da sinistra
                temp_left.n_rows = MIN(max_dims[i-1][l].n_rows,max_dims[i-m_cols][l].n_rows + 1) == 0 ? 1 : MIN(max_dims[i-1][l].n_rows,max_dims[i-m_cols][l].n_rows + 1);
                temp_left.n_cols = max_dims[i-1][l].n_cols + 1;
                temp_left.area = temp_left.n_rows * temp_left.n_cols;
                
                if (temp_left.area > temp_left_area)
                {
                    new_max_dim_left = temp_left;
                    temp_left_area = temp_left.area;
                }
            }

            // Salvataggio dell'effettivo massimo
            if (new_max_dim_top.area >= new_max_dim_left.area)
            {
                max_dims[i][2].n_rows = new_max_dim_top.n_rows;
                max_dims[i][2].n_cols = new_max_dim_top.n_cols;
                max_dims[i][2].area = new_max_dim_top.area;
            }
            else
            {
                max_dims[i][2].n_rows = new_max_dim_left.n_rows;
                max_dims[i][2].n_cols = new_max_dim_left.n_cols;
                max_dims[i][2].area = new_max_dim_left.area;
            }
            
        }
        
        temp = MAX(max_dims[i][0].area,MAX(max_dims[i][1].area,max_dims[i][2].area));
        if (temp > max_area)
        {
            max_area = temp;
        }

    }
   
    printMaxDimMatrix(max_dims,m_rows,m_cols);
    return max_area;

}

void printMaxDim(Max_Dim_t *m)
{
    printf("(n_rows=%d, n_cols=%d, area=%d)",m->n_rows,m->n_cols,m->area);
}

void printMaxDimMatrix(Max_Dim_t (*A)[3], int A_rows, int A_cols)
{
    printf("-- Massime matrici riga --\n");
    for (int i = 0; i < A_rows*A_cols; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printMaxDim(&A[i][j]);
            printf(" ");
        }
        printf("\n");
    }
    
}