#include <iostream>
#include <unistd.h>
#include <vector>


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




#define MAX_TEST 5000
#define R_MAX 7
#define C_MAX 7

int matrix[R_MAX*C_MAX];


/*
Soluzione con backtracking la complessità attesa nel caso peggiore, è O(n*(4^(n*m))) dove n è il numero di righe.

*/

using namespace std;

//Struttura definita per identificare una posizione all'interno della matrice.
typedef struct pos{

    int x,y;//x= riga, y = colonna
    bool operator==(const struct pos &my){return (this->x==my.x && this->y == my.y);} //Overload dell operatore di uaguaglianza
    void print(){cout<<this->x<<","<<this->y;}                                        //Funzione di comodo.

}Pos;

//stampa la boards nel caso di stampa post soluzioen fa vedere anche i valori "- 1" assegnati che percorrono il percorso trovato. 
void print_boards(vector <vector<int> > &boards)
{
    for (size_t i = 0; i < boards.size(); i++)
    {
        for (size_t j = 0; j < boards[i].size(); j++)
        {
            cout<<boards[i][j]<<" ";
        }cout<<"\n";
        
    }
}

//Stampa la soluzione trovata.
void display_solution(vector <Pos> &solution)
{
    cout<<"PATH = ";
    for (size_t i = 0; i < solution.size(); i++)
    {
        solution[i].print();
        if(i<solution.size()-1)
            cout<<" -> ";

    }
    cout<<endl;
    cout<<"Solution size = "<<solution.size()<<"\n";    

}

//Posizione che verifica le next move se sono possibili ritorna true
bool check_0(vector < vector <int> > &visit,Pos current, vector <vector <int> > &boards){

    if(current.x >= 0 && current.y < boards[current.x].size() && current.x < boards.size() && current.y >= 0)
        if(visit[current.x][current.y] != 1 )
            if(boards[current.x][current.y] != 0 && boards[current.x][current.y] != 2)
                return true;
    
    return false;

}

//funziona ricorsiva che prova tutti i percorsi .
//"main" del backtracking tenta ogni possibile strada fattibile finchè riesce a proseguire.
//La complessità è esponenzia ed è dipendente da quanti vincoli ho sul percorso.
void backtracking(vector < vector <int> > &visit ,vector <Pos> &ending_solution, vector <Pos> &current_solution, Pos current_posizion, vector <vector <int> > &boards){

    if(current_posizion.y == boards[0].size()-1)
    {
        current_solution.push_back(current_posizion);

        visit[current_posizion.x][current_posizion.y] = 1;

        if (ending_solution.empty()==true)
        {
            ending_solution = current_solution;
        }
        else if( ending_solution.size() > current_solution.size()) //process solution
        {   
            ending_solution.clear();
            ending_solution = current_solution;
        }

    }
    else
    {  
        
        /*-------------------------------------------------------------------------------------------------   
        |    Qui verifico se la soluzione corrente è già maggiore si una soluzione trovata in precedenza,  |
        |    in queso caso non c'è alcun motivo di continuare la ricerca,                                  |
        |    quindi applico un "pruning dell'albero di ricorsione."                                        |
        ---------------------------------------------------------------------------------------------------*/
        current_solution.push_back(current_posizion);
        if(ending_solution.empty()==false)
        {
            if(current_solution.size() >= ending_solution.size())
                return;            
        }

        //La matrice visit mi tiene traccia dei percorsi già visitati.
        visit[current_posizion.x][current_posizion.y] = 1;
        
        //Possibili nuovi spostamenti.
        Pos current_go_right = {.x = current_posizion.x, .y = current_posizion.y + 1};
        Pos current_go_down = {.x = current_posizion.x-1, .y = current_posizion.y};
        Pos current_go_up = {.x = current_posizion.x + 1, .y = current_posizion.y};
        Pos current_go_left = {.x = current_posizion.x, .y = current_posizion.y -1};

        //Per ogni possibile nuova posizione sulla matrice eseguo prima un check sulla fattibilità dello spostamento,
        //dopo questo richiamo ricorsivamente "backtraking" con il nuovo punto dato dalla mossa eseguita.
        if(check_0(visit,current_go_right,boards))
            backtracking(visit, ending_solution, current_solution,current_go_right,boards);

        if(check_0(visit, current_go_down,boards))
            backtracking(visit, ending_solution, current_solution, current_go_down,boards);
        
        if(check_0(visit, current_go_up,boards))
            backtracking(visit, ending_solution, current_solution, current_go_up,boards);
        
        if(check_0(visit, current_go_left, boards))
            backtracking(visit, ending_solution, current_solution, current_go_left,boards);     

        
        current_solution.pop_back();
        visit[current_posizion.x][current_posizion.y] = 0;

    }
}

//Processa una matrice data in quanto essendo anche i punti adiacenti agli "0" inaccessibili,
//è coneventiente preprocessare la matrice con gli "0" inserendo dei "2" vicino a quest'ultimi,
//così facendo la funzione di check per le posizione possibili risulta di immediata implementazione.
vector <vector <int > > pre_processing_matrix(vector < vector <int> > &matrix)
{

    vector < vector <int> >new_matrix = matrix;

    for (size_t i = 0; i < new_matrix.size(); i++)
    {
        for (size_t j = 0; j < new_matrix[0].size(); j++)
        {
            if (new_matrix[i][j] == 0)
            {
                if(j < new_matrix[i].size()-1)
                    {
                        if(new_matrix[i][j+1]!= 0)
                            new_matrix[i][j+1] = 2;
                    }
                if(j > 0)
                    {
                        if(new_matrix[i][j-1]!= 0)
                            new_matrix[i][j-1] = 2;
                    }
                if(i > 0)
                    {
                        if(new_matrix[i-1][j]!= 0)
                            new_matrix[i-1][j] = 2;
                    }
                if(i< new_matrix.size()-1)
                    {
                        if(new_matrix[i+1][j]!= 0)
                            new_matrix[i+1][j] = 2;
                    }
            }
            
            
        }
            
    }
    
   return new_matrix;    

}

//Per ridurre ulteriormente la complessità verifico se esiste almeno una soluzione,
//tale verifica è effettuata considerando una colonna fissata verificare se esiste almeno un "1" altrimenti, 
//c'è un muro di "0" o di "1" vicino agli zero.
bool is_there_a_wall(vector <vector <int> > &matrix)
{
    
    for (size_t i = 0; i < matrix[0].size(); i++)
    {
        int count = 0;
        for (size_t j = 0; j < matrix.size(); j++)
        {
            if(matrix[j][i] ==0 || matrix[j][i]==2)count++;
        }
        if(count==matrix.size())return true; //ho trovato un muro
    }
    return false;
}

//La funzione find_min_path inizia già il backtracking, prunacompletamente dei rami se portano a percorsi senza soluzione,
//o se non hanno punti di partenza.
//Infine lancia per ogni punto di partenza disponibile il backtracking.
int find_min_path(vector <vector <int> > &boards)
{
    //cout<<"start\n";
    vector <Pos> curr;
    vector <Pos> ending;

    vector <vector <int> >visit;

    visit.resize(boards.size(),vector <int> (boards[0].size()));

    vector <vector <int> >max = pre_processing_matrix(boards);

    int max_path = 4000;
    vector <Pos> real_ending(max_path);
    
    if (is_there_a_wall(max)) 
    {
        real_ending.clear();
        return 0;
    }
    //cout<<"superato primo check\n";
    int i,j;
    for (i = 0; i < max.size(); i++)
        {
            for (j=0;j<max.size();j++)
                {
                    vector <Pos> curr;
                    vector <Pos> ending;
                    vector <vector <int> >visit;
                    visit.resize(boards.size(),vector <int> (boards[0].size()));
                    vector <vector <int> >max = pre_processing_matrix(boards);
                    
                    if(check_0(visit,(Pos){i,0},max) && check_0(visit,(Pos){j,(int)boards[0].size()-1},max))
                        backtracking(visit, ending, curr, (Pos){i,0}, max);
                    
                    
                    if(real_ending.empty() != true && ending.empty() != true && real_ending.size() > ending.size())
                        {
                            real_ending = ending;
                        }

                }
            
        }
        
    if(real_ending.size()==max_path)real_ending.clear();
    //cout<<"fine"<<endl;
    return real_ending.size();
}



int main(int argc, char const *argv[])
{
    srand(getpid());

    int i,j,k,d,l,r,c;

    for (i = 0; i < MAX_TEST; i++)
    {
        //cout<<"indice test : "<<i<<"\n";
        int_least64_t rand_i = 0;
        int_least64_t rand_j = 0;
        r = (rand()%(R_MAX-5)) + 5;
        c = (rand()%(C_MAX-6)) + 6;
        for (j = 0; j < r; j++)
        {
            for (d = 0; d < c; d++)
            {
                matrix[j*c + d] = 1;
            }
            
        }
        int k = r/3 + c/3;
        
        for (l = 0; l < k; l++)
        {
        
            rand_i = rand()%r;
            
            rand_j = rand()%(c-5)+2;
            

            matrix[rand_i*c + rand_j] = 0;
        }
        
        vector < vector <int> > board;
        board.resize(r, vector<int> (c));

        for ( int p = 0; p < r; p++)
        {
            for(j = 0;j<c;j++)
                board[p][j] = matrix[p*c + j];
        }
        
        //print_boards(board);
        

        int res1 = find_min_path(board) - 1;

        bool *matrix2 = (bool*)malloc(sizeof(bool)*r*c);
        for (int i = 0; i < r*c; i++)
        {
            if (matrix[i] == 0)
            {
                matrix2[i] = false;
            }
            else
            {
                matrix2[i] = true;
            }
            
        }
        

        int res2 = min_paths(matrix2,r,c);
        free(matrix2);
        //printf("Res1 = %d Res2 = %d\n",res1,res2);
        if(res1!=res2)
            {
                printf("Errore trovato!\nRes1 = %d Res2 = %d\n",res1,res2);
                for (int j = 0; j < r; j++)
                {
                    for(int p = 0;p<c;p++)
                        cout<<matrix[j*c + p]<<" ";
                    cout<<endl;
                }
                
            }
        
    }

    

    return 0;
}

int min_paths(bool *matrix, int m_rows, int m_cols)
{
    int *memo = (int*)malloc(sizeof(int)*(m_rows*m_cols)*(m_rows*m_cols)*(m_rows*m_cols));
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
    
    int *neighbors = (int*)malloc(sizeof(int)*4);
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