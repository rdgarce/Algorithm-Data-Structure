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

Soluzione:
Il problema viene risolto mediante la programmazione dinamica, sotto alcune ipotesi che permettono
di visualizzarlo logicamente come quello di trovare il minimo percorso tra due nodi in un grafo aciclico.
IPOTESI:
1) Ogni cella della matrice che contiene '1', e soltanto '1', diventa un nodo in un grafo, a meno che essa non sia adiacente ad una cella contenente uno '0',
2) Ogni nodo è connesso a tutti i nodi che corrispondono a celle adiacenti nella matrice di partenza,
3) Viene mantenuta una matrice di booleani "visited" delle stesse dimensioni della matrice di partenza, dove, di volta in volta,
    visited[i] = 'true' quando viene visitato il nodo i-esimo del grafo (corrispondente alla cella i-esima della matrice di partenza).

Le prime due ipotesi permettono di costruire un grafo (logico) corrispondente alla matrice,
mentre grazie alla terza ipotesi vengono evitati in ogni circostanza percorsi che portano a nodi già visitati nella stessa istanza del problema,
rendendo, di fatto, il grafo aciclico.
Quest'ultima ipotesi non restringe il campo delle soluzioni del problema di partenza perché una soluzione contenente un ciclo è sicuramente minorata
dalla stessa soluzione al netto del ciclo.

Formula della ricorsione:
D(s,v) = min_u{1 + D(u,v) | per ogni u collegato ad s che non sia già stato visitato}

    Casi base:
        D(s,s) = 0
        D(s,v) = INT_MAX (Inteso come infinito), se da s non esiste un percorso per v che obblighi a passare per una cella già visitata in precedenza

MATRICE DI MEMOIZATION (nxm)x(nxm):
Salvo il costo del minimo percorso da ogni cella verso ogni cella della matrice:

         0     1     2    ...  nxm-1
      |-----------------------------|
0     |  0  | ... |     |     | ... |
1     | ... |  0  |     |     |     |
2     |     |     |  0  |     |     |
...   |     | ... |     |  0  |     |
nxm-1 |     |     |     | ... |  0  |
      |-----------------------------|

Test:

MATRICE DI INPUT 1 nxm:
1 - 0 - 1 1 1
1 1 - 1 1 1 1
1 1 1 1 - 1 1
1 1 1 - 0 - 1

MATRICE DI INPUT 2 nxm:
1 - 0 - 1
1 1 - 1 1
1 1 1 1 1

MATRICE DI INPUT 3 nxm:
1 1 1
1 1 1
1 1 1

MATRICE DI INPUT 4 nxm:
1 1 - 1 1 1 1 1 1 1 1 1 1
1 - 0 - 1 1 1 1 - 1 1 1 1
1 1 - 1 1 1 1 - 0 - 1 1 1
1 1 - 1 1 - 1 1 - - 1 1 1
1 - 0 - - 0 - 1 - 0 - 1 1
1 1 - 1 1 - 1 1 1 - 1 1 1
1 1 1 1 1 1 1 1 - 0 - 1 1

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
int min_path(bool *matrix, int m_rows, int m_cols, int start_pos, int end_pos, bool *visited, int *memo);

int main(){

    bool m[7][13] = {
                        {1,1,1,1,1,1,1,1,1,1,1,1,1},
                        {1,1,0,1,1,1,1,1,1,1,1,1,1},
                        {1,1,1,1,1,1,1,1,0,1,1,1,1},
                        {1,1,1,1,1,1,1,1,1,1,1,1,1},
                        {1,1,0,1,1,0,1,1,1,0,1,1,1},
                        {1,1,1,1,1,1,1,1,1,1,1,1,1},
                        {1,1,1,1,1,1,1,1,1,1,0,1,1}
                    };
    int best_value_path = min_paths(m,7,13);

    printf("Il percorso minimo ha lunghezza: %d\n",best_value_path);
}

int min_paths(bool *matrix, int m_rows, int m_cols){

    int *memo = malloc(sizeof(int)*m_rows*m_cols*m_rows*m_cols);
    bool *visited = malloc(sizeof(bool)*m_rows*m_cols);
    if (!memo || !visited)
        exit(-1);
    
    memset(memo,-1,sizeof(int)*m_rows*m_cols*m_rows*m_cols);

    int best_path_value = INT_MAX;
    int temp;
    for (int i = 0; i < m_rows*m_cols; i = i + m_cols){

        for (int j = m_cols - 1; j < m_rows*m_cols; j = j + m_cols){
            
            //memset(visited,false,sizeof(bool)*m_rows*m_cols);
            temp = min_path(matrix,m_rows,m_cols,i,j,visited,memo);
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
    free(visited);
    return best_path_value != INT_MAX ? best_path_value : -1;
    
}

int min_path(bool *matrix, int m_rows, int m_cols, int start_pos, int end_pos, bool *visited, int *memo){

    visited[start_pos] = true;

    //printf("Parto da: %d\n",  start_pos);

    // Caso base, memorizzo e ritorno
    if (start_pos == end_pos){
        //printf("Sto scrivendo 0 nella pos %d, come costo del percorso (%d,%d)\n",memo_index(start_pos,end_pos,m_rows, m_cols),start_pos,end_pos);
        memo[memo_index(start_pos,end_pos,m_rows, m_cols)] = 0;
        return 0;
    }

    // Controllo se esiste già un risultato memorizzato
    if (memo[memo_index(start_pos,end_pos,m_rows, m_cols)] >= 0){
        //printf("*** STO FACENDO RIUSO ***\n");
        return memo[memo_index(start_pos,end_pos,m_rows, m_cols)];
    }
    
    int *neighbors = malloc(sizeof(int)*4);
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

        if (!visited[neighbors[i]]){
            
            temp = min_path(matrix, m_rows, m_cols, neighbors[i], end_pos, visited, memo);
            visited[neighbors[i]] = false;

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

    // Verifico se il nodo in SINISTRA è collegato al nodo [position]
    neighbor = position - 1;
    if ((position % m_cols != 0) && legal_pos(neighbor,m_rows,m_cols) && matrix[neighbor] == 1){
        condition = true;

        // Verifico se tale nodo ha un nodo in BASSO che è 0
        temp = neighbor + m_cols;
        if (legal_pos(temp,m_rows,m_cols) && matrix[temp] == 0)
            condition = false;
        // Verifico se tale nodo ha un nodo in SINISTRA che è 0
        temp = neighbor - 1;
        if ((neighbor % m_cols != 0) && legal_pos(temp,m_rows,m_cols) && matrix[temp] == 0)
            condition = false;
        // Verifico se tale nodo ha un nodo in ALTO che è 0
        temp = neighbor - m_cols;
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