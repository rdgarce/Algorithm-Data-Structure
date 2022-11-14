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

int max_submatrix(bool *matrix, int m_rows, int m_cols);
int __max_submatrix(bool *matrix, int m_rows, int m_cols, int position, int sub_m_h, int sub_m_w, int *visited);

int main(){

    bool m[5][5]={
                    {1,1,1,1,1},
                    {1,1,1,1,1},
                    {0,0,1,1,1},
                    {0,0,1,1,1},
                    {0,0,0,0,0}
                };

    int a = max_submatrix(m,5,5);
    printf("Size = %d\n",a);
    
    
}

int max_submatrix(bool *matrix, int m_rows, int m_cols){

    int *visited = malloc(sizeof(int)*m_rows*m_cols);
    if (!visited)
        exit(-1);
    memset(visited,0,m_rows*m_cols);
    
    int max_submatrix_size = 0;
    int temp;
    for (int i = 0; i < m_rows*m_cols; i++){

        if (matrix[i] == 0){
            temp = __max_submatrix(matrix,m_rows,m_cols,i,1,1,visited);
            if (temp > max_submatrix_size)
                max_submatrix_size = temp;
        }
        
    }

    return max_submatrix_size;
    
}

/*
* Controllo se la sottomatrice di [sub_m_h] righe e [sub_m_w] colonne
* con primo elemento in matrix[position] è tutta libera.
* Do per scontato il sottoproblema:
* - Con una colonna in meno se il numero di righe è minore di quello di colonne
* - Con una riga in meno se il numero è uguale
*/ 
int __max_submatrix(bool *matrix, int m_rows, int m_cols, int position, int sub_m_h, int sub_m_w, int *visited){

    printf("Entro in pos: %d\n",position);

    //Controllo se ho già un risultato per tale cella
    if (visited[position] > 0)
        return visited[position];
    
    //Serve il caso base con entrmabe dimensioni 1

    if (sub_m_h < sub_m_w){
        // Con una colonna in meno se il numero di righe è minore di quello di colonne
        int index = position + sub_m_w - 1;
        int factor = m_cols;
        int count = 0;
        int temp1;
        int temp2;
        for (int i = 0; i < sub_m_h; i++){
            if (matrix[index + i*factor] == 0)
                count++;
        }
        if (count == sub_m_h){

            // La matrice è effettivamente di questa dimensione
            temp1 = __max_submatrix(matrix,m_rows,m_cols,position,sub_m_h+1,sub_m_w,visited);
            temp2 = __max_submatrix(matrix,m_rows,m_cols,position,sub_m_h,sub_m_w+1,visited);
            if (temp1 == -1 && temp2 == -1)
            {
                // Qui salvo i visited e ritorno l'area di dimensione inferiore
                return sub_m_h*sub_m_w;
            }
            else{
                return temp1 > temp2 ? temp1 : temp2;
            }
            
        }
        else{

            //Non lo è
            return -1;
        }
    }
    else{
        // Con una riga in meno se il numero è uguale
        int index = position + (sub_m_h-1)*m_cols;
        int factor = 1;
        int count = 0;
        int temp1;
        int temp2;
        for (int i = 0; i < sub_m_w; i++){
            if (matrix[index + i*factor] == 0)
                count++;
        }
        if (count == sub_m_w)
        {
            // La matrice è effettivamente di questa dimensione
            temp1 = __max_submatrix(matrix,m_rows,m_cols,position,sub_m_h+1,sub_m_w,visited);
            temp2 = __max_submatrix(matrix,m_rows,m_cols,position,sub_m_h,sub_m_w+1,visited);
            if (temp1 == -1 && temp2 == -1)
            {
                // Qui salvo i visited e ritorno l'area di dimensione inferiore
                return sub_m_h*sub_m_w;
            }
            else{
                return temp1 > temp2 ? temp1 : temp2;
            }
        }
        else{

            //Non lo è
            return -1;
        }
        
        
    }
    
    

}