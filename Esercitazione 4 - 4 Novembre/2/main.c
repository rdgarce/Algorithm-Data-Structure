#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define i2c(i) (i + '0')
#define c2i(i) (i - '0')

void chess_game(char *board, int board_dim, int *partial_solution, int sol_size, int *solutions_count);

bool is_solution(int sol_size, int board_dim);

void make_move(char *board, int board_dim, int queen_pos);

void unmake_move(char *board, int board_dim, int queen_pos);

void construct_candidate(char* board, int board_dim, int *partial_solution, int sol_size, int *array_of_moves, int *found_moves_count);

void printBoard(char *board, int board_dim);

char *get_chessboard(int dim);

void print_array(int *A, int len);

int main(){

    int board_size = 5;
    char *chessboard = get_chessboard(board_size);
    int *partial_solution = malloc(sizeof(int)*board_size);
    int result = 0;

    if (!partial_solution)
            exit(1);

    chess_game(chessboard,board_size,partial_solution,0,&result);
    printf("Risultato: %d\n",result);
 
}


bool is_solution(int sol_size, int board_dim){
    return sol_size == board_dim;
}

void chess_game(char *board, int board_dim, int *partial_solution, int sol_size, int *solutions_count){

    //printf("Solution size: %d\n",sol_size);
    if (is_solution(sol_size,board_dim)){
        (*solutions_count)++;
        /*
        printf("*** Ho trovato una soluzione\n");
        print_array(partial_solution,sol_size);
        printf("\n");
        */
    }
    else{

        int *next_moves = malloc(sizeof(int)*board_dim*board_dim);
        if (!next_moves)
            exit(1);
        
        int moves_count;

        construct_candidate(board,board_dim,partial_solution,sol_size,next_moves,&moves_count);

        /*
        printf("Stampo array della solutione parziale: ");
        print_array(partial_solution,sol_size);
        printf("\n");

        printf("Stampo array delle mosse possibili: ");
        print_array(next_moves,moves_count);
        printf("\n");
        */

        for (int i = 0; i < moves_count; i++){

            partial_solution[sol_size] = next_moves[i];
            make_move(board,board_dim,next_moves[i]);
            //printf("Ho inserito una regina in pos: %d\n",next_moves[i]);
            //printBoard(board,board_dim);
            //printf("\n");
            chess_game(board,board_dim,partial_solution,sol_size+1,solutions_count);
            unmake_move(board,board_dim,next_moves[i]);
        }
        
    }

}

void make_move(char *board, int board_dim, int queen_pos){

    int first_row_elem = (queen_pos/board_dim) * board_dim;
    int first_col_elem = queen_pos - first_row_elem;

    int row_index = first_row_elem/board_dim;
    int col_index = first_col_elem%board_dim;
    
    int maj_diag_factor = col_index >= row_index ? row_index : col_index;
    int first_maj_diag_elem = queen_pos - (board_dim+1)*maj_diag_factor;

    int min_diag_factor = (board_dim-1-col_index) >= row_index ? row_index : board_dim-1-col_index;
    int first_min_diag_elem = queen_pos - (board_dim-1)*min_diag_factor;

    //printf("first_row_elem: %d\nfirst_col_elem: %d\nrow_index: %d\ncol_index: %d\nmaj_diag_factor: %d\nfirst_maj_diag_elem: %d\n",first_row_elem,first_col_elem,row_index, col_index, maj_diag_factor,first_maj_diag_elem);

    // Aggiunge 1 alla diagonale maggiore
    while (first_maj_diag_elem >= 0 && first_maj_diag_elem < board_dim*board_dim){
        board[first_maj_diag_elem]++;
        if ((first_maj_diag_elem + board_dim + 1)%board_dim <= first_maj_diag_elem%board_dim)
            break;
        
        first_maj_diag_elem = first_maj_diag_elem + board_dim + 1;
        
    }
    
    // Aggiunge 1 alla diagonale minore
    while (first_min_diag_elem >= 0 && first_min_diag_elem < board_dim*board_dim){
        board[first_min_diag_elem]++;
        if ((first_min_diag_elem + board_dim - 1)%board_dim >= first_min_diag_elem%board_dim)
            break;

        first_min_diag_elem = first_min_diag_elem + board_dim - 1;
    }
    
    // Aggiunge 1 alle righe e alle colonne
    for (int i = 0; i < board_dim; i++){
        board[first_row_elem]++;
        board[first_col_elem]++;
        first_row_elem++;
        first_col_elem = first_col_elem + board_dim;

    }
    
    board[queen_pos] = 'Q';

}

void construct_candidate(char* board, int board_dim, int *partial_solution, int sol_size, int *array_of_moves, int *found_moves_count){

    int moves_count = 0;

    for (int i = 0; i < board_dim*board_dim; i++){
        if (board[i] == '0' && i >= partial_solution[sol_size-1]){
            array_of_moves[moves_count] = i;
            moves_count++;
        }
    }
    
    *found_moves_count = moves_count;

}

void unmake_move(char *board, int board_dim, int queen_pos){    

    int first_row_elem = (queen_pos/board_dim) * board_dim;
    int first_col_elem = queen_pos - first_row_elem;

    int row_index = first_row_elem/board_dim;
    int col_index = first_col_elem%board_dim;
    
    int maj_diag_factor = col_index >= row_index ? row_index : col_index;
    int first_maj_diag_elem = queen_pos - (board_dim+1)*maj_diag_factor;

    int min_diag_factor = (board_dim-1-col_index) >= row_index ? row_index : board_dim-1-col_index;
    int first_min_diag_elem = queen_pos - (board_dim-1)*min_diag_factor;

    // Sottrae 1 alla diagonale maggiore
    while (first_maj_diag_elem >= 0 && first_maj_diag_elem < board_dim*board_dim){
        board[first_maj_diag_elem]--;
        if ((first_maj_diag_elem + board_dim + 1)%board_dim <= first_maj_diag_elem%board_dim)
            break;
        
        first_maj_diag_elem = first_maj_diag_elem + board_dim + 1;
        
    }
    
    // Sottrae 1 alla diagonale minore
    while (first_min_diag_elem >= 0 && first_min_diag_elem < board_dim*board_dim){
        board[first_min_diag_elem]--;
        if ((first_min_diag_elem + board_dim - 1)%board_dim >= first_min_diag_elem%board_dim)
            break;

        first_min_diag_elem = first_min_diag_elem + board_dim - 1;
    }
    
    // Sottrae 1 alle righe e alle colonne
    for (int i = 0; i < board_dim; i++){
        board[first_row_elem]--;
        board[first_col_elem]--;
        first_row_elem++;
        first_col_elem = first_col_elem + board_dim;

    }
    
    board[queen_pos] = '0';

}

void printBoard(char *board, int board_dim){
    
    for (int i = 0; i < board_dim; i++){

        for (int j = 0; j < board_dim; j++){
            
            printf("%c ",board[i*board_dim + j]);
        }
        printf("\n");
        /* code */
    }
    
}

char *get_chessboard(int dim){

    char *board = malloc(dim*dim);
    if (!board)
        return NULL;
    
    memset(board,'0',dim*dim);
    return board;
}

void print_array(int *A, int len){
    printf("[");
    for(int i=0;i<len;i++)
        printf("%d ", A[i]);
    printf("]");
}