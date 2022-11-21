#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int max_sub_matrix_size(bool *matrix, int m_rows, int m_cols);
int max_sub_from_index(bool *matrix, int m_rows, int m_cols, int pos, int *TOP, int *LEFT);

#define LEGAL_POS(m_rows, m_cols, position) ((position) >= 0 && (position) < (m_rows)*(m_cols))
#define SAME_ROW(m_rows, m_cols, position1, position2) ((position1)/(m_cols) == (position2)/(m_cols))
#define MAX(one, two) ((one) > (two) ? (one) : (two))
#define MIN(one, two) ((one) < (two) ? (one) : (two))

int main()
{

    bool m[5][6]={
                    {0,0,1,1,1,0},
                    {0,1,0,0,0,0},
                    {1,1,0,0,0,0},
                    {0,0,0,1,1,0},
                    {0,0,0,1,1,0},
                };
    
    int res = max_sub_matrix_size(m,5,6);
    int res_v2 = max_sub_matrix_size_v2(m,5,6);
    printf("RES: %d, RES V2: %d\n",res,res_v2);
}

int max_sub_matrix_size(bool *matrix, int m_rows, int m_cols)
{
    
    int *TOP = malloc(sizeof(int)*m_rows*m_cols);
    int *LEFT = malloc(sizeof(int)*m_rows*m_cols);
    if (!TOP || !LEFT)
    {
        return -1;
    }
    
    memset(TOP,0,sizeof(int)*m_rows*m_cols);
    memset(LEFT,0,sizeof(int)*m_rows*m_cols);

    int max_area = 0;
    int temp;
    for (int i = 0; i < m_rows*m_cols; i++)
    {
        if (matrix[i] != 0)
            continue;
        
        // Setting della matrice TOP
        LEGAL_POS(m_rows,m_cols,i-m_cols) ? (TOP[i] = TOP[i-m_cols] + 1) : (TOP[i] = 1);

        // Settig della matrice LEFT
        SAME_ROW(m_rows,m_cols,i,i-1) ? (LEFT[i] = LEFT[i-1] + 1) : (LEFT[i] = 1);

        // Trovo l'area massima
        int sub_area;
        if (LEGAL_POS(m_rows,m_cols,i-m_cols-1))
        {
            sub_area = MIN(TOP[i],TOP[i-m_cols-1]+1) * MIN(LEFT[i],LEFT[i-m_cols-1]+1);
        }
        else
        {
            sub_area = TOP[i] * LEFT[i];
        }

        temp = MAX(sub_area,MAX(TOP[i],LEFT[i]));
        
        if (temp > max_area)
        {
            max_area = temp;
        }
        
    }

    free(TOP);
    free(LEFT);
    return max_area;

}

// Non funziona per sovrascrittura della memoria
int max_sub_matrix_size_v2(bool *matrix, int m_rows, int m_cols)
{
    
    int *TOP = malloc(sizeof(int)*m_cols);
    int *LEFT = malloc(sizeof(int)*m_cols);
    if (!TOP || !LEFT)
    {
        return -1;
    }
    
    memset(TOP,0,sizeof(int)*m_cols);
    memset(LEFT,0,sizeof(int)*m_cols);

    int max_area = 0;
    int temp;
    for (int i = 0; i < m_rows*m_cols; i++)
    {
        if (matrix[i] != 0)
            continue;
        
        // Setting della matrice TOP
        LEGAL_POS(m_rows,m_cols,i-m_cols) ? (TOP[i%m_cols] = TOP[i%m_cols] + 1) : (TOP[i%m_cols] = 1);

        // Settig della matrice LEFT
        SAME_ROW(m_rows,m_cols,i,i-1) ? (LEFT[i%m_cols] = LEFT[(i-1)%m_cols] + 1) : (LEFT[i%m_cols] = 1);

        // Trovo l'area massima
        int sub_area;
        if (LEGAL_POS(m_rows,m_cols,i-m_cols-1))
        {
            sub_area = MIN(TOP[i%m_cols],TOP[(i-1)%m_cols]+1) * MIN(LEFT[i%m_cols],LEFT[(i-1)%m_cols]+1);
        }
        else
        {
            sub_area = TOP[i%m_cols] * LEFT[i%m_cols];
        }

        temp = MAX(sub_area,MAX(TOP[i%m_cols],LEFT[i%m_cols]));
        
        if (temp > max_area)
        {
            max_area = temp;
        }
        
    }

    free(TOP);
    free(LEFT);
    return max_area;

}