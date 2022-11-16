/*
Si  consideri  una  matrice  di  0  ed  1,  in  cui  “1”  indica  “posizione  occupata”  e  “0”  indica 
“posizione libera”. Si scriva un algoritmo per determinare la sottomatrice massima libera 
(ossia che contiene tutti 0). L’algoritmo deve riportare il numero di 0 di tale sottomatrice. 
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
1 1 1 1
1 0 0 0
1 0 0 0
1 1 1 1

*/
typedef enum Dim_t{
    BASE,
    ROW,
    COLUMN
}Dim_t;

int max_submatrix(bool *matrix, int m_rows, int m_cols);
int max_submatrix_v2_(bool *matrix, int m_rows, int m_cols, int position, int sub_m_h, int sub_m_w, Dim_t dim, int *visited);



int main(){
    
    bool m[5][6]={
                    {0,1,1,1,1,0},
                    {0,1,1,1,1,0},
                    {0,0,0,0,0,0},
                    {0,1,1,1,1,0},
                    {0,1,1,1,1,0},
                };

    int a = max_submatrix(m,5,6);
    printf("Size = %d\n",a);
    
    
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
