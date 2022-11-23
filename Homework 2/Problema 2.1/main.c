/*

Soluzione:
Il problema viene risolto mediante la programmazione dinamica, sotto alcune ipotesi che permettono
di visualizzarlo logicamente come quello di trovare il minimo percorso tra nodi in un grafo ciclico.
IPOTESI:
1) Ogni cella della matrice che contiene '1', e soltanto '1', diventa un nodo in un grafo, 
   a meno che essa non sia adiacente ad una cella contenente uno '0',
2) Ogni nodo è connesso a tutti i nodi che corrispondono a celle adiacenti nella matrice di partenza,

Le due ipotesi permettono di costruire un grafo (logico) corrispondente alla matrice e
ricondurre il problema a quello del minimo percorso con k mosse.

Formula della ricorsione:
D(s,v)_{k} = min_u{1 + D(u,v)_{k-1} | per ogni u collegato ad s che non sia già stato visitato}

    Casi base:
        D(s,s)_{k} = 0, Per ogni k
        D(s,v)_{k} = INT_MAX (Inteso come infinito), se k = 0

Per il caso in analisi, si fissa k = n*m, in quanto si suppone, come limite superiore, che tutte le celle della matrice
diventino nodi del grafo.

MATRICE DI MEMOIZATION k*(n*m)*(n*m):
Viene salvato il costo del minimo percorso da ogni cella verso ogni cella della matrice, per tutti i possibili k

     k=0\   0     1     2    ...  nxm-1
         |-----------------------------|
   0     |  0  | ... |     |     | ... |
   1     | ... |  0  |     |     |     |
   2     |     |     |  0  |     |     |
   ...   |     | ... |     |  0  |     |
   nxm-1 |     |     |     | ... |  0  |
         |-----------------------------|

     k=1\   0     1     2    ...  nxm-1
         |-----------------------------|
   0     |  0  | ... |     |     | ... |
   1     | ... |  0  |     |     |     |
   2     |     |     |  0  |     |     |
   ...   |     | ... |     |  0  |     |
   nxm-1 |     |     |     | ... |  0  |
         |-----------------------------|

                        .
                        .
                        .

 k=n*m-1\   0     1     2    ...  nxm-1
         |-----------------------------|
   0     |  0  | ... |     |     | ... |
   1     | ... |  0  |     |     |     |
   2     |     |     |  0  |     |     |
   ...   |     | ... |     |  0  |     |
   nxm-1 |     |     |     | ... |  0  |
         |-----------------------------|

Test:

MATRICE DI INPUT 1 4x7:
1 1 0 1 1 1 1
1 1 1 1 1 1 1
1 1 1 1 1 1 1
1 1 1 1 0 1 1

MATRICE DI INPUT 2 3x5:
1 1 0 1 1
1 1 1 1 1
1 1 1 1 1

MATRICE DI INPUT 3 3x3:
1 1 1
1 1 1
1 1 1

MATRICE DI INPUT 4 7x13:
1 1 1 1 1 1 1 1 1 1 1 1 1
1 1 0 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 0 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1 1
1 1 0 1 1 0 1 1 1 0 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 0 1 1 1

*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

#define LEGAL_POS(index,rows,cols) ((index) >= 0 && (index) < (rows)*(cols))
#define MEMO_INDEX(start_pos, end_pos, k, rows, cols) ((start_pos)*(cols)*(rows) + (end_pos) + (k)*(rows)*(cols)*(rows)*(cols))

void indegree(bool *matrix, int m_rows, int m_cols, int *array_of_position, int *array_size, int position);
void print_array(int *A, int len);
int min_paths(bool *matrix, int m_rows, int m_cols);
int min_path(bool *matrix, int m_rows, int m_cols, int prev_pos, int start_pos, int end_pos, int k, int *memo);

int main(){

    int n_tests;
    int m_rows;
    int m_cols;
    bool *matrix;

    printf("Inserire il numero di casi di test\n");
    scanf("%d",&n_tests);
    for (int i = 0; i < n_tests; i++)
    {
        printf("Inserire #righe #colonne del #%d caso di test\n",i+1);
        scanf("%d %d",&m_rows, &m_cols);
        matrix = malloc(sizeof(bool)*m_rows*m_cols);
        if (!matrix)
            exit(-1);
        
        for (int i = 0; i < m_rows*m_cols; i++)
        {
            scanf("%d",&matrix[i]);
        }

        printf("Il percorso minimo della matrice del #%d caso di test ha lunghezza: %d\n",i+1,min_paths(matrix,m_rows,m_cols));
        free(matrix);
    }
    
}

/*
* Data la matrice [matrix] di [m_rows] righe e [m_cols] colonne,restituisce il minor numero di spostamenti
* necessari per arrivare da una qualsiasi delle posizioni della prima colonna della matrice ad una qualsiasi
* di quelle dell'ultima colonna, oppure -1 se non esiste alcun percorso.
* -----
* NOTA BENE:
* 1) In numero di spostamenti viene inteso come il numero di celle che è necessario percorrere dalla sorgente
*    alla destinazione, esclusa la sorgente. (e.g.: A->B->C. Il numero di spostamenti da A a C è 2).
* 2) E' stato assunto che tutti gli elementi della prima colonna e tutti quelli dell'ultima non siano 0 ne
*    siano adiacenti ad uno 0. Quindi che sia possibile "partire" da ogni cella della prima colonna e 
*    "arrivare" in ogni cella dell'ultima colonna.
* 3) Non è possibile elaborare percorsi con numero di spostamenti maggiore di INT_MAX-1,
*    quindi [m_rows]*[m_cols] <= INT_MAX-1
*/
int min_paths(bool *matrix, int m_rows, int m_cols)
{
    int *memo = malloc(sizeof(int)*(m_rows*m_cols)*(m_rows*m_cols)*(m_rows*m_cols));
    if (!memo)
        exit(-1);
    
    memset(memo,-1,sizeof(int)*(m_rows*m_cols)*(m_rows*m_cols)*(m_rows*m_cols));

    int best_path_value = INT_MAX;
    int temp;
    
    // Ciclo su tutti gli elementi della prima colonna
    for (int i = 0; i < m_rows*m_cols; i = i + m_cols)
    {
        // Ciclo su tutti gli elementi dell'ultima colonna
        for (int j = m_cols - 1; j < m_rows*m_cols; j = j + m_cols)
        {
            temp = min_path(matrix,m_rows,m_cols,i,i,j, m_rows*m_cols -1, memo);
            if (temp < best_path_value)
                best_path_value = temp;
        }
    }
    
    free(memo);
    return best_path_value != INT_MAX ? best_path_value : -1;
}

int min_path(bool *matrix, int m_rows, int m_cols,int prev_pos, int start_pos, int end_pos, int k, int *memo)
{
    // Caso base 1: memorizzo e ritorno
    if (start_pos == end_pos)
    {
        memo[MEMO_INDEX(start_pos, end_pos, k, m_rows, m_cols)] = 0;
        return 0;
    }

    // Caso base 2: memorizzo e ritorno
    if (k == 0 && start_pos != end_pos)
    {
        memo[MEMO_INDEX(start_pos, end_pos, k, m_rows, m_cols)] = INT_MAX;
        return INT_MAX;
    }
    
    // Controllo l'esistenza di un risultato precedentemente memorizzato
    if (memo[MEMO_INDEX(start_pos, end_pos, k, m_rows, m_cols)] >= 0)
    {
        return memo[MEMO_INDEX(start_pos, end_pos, k, m_rows, m_cols)];
    }
    
    int *neighbors = malloc(sizeof(int)*4);
    if (!neighbors)
        exit(-1);
    
    int size;

    // Calcolo le celle raggiungibili da quella attuale
    indegree(matrix,m_rows,m_cols,neighbors,&size,start_pos);

    int result = INT_MAX;
    int temp;

    // Iterazione su tutte le celle raggiungibili
    for (int i = 0; i < size; i++)
    {
        // Evito di rivisitare il nodo da cui sono arrivato
        if (neighbors[i] == prev_pos)
            continue;
        
        // Calcolo della soluzione ottima del sottoproblema per il nodo prossimo con (k-1) mosse
        temp = min_path(matrix, m_rows, m_cols,start_pos, neighbors[i], end_pos, k-1, memo);
        
        // Trovo il percorso di minimo costo tra i sottoproblemi
        if (temp < result)
            result = temp + 1;
    }
    
    // Salvataggio della soluzione del problema attuale
    memo[MEMO_INDEX(start_pos, end_pos, k, m_rows, m_cols)] = result;        

    free(neighbors);
    
    return result;
}

/*
* Data la matrice [matrix] di [m_rows] righe e [m_cols] colonne, e dato [array_of_position], puntatore a
* vettore di int allocato dal chiamante, popola [array_of_position] con gli indici delle posizioni di
* [matrix] in cui è possibile arrivare a partire da quella con indice [position]. 
* Infine, inserisce nella memoria puntata da [array_size] il numero di posizioni raggiungibili.
*/
void indegree(bool *matrix, int m_rows, int m_cols, int *array_of_position, int *array_size, int position)
{
    int count = 0;
    int neighbor;
    int temp;
    bool condition = false;

    // Verifico se il nodo in DESTRA è collegato al nodo [position]
    neighbor = position + 1;
    if ((neighbor % m_cols != 0) && LEGAL_POS(neighbor,m_rows,m_cols) && matrix[neighbor] == 1)
    {
        condition = true;

        // Verifico se tale nodo ha un nodo in ALTO che è 0
        temp = neighbor - m_cols;
        if (LEGAL_POS(temp,m_rows,m_cols) && matrix[temp] == 0)
            condition = false;
        // Verifico se tale nodo ha un nodo in BASSO che è 0
        temp = neighbor + m_cols;
        if (LEGAL_POS(temp,m_rows,m_cols) && matrix[temp] == 0)
            condition = false;
        // Verifico se tale nodo ha un nodo in DESTRA che è 0
        temp = neighbor + 1;
        if ((temp % m_cols != 0) && LEGAL_POS(temp,m_rows,m_cols) && matrix[temp] == 0)
            condition = false;
    }
    if (condition == true)
    {
        array_of_position[count] = neighbor;
        count++;
        condition = false;
    }

    // Verifico se il nodo in ALTO è collegato al nodo [position]
    neighbor = position - m_cols;
    if (LEGAL_POS(neighbor,m_rows,m_cols) && matrix[neighbor] == 1)
    {
        condition = true;

        // Verifico se tale nodo ha un nodo in ALTO che è 0
        temp = neighbor - m_cols;
        if (LEGAL_POS(temp,m_rows,m_cols) && matrix[temp] == 0)
            condition = false;
        // Verifico se tale nodo ha un nodo in SINISTRA che è 0
        temp = neighbor - 1;
        if ((neighbor % m_cols != 0) && LEGAL_POS(temp,m_rows,m_cols) && matrix[temp] == 0)
            condition = false;
        // Verifico se tale nodo ha un nodo in DESTRA che è 0
        temp = neighbor + 1;
        if ((temp % m_cols != 0) && LEGAL_POS(temp,m_rows,m_cols) && matrix[temp] == 0)
            condition = false;
    }
    if (condition == true)
    {
        array_of_position[count] = neighbor;
        count++;
        condition = false;
    }

    // Verifico se il nodo in BASSO è collegato al nodo [position]
    neighbor = position + m_cols;
    if (LEGAL_POS(neighbor,m_rows,m_cols) && matrix[neighbor] == 1)
    {
        condition = true;

        // Verifico se tale nodo ha un nodo in BASSO che è 0
        temp = neighbor + m_cols;
        if (LEGAL_POS(temp,m_rows,m_cols) && matrix[temp] == 0)
            condition = false;
        // Verifico se tale nodo ha un nodo in SINISTRA che è 0
        temp = neighbor - 1;
        if ((neighbor % m_cols != 0) && LEGAL_POS(temp,m_rows,m_cols) && matrix[temp] == 0)
            condition = false;
        // Verifico se tale nodo ha un nodo in DESTRA che è 0
        temp = neighbor + 1;
        if ((temp % m_cols != 0) && LEGAL_POS(temp,m_rows,m_cols) && matrix[temp] == 0)
            condition = false;
    }
    if (condition == true)
    {
        array_of_position[count] = neighbor;
        count++;
        condition = false;
    }

    // Verifico se il nodo in SINISTRA è collegato al nodo [position]
    neighbor = position - 1;
    if ((position % m_cols != 0) && LEGAL_POS(neighbor,m_rows,m_cols) && matrix[neighbor] == 1)
    {
        condition = true;

        // Verifico se tale nodo ha un nodo in BASSO che è 0
        temp = neighbor + m_cols;
        if (LEGAL_POS(temp,m_rows,m_cols) && matrix[temp] == 0)
            condition = false;
        // Verifico se tale nodo ha un nodo in SINISTRA che è 0
        temp = neighbor - 1;
        if ((neighbor % m_cols != 0) && LEGAL_POS(temp,m_rows,m_cols) && matrix[temp] == 0)
            condition = false;
        // Verifico se tale nodo ha un nodo in ALTO che è 0
        temp = neighbor - m_cols;
        if (LEGAL_POS(temp,m_rows,m_cols) && matrix[temp] == 0)
            condition = false;
    }
    if (condition == true)
    {
        array_of_position[count] = neighbor;
        count++;
        condition = false;
    }

    *array_size = count;
    
}

void print_array(int *A, int len)
{
    printf("[");
    for(int i=0;i<len;i++)
        printf("%d ", A[i]);
    printf("]");
}