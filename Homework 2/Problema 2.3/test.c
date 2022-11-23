#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum Dim_t{
    BASE,
    ROW,
    COLUMN
}Dim_t;

int max_submatrix(bool *matrix, int m_rows, int m_cols);
int max_submatrix_v2_(bool *matrix, int m_rows, int m_cols, int position, int sub_m_h, int sub_m_w, Dim_t dim, int *visited);

int max_sub_matrix_size(bool *matrix, int m_rows, int m_cols);

#define LEGAL_POS(m_rows, m_cols, position) ((position) >= 0 && (position) < (m_rows)*(m_cols))
#define SAME_ROW(m_rows, m_cols, position1, position2) ((position1)/(m_cols) == (position2)/(m_cols))
#define MAX(one, two) ((one) > (two) ? (one) : (two))
#define MIN(one, two) ((one) < (two) ? (one) : (two))

#define MAX_TESTS 10000
#define MAX_ROWS 5
#define MAX_COLS 5
#define ONES_QNT 1/2
int main(){

    int n_tests = MAX_TESTS;
    int m_rows, m_cols;
    bool *matrix;
    int rand_pos;
    int res1, res2;
    for (int i = 0; i < n_tests; i++)
    {
        m_rows = rand() % MAX_ROWS + 1;
        m_cols = rand() % MAX_COLS + 1;

        matrix = calloc(m_rows*m_cols,sizeof(bool));
        if (!matrix)
        {
            printf("Errore di inizializzazione\n");
            exit(-1);
        }

        for (int i = 0; i < m_rows*m_cols*ONES_QNT; i++)
        {
            rand_pos = rand() % (m_rows*m_cols);
            if (matrix[rand_pos] != 1)
            {
                matrix[rand_pos] = 1;
            }
            else
            {
                while (matrix[rand_pos] == 1)
                {
                    rand_pos = rand() % (m_rows*m_cols);
                }
                matrix[rand_pos] = 1;
            }
            
        }

        res1 = max_submatrix(matrix,m_rows,m_cols);
        res2 = max_sub_matrix_size(matrix,m_rows,m_cols);

        if (res1 != res2)
        {
            printf("Errore trovato!\n>Res1 = %d e Res2 = %d\n",res1,res2);
            for (int i = 0; i < m_rows; i++)
            {
                for (int j = 0; j < m_cols; j++)
                {
                    printf("%d ",matrix[i*m_cols + j]);
                }
                printf("\n");
                
            }
            printf("\n");

        }
        free(matrix);

    }
    printf("Test terminati\n");
    
}

int max_submatrix(bool *matrix, int m_rows, int m_cols){

    int *visited = malloc(sizeof(int)*m_rows*m_cols);
    if (!visited)
        exit(-1);
    memset(visited,0,sizeof(int)*m_rows*m_cols);
    
    int max_submatrix_size = 0;
    int temp;
    for (int i = 0; i < m_rows*m_cols; i++){

        if (matrix[i] == 0){
            temp = max_submatrix_v2_(matrix,m_rows,m_cols,i,1,1,BASE,visited);
            if (temp > max_submatrix_size)
                max_submatrix_size = temp;
        }
        
    }

    /*
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            printf("%d ",visited[i*m_cols + j]);
        }
        
        printf("\n");
    }
    */
    
    
    free(visited);
    return max_submatrix_size;
    
}

int max_submatrix_v2_(bool *matrix, int m_rows, int m_cols, int position, int sub_m_h, int sub_m_w, Dim_t dim, int *visited){

    int result_1 = -1;
    int result_2 = -1;
    //printf("Sto entrando in pos %d con dim (%d,%d)\n",position,sub_m_h,sub_m_w);

    /*
    if (visited[position] > 0)
    {
        //printf("Ritorno un valore memo: %d\n",visited[position]);
        return visited[position];
    }
    */
    
    
    // Controllo della validità delle dimensioni della sottomatrice
    if ((position + (sub_m_w-1))/m_cols > position/m_cols || position + (sub_m_h-1)*m_cols >= m_rows*m_cols)
    {
        //printf("Sto ritornando -1\n");
        return -1;
    }

    /*
    if (sub_m_h == 1 && sub_m_w == 1)
    {
        result_1 = max_submatrix_v2_(matrix,m_rows,m_cols,position,sub_m_h,sub_m_w+1,COLUMN,visited);
        result_2 = max_submatrix_v2_(matrix,m_rows,m_cols,position,sub_m_h+1,sub_m_w,ROW,visited);
        if (result_1 == -1 && result_2 == -1)
        {
            return -1;
        }
        else
            return result_1 > result_2 ? result_1 : result_2;
    }
    */
    
    
    if (dim == COLUMN)
    {
        int index = position + sub_m_w - 1;
        int factor = m_cols;
        int count = 0;
        for (int i = 0; i < sub_m_h; i++)
        {
            if (matrix[index + i*factor] == 0)
                count++;
        }

        if (count != sub_m_h)
        {
            return -1;
        }
        
        // La matrice è effettivamente di questa dimensione, vado avanti nella ricorsione
        result_1 = max_submatrix_v2_(matrix,m_rows,m_cols,position,sub_m_h,sub_m_w+1,COLUMN,visited);
        result_2 = max_submatrix_v2_(matrix,m_rows,m_cols,position,sub_m_h+1,sub_m_w,ROW,visited);
        
        if (result_1 != -1 || result_2 != -1)
        {
            return result_1 > result_2 ? result_1 : result_2;
        }
            
        // Qui salvo i visited e ritorno l'area di dimensione inferiore
        //printf("Sto salvando area pari a %d in pos %d con dim (%d,%d)\n",sub_m_h*sub_m_w,position,sub_m_h,sub_m_w);
        for (int i = 0; i < sub_m_h; i++)
        {
            for (int j = position + i*m_cols; j < position + i*m_cols + sub_m_w; j++)
            {
                visited[j]= sub_m_h*sub_m_w;
            }
            
        }
        return sub_m_h*sub_m_w;
    }
    else{
        
        // Con una riga in meno se il numero è uguale
        int index = position + (sub_m_h-1)*m_cols;
        int factor = 1;
        int count = 0;
        for (int i = 0; i < sub_m_w; i++){
            if (matrix[index + i*factor] == 0)
                count++;
        }
        if (count != sub_m_w)
        {
            return -1;
        }

        // La matrice è effettivamente di questa dimensione
        result_1 = max_submatrix_v2_(matrix,m_rows,m_cols,position,sub_m_h,sub_m_w+1,COLUMN,visited);
        result_2 = max_submatrix_v2_(matrix,m_rows,m_cols,position,sub_m_h+1,sub_m_w,ROW,visited);
        if (result_1 != -1 || result_2 != -1)
        {
            return result_1 > result_2 ? result_1 : result_2;
        }
        
        // Qui salvo i visited e ritorno l'area di dimensione inferiore
        //printf("Sto salvando area pari a %d in pos %d con dim (%d,%d)\n",sub_m_h*sub_m_w,position,sub_m_h,sub_m_w);

    
        for (int i = 0; i < sub_m_h; i++)
        {
            for (int j = position + i*m_cols; j < position + i*m_cols + sub_m_w; j++)
            {
                visited[j]= sub_m_h*sub_m_w;
            }
            
        }    
        return sub_m_h*sub_m_w;
    }
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
    int temp = 0;
    int sub_area = 0;

    for (int i = 0; i < m_rows*m_cols; i++)
    {
        if (matrix[i] != 0)
            continue;
        
        // Setting della matrice TOP
        if (LEGAL_POS(m_rows,m_cols,i-m_cols))
        {
            TOP[i] = TOP[i-m_cols] + 1;
        }
        else
        {
            TOP[i] = 1;
        }

        // Setting della matrice LEFT
        if (LEGAL_POS(m_rows,m_cols,i-1) && SAME_ROW(m_rows,m_cols,i,i-1))
        {
            LEFT[i] = LEFT[i-1] + 1;
        }
        else
        {
            LEFT[i] = 1;
        }

        // Trovo l'area massima
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