#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum Dim_t{
    BASE,
    ROW,
    COLUMN
}Dim_t;

typedef struct Max_Dim_t
{
    int  n_rows;
    int  n_cols;
    int  area;
    bool reverse;
}Max_Dim_t;

int max_submatrix(bool *matrix, int m_rows, int m_cols);
int max_submatrix_v2_(bool *matrix, int m_rows, int m_cols, int position, int sub_m_h, int sub_m_w, Dim_t dim, int *visited);

int max_sub_matrix_size(bool *matrix, int m_rows, int m_cols);


#define LEGAL_POS(m_rows, m_cols, position) ((position) >= 0 && (position) < (m_rows)*(m_cols))
#define SAME_ROW(m_rows, m_cols, position1, position2) ((position1)/(m_cols) == (position2)/(m_cols))
#define MAX(one, two) ((one) > (two) ? (one) : (two))
#define MIN(one, two) ((one) < (two) ? (one) : (two))

#define MAX_TESTS 10000000
#define MAX_ROWS 7
#define MAX_COLS 7
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
   
    //printMaxDimMatrix(max_dims,m_rows,m_cols);
    return max_area;

}
