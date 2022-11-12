/*
Si consideri il seguente problema di minimo percorso vincolato. Sia data una matrice 
rettangolare di 1 e 0, in cui 1 indica una cella che è possibile percorrere e 0 una cella che 
non è possibile percorrere. Inoltre, si assuma che non è possibile percorrere neanche le 
quattro celle adiacenti (sinistra, destra, sopra e sotto) ad una cella che contiene uno 0. 
Calcolare la lunghezza del più breve percorso possibile da qualsiasi cella nella prima 
colonna a qualsiasi cella nell'ultima colonna della matrice. L’obiettivo è evitare le celle 
contrassegnate con 0 e le loro quattro celle adiacenti (sinistra, destra, sopra e sotto). 
Le mosse possibili da una determinata cella sono lo spostamento di una cella adiacente a 
sinistra, destra, sopra o sotto (non sono consentiti spostamenti in diagonale). 


MATRICE DI INPUT nxm:
1 - 0 - 1 1 1
1 1 - 1 1 1 1
1 1 1 1 - 1 1
1 1 1 - 0 - 1

MATRICE DI INPUT 2:
1 - 0 - 1
1 1 - 1 1
1 1 1 1 1

MATRICE DI INPUT 3:
1 1 1
1 1 1
1 1 1

MATRICE DI MEMOIZATION nxn:
Salvo il costo del minimo percorso da ogni cella verso ogni cella della matrice:
         0     1     2    ...  nxm-1
      |-----------------------------|
0     |  0  | ... |     |     | ... |
1     | ... |  0  |     |     |     |
2     |     |     |  0  |     |     |
...   |     | ... |     |  0  |     |
nxm-1 |     |     |     | ... |  0  |
      |-----------------------------|

Formula della ricorsione
D(s,v) = min_u{1 + D(u,v) | per ogni u collegato ad s che non sia a sinistra di s}

Caso base:
D(s,s) = 0
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

#define legal_pos(index,rows,cols) (index >= 0 && index < rows*cols)
#define memo_index(start_pos, end_pos, rows, cols) (start_pos*cols*rows + end_pos)

void indegree(bool *matrix, int m_rows, int m_cols, int *array_of_position, int *array_size, int position);
void print_array(int *A, int len);
int min_paths(bool *matrix, int m_rows, int m_cols);
int min_path(bool *matrix, int m_rows, int m_cols, int start_pos, int prev_pos, int end_pos, int *memo);

int main(){

    bool m[4][7] = {{1,1,0,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,0,1,1}};
    int best_value_path = min_paths(m,4,7);

    printf("Il percorso minimo ha lunghezza: %d\n",best_value_path);
}

int min_paths(bool *matrix, int m_rows, int m_cols){

    int *memo = malloc(sizeof(int)*m_rows*m_cols*m_rows*m_cols);
    if (!memo)
        exit(-1);
    
    memset(memo,-1,sizeof(int)*m_rows*m_cols*m_rows*m_cols);

    int best_path_value = INT_MAX;
    int temp;
    for (int i = 0; i < m_rows*m_cols; i = i + m_cols){

        for (int j = m_cols - 1; j < m_rows*m_cols; j = j + m_cols){
            
            temp = min_path(matrix,m_rows,m_cols,i,i,j,memo);
            if (temp < best_path_value)
                best_path_value = temp;

        }  

    }
    
    /*
    for (int i = 0; i < m_rows*m_cols; i++)
    {
        for (int j = 0; j < m_rows*m_cols; j++)
        {
            printf("%d ",memo[i*m_cols*m_rows + j]);
        }

        printf("\n");
        
    }
    */

    free(memo);
    return best_path_value != INT_MAX ? best_path_value : -1;
    
}

int min_path(bool *matrix, int m_rows, int m_cols, int start_pos, int prev_pos, int end_pos, int *memo){

    //printf("Parto da: %d\n",  start_pos);

    // Caso base, memorizzo e ritorno
    if (start_pos == end_pos){
        //printf("Sto scrivendo 0 nella pos %d, come costo del percorso (%d,%d)\n",memo_index(start_pos,end_pos,m_rows, m_cols),start_pos,end_pos);
        memo[memo_index(start_pos,end_pos,m_rows, m_cols)] = 0;
        return 0;
    }

    // Controllo se esiste già un risultato memorizzato
    if (memo[memo_index(start_pos,end_pos,m_rows, m_cols)] >= 0)
        return memo[memo_index(start_pos,end_pos,m_rows, m_cols)];
    
    int *neighbors = malloc(sizeof(int)*3);
    if (!neighbors)
        exit(-1);
    
    int size;

    //printf("Sto per calcolare indegree\n");

    indegree(matrix,m_rows,m_cols,neighbors,&size,start_pos);

    /*
    printf("Vicini con size = %d: ",size);
    print_array(neighbors,size);
    printf("\n");
    */
    

    int result = INT_MAX;
    int temp;
    for (int i = 0; i < size; i++){

        if (neighbors[i] != prev_pos){

            temp = min_path(matrix, m_rows, m_cols, neighbors[i], start_pos, end_pos, memo);
            
            if (temp != INT_MAX)
                memo[memo_index(neighbors[i],end_pos,m_rows, m_cols)] = temp;
            
            if (temp < result)
                result = temp + 1;

        }
        
    }
    
    if (result != INT_MAX){
        memo[memo_index(start_pos,end_pos,m_rows, m_cols)] = result;
        //printf("Sto salvando %d per il percorso (%d,%d) in pos %d\n",result,start_pos,end_pos,memo_index(start_pos,end_pos,m_rows, m_cols));
    }

    free(neighbors);
    
    return result;
    
}

void indegree(bool *matrix, int m_rows, int m_cols, int *array_of_position, int *array_size, int position){

    int count = 0;
    int neighbor;
    int temp;
    bool condition = false;

    // Verifico se il nodo in ALTO è collegato al nodo [position]
    neighbor = position - m_cols;
    if (legal_pos(neighbor,m_rows,m_cols) && matrix[neighbor] == 1){
        condition = true;

        // Verifico se tale nodo ha un nodo in ALTO che è 0
        temp = neighbor - m_cols;
        if (legal_pos(temp,m_rows,m_cols) && matrix[temp] == 0)
            condition = false;
        // Verifico se tale nodo ha un nodo in SINISTRA che è 0
        temp = neighbor - 1;
        if ((neighbor % m_cols != 0) && legal_pos(temp,m_rows,m_cols) && matrix[temp] == 0)
            condition = false;
        // Verifico se tale nodo ha un nodo in DESTRA che è 0
        temp = neighbor + 1;
        if ((temp % m_cols != 0) && legal_pos(temp,m_rows,m_cols) && matrix[temp] == 0)
            condition = false;
    }
    if (condition == true){
        array_of_position[count] = neighbor;
        count++;
        condition = false;
    }

    // Verifico se il nodo in DESTRA è collegato al nodo [position]
    neighbor = position + 1;
    if ((neighbor % m_cols != 0) && legal_pos(neighbor,m_rows,m_cols) && matrix[neighbor] == 1){
        condition = true;

        // Verifico se tale nodo ha un nodo in ALTO che è 0
        temp = neighbor - m_cols;
        if (legal_pos(temp,m_rows,m_cols) && matrix[temp] == 0)
            condition = false;
        // Verifico se tale nodo ha un nodo in BASSO che è 0
        temp = neighbor + m_cols;
        if (legal_pos(temp,m_rows,m_cols) && matrix[temp] == 0)
            condition = false;
        // Verifico se tale nodo ha un nodo in DESTRA che è 0
        temp = neighbor + 1;
        if ((temp % m_cols != 0) && legal_pos(temp,m_rows,m_cols) && matrix[temp] == 0)
            condition = false;
    }
    if (condition == true){
        array_of_position[count] = neighbor;
        count++;
        condition = false;
    }

    // Verifico se il nodo in BASSO è collegato al nodo [position]
    neighbor = position + m_cols;
    if (legal_pos(neighbor,m_rows,m_cols) && matrix[neighbor] == 1){
        condition = true;

        // Verifico se tale nodo ha un nodo in BASSO che è 0
        temp = neighbor + m_cols;
        if (legal_pos(temp,m_rows,m_cols) && matrix[temp] == 0)
            condition = false;
        // Verifico se tale nodo ha un nodo in SINISTRA che è 0
        temp = neighbor - 1;
        if ((neighbor % m_cols != 0) && legal_pos(temp,m_rows,m_cols) && matrix[temp] == 0)
            condition = false;
        // Verifico se tale nodo ha un nodo in DESTRA che è 0
        temp = neighbor + 1;
        if ((temp % m_cols != 0) && legal_pos(temp,m_rows,m_cols) && matrix[temp] == 0)
            condition = false;
    }
    if (condition == true){
        array_of_position[count] = neighbor;
        count++;
        condition = false;
    }

    *array_size = count;
    
}

void print_array(int *A, int len){
    printf("[");
    for(int i=0;i<len;i++)
        printf("%d ", A[i]);
    printf("]");
}