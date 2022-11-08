/*
* Stampare tutti i possibili percorsi dall'alto a sinistra in basso
* a destra di una matrice mXn con il vincolo 
* che da ogni cella puoi spostarti solo a destra o in basso.
*
* INPUT
* 1 2 3
* 4 5 6
*
* OUTPUT
* 1 4 5 6
* 1 2 5 6
* 1 2 3 6
*/

#include <stdio.h>
#include <stdbool.h>

#define MAX_MOVES 2
#define row_index(index,cols) (index/cols)
#define col_index(index,cols) (index%cols)

void print_solution(int *input_matrix,int rows, int cols, int *solution, int len);
bool is_a_solution(int *input_matrix, int rows, int cols, int *partial_solution, int sol_size);
void construct_candidates(int *input_matrix,int rows, int cols,
                            int *partial_solution, int sol_size,
                            int *array_of_moves, int *found_moves, int max_moves);
void matrix_navigator(int *input_matrix,int rows, int cols, int *partial_solution, int sol_size);



int main(){

    int input_t_1[][2]={{1,2},{3,4}};
    int partial_solution[4] = {0};

    matrix_navigator(input_t_1,2,2,partial_solution,1);

}

void print_array(int *A, int len){
    printf("[");
    for(int i=0;i<len;i++)
        printf("%d ", A[i]);
    printf("]");
}

void print_solution(int *input_matrix,int rows, int cols, int *solution, int len){
    printf("[");
    for(int i=0;i<len;i++)
        printf("%d ", input_matrix[solution[i]]);
    printf("]");
}


void matrix_navigator(int *input_matrix,int rows, int cols, int *partial_solution, int sol_size){
    
    if (is_a_solution(input_matrix, rows, cols, partial_solution, sol_size)){
        print_solution(input_matrix, rows, cols, partial_solution,sol_size);
        printf("\n");
    }
    else{

        int candidate_moves[MAX_MOVES];
        int n_candidate;

        construct_candidates(input_matrix, rows, cols, partial_solution, sol_size, candidate_moves, &n_candidate, MAX_MOVES);

        for (int i = 0; i < n_candidate; i++)
        {
            partial_solution[sol_size] = candidate_moves[i];
            matrix_navigator(input_matrix,rows,cols,partial_solution,sol_size + 1);
        }
        
    }

}

/*
* Ritorna true se [partial_solution] è una soluzione del problema in [input_matrix] di dimensione [rows]x[cols]
*/
inline bool is_a_solution(int *input_matrix, int rows, int cols, int *partial_solution, int sol_size){

    return input_matrix[partial_solution[sol_size-1]] == input_matrix[rows*cols -1];

}

/*
* Inserisce in [array_of_moves] un massimo di [max_moves] possibili prossime azioni 
* a partire dallo stato della [partial_solution] del problema in [input_matrix] 
* di dimensione [rows]x[cols] e valorizza [found_moves] con il numero di azioni prodotte. 
*/
void construct_candidates(int *input_matrix, int rows, int cols, int *partial_solution, int sol_size, int *array_of_moves, int *found_moves, int max_moves){
    
    int actual_state = partial_solution[sol_size-1];
    
    int n_found_moves = 0;
    // Verifico fattibilità mossa verso il basso
    if (actual_state + cols < rows*cols)
    {
        array_of_moves[n_found_moves] = actual_state + cols;
        n_found_moves++;
    }
    // Verifico fattibilità mossa verso destra
    if (actual_state + 1 < rows*cols && (actual_state + 1) % cols != 0)
    {
        array_of_moves[n_found_moves] = actual_state + 1;
        n_found_moves++;
    }

    *found_moves = n_found_moves;
    
}