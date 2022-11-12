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
#define memo_index(start_pos, end_pos) (start_pos * end_pos)

void indegree(bool *matrix, int m_rows, int m_cols, int *array_of_position, int *array_size, int position);
void print_array(int *A, int len);
int *min_paths(bool *matrix, int m_rows, int m_cols);
int min_path(bool *matrix, int m_rows, int m_cols, int start_pos, int end_pos, int *memo);

int main(){

    bool m[4][7] = {{1,1,0,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,0,1,1}};

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 7; j++)
        {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    

    int a[3];
    int size;

    min_paths(m,4,7);

}

int *min_paths(bool *matrix, int m_rows, int m_cols){

    int *memo = malloc(sizeof(int)*m_rows*m_cols*m_rows*m_cols);
    if (!memo)
        exit(-1);
    
    memset(memo,-1,sizeof(int)*m_rows*m_cols*m_rows*m_cols);

    for (int i = 0; i < m_rows*m_cols; i = i + m_cols){

        for (int j = m_cols - 1; j < m_rows*m_cols; j = j + m_cols){

            min_path(matrix,m_rows,m_cols,i,j,memo);
            //printf("%d %d\n",i,j);

        }  

    }
    
}

int min_path(bool *matrix, int m_rows, int m_cols, int start_pos, int end_pos, int *memo){

    // Caso base, memorizzo e ritorno
    if (start_pos == end_pos){
        memo[memo_index(start_pos,end_pos)] = 0;
        return 0;
    }

    // Controllo se esiste già un risultato memorizzato
    if (memo[memo_index(start_pos,end_pos)] >= 0)
        return memo[memo_index(start_pos,end_pos)];
    
    int neighbors[3];
    int size;
    indegree(matrix,m_rows,m_cols,neighbors,&size,start_pos);

    int result = INT_MAX;
    int arg_min;
    int temp;
    for (int i = 0; i < size; i++){

        temp = 1 + min_path(matrix,m_rows,m_cols,neighbors[i],end_pos,memo);
        memo[memo_index(neighbors[i],end_pos)] = temp;
        if (temp < result)
        {
            result = temp;
            arg_min = neighbors[i];
        }
        
    }

    memo[memo_index(arg_min,end_pos)] = result;
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
        if (legal_pos(temp,m_rows,m_cols) && matrix[temp] == 0)
            condition = false;
        // Verifico se tale nodo ha un nodo in DESTRA che è 0
        temp = neighbor + 1;
        if (legal_pos(temp,m_rows,m_cols) && matrix[temp] == 0)
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
        if (legal_pos(temp,m_rows,m_cols) && matrix[temp] == 0)
            condition = false;
        // Verifico se tale nodo ha un nodo in DESTRA che è 0
        temp = neighbor + 1;
        if (legal_pos(temp,m_rows,m_cols) && matrix[temp] == 0)
            condition = false;
    }
    if (condition == true){
        array_of_position[count] = neighbor;
        count++;
        condition = false;
    }

    // Verifico se il nodo in DESTRA è collegato al nodo [position]
    neighbor = position + 1;
    if (legal_pos(neighbor,m_rows,m_cols) && matrix[neighbor] == 1){
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
        if (legal_pos(temp,m_rows,m_cols) && matrix[temp] == 0)
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