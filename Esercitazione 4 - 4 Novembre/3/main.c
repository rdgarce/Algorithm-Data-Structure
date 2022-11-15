#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void backtracking(int *matrix, int m_rows, int m_cols, int *partial_solution, int sol_size, int *max_path_lenght);
void construct_candidates(int *matrix, int m_rows, int m_cols, int *partial_solution, int sol_size, 
                                                                int *array_of_moves, int *n_moves);
void print_array(int *A, int len);

#define MAX_SIZE 100
#define MAX_N_TESTS 15

int main(){

    int *matrix[MAX_N_TESTS];
    int partial_solution[MAX_SIZE*MAX_SIZE];
    int n_test;
    char name[MAX_N_TESTS][64];
    int m_rows[MAX_N_TESTS]; 
    int m_cols[MAX_N_TESTS];

    scanf("%d\n",&n_test);
    for (int n = 0; n < n_test; n++)
    {
        scanf("%s %d %d\n",name[n],&(m_rows[n]),&(m_cols[n]));
        matrix[n] = malloc(sizeof(int)*m_rows[n]*m_cols[n]);
        for (int i = 0; i < m_rows[n]; i++)
        {
            for (int j = 0; j < m_cols[n]; j++)
            {   
                scanf("%d",&matrix[n][i*m_cols[n] + j]);
            }

        }  
    }

    int max_path_lenght = 0;
    int temp = 0;
    for (int n = 0; n < n_test; n++)
    {
        temp = 0;
        max_path_lenght = 0;
        // Chiamo backtracking sulla matrice e stampo
        for (int i = 0; i < m_rows[n]; i++)
        {
            for (int j = 0; j < m_cols[n]; j++)
            {
                partial_solution[0] = i*m_cols[n] + j;
                backtracking(matrix[n],m_rows[n],m_cols[n],partial_solution,1,&temp);
                if (temp > max_path_lenght)
                {
                    max_path_lenght = temp;
                }
                
            }
        
        }
        printf("%s: %d\n",name[n],max_path_lenght);
    }

}

void backtracking(int *matrix, int m_rows, int m_cols, int *partial_solution, int sol_size, int *max_path_lenght){

    int *array_of_moves = malloc(sizeof(int)*4);
    int n_moves;

    construct_candidates(matrix,m_rows,m_cols,partial_solution,sol_size,array_of_moves,&n_moves);

    if (n_moves == 0 && sol_size > (*max_path_lenght))
    {
        (*max_path_lenght) = sol_size;
    }

    for (int i = 0; i < n_moves; i++)
    {
        partial_solution[sol_size] = array_of_moves[i];
        backtracking(matrix,m_rows,m_cols,partial_solution,sol_size+1,max_path_lenght);
    }

    free(array_of_moves);
    
}

void construct_candidates(int *matrix, int m_rows, int m_cols, int *partial_solution, int sol_size, 
                                                                int *array_of_moves, int *n_moves){
    
    int count = 0;
    int position = partial_solution[sol_size-1];    
    int up = position - m_cols;
    int right = position + 1;
    int down = position + m_cols;
    int left = position - 1;

    if (up >= 0 && up < m_rows*m_cols && matrix[up] < matrix[position])
    {
        array_of_moves[count] = up;
        count++;
    }
    if (right%m_cols != 0 && matrix[right] < matrix[position])
    {
        array_of_moves[count] = right;
        count++;
    }
    if (down >= 0 && down < m_rows*m_cols && matrix[down] < matrix[position])
    {
        array_of_moves[count] = down;
        count++;
    }
    
    if (position % m_cols != 0 && matrix[left] < matrix[position])
    {
        array_of_moves[count] = left;
        count++;
    }

    *n_moves = count;
}

void print_array(int *A, int len){
    printf("[");
    for(int i=0;i<len;i++)
        printf("%d ", A[i]);
    printf("]");
}