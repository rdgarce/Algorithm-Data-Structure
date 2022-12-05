#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum Dim_t{
    BASE,
    ROW,
    COLUMN
}Dim_t;


typedef struct stack_t
{
    int index;
    int dim;
    int memory[];
}stack_t;

stack_t *create_stack(int dim);
void delete_stack(stack_t *s);
void empty_stack(stack_t *s);
bool is_empty(stack_t *s);
void stack_push(stack_t *s, int elem);
bool stack_pop(stack_t *s, int *elem);
int stack_head(stack_t *s);

int max_submatrix(bool *matrix, int m_rows, int m_cols);
int max_submatrix_v2_(bool *matrix, int m_rows, int m_cols, int position, int sub_m_h, int sub_m_w, Dim_t dim, int *visited);

int max_sub_matrix_size(bool *matrix, int m_rows, int m_cols);


#define LEGAL_POS(m_rows, m_cols, position) ((position) >= 0 && (position) < (m_rows)*(m_cols))
#define SAME_ROW(m_rows, m_cols, position1, position2) ((position1)/(m_cols) == (position2)/(m_cols))
#define MAX(one, two) ((one) > (two) ? (one) : (two))
#define MIN(one, two) ((one) < (two) ? (one) : (two))

#define MAX_TESTS 1000
#define MAX_ROWS 50
#define MAX_COLS 50
#define ONES_QNT 1/2
int main(){

    int n_tests = MAX_TESTS;
    int m_rows, m_cols;
    bool *matrix;
    int rand_pos;
    int res1, res2;
    for (int i = 0; i < n_tests; i++)
    {
        m_rows = rand() % MAX_ROWS + 1;
        m_cols = rand() % MAX_COLS + 1;

        matrix = calloc(m_rows*m_cols,sizeof(bool));
        if (!matrix)
        {
            printf("Errore di inizializzazione\n");
            exit(-1);
        }

        for (int i = 0; i < m_rows*m_cols*ONES_QNT; i++)
        {
            rand_pos = rand() % (m_rows*m_cols);
            if (matrix[rand_pos] != 1)
            {
                matrix[rand_pos] = 1;
            }
            else
            {
                while (matrix[rand_pos] == 1)
                {
                    rand_pos = rand() % (m_rows*m_cols);
                }
                matrix[rand_pos] = 1;
            }
            
        }

        res1 = max_submatrix(matrix,m_rows,m_cols);
        res2 = max_sub_matrix_size(matrix,m_rows,m_cols);

        if (res1 != res2)
        {
            printf("Errore trovato!\n>Res1 = %d e Res2 = %d\n",res1,res2);
            for (int i = 0; i < m_rows; i++)
            {
                for (int j = 0; j < m_cols; j++)
                {
                    printf("%d ",matrix[i*m_cols + j]);
                }
                printf("\n");
                
            }
            printf("\n");

        }
        free(matrix);

    }
    printf("Test terminati\n");
    
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

int max_sub_matrix_size(bool *matrix, int m_rows, int m_cols)
{
    int *TOP = malloc(sizeof(int)*m_cols);
    stack_t *STACK_indexes = create_stack(m_cols);
    stack_t *STACK_values = create_stack(m_cols);
    if (!TOP || !STACK_indexes || !STACK_values)
    {
        return -1;
    }
    
    int dummy;
    int area = 0;
    int max_area = 0;
    int index, value;

    for (int i = 0; i < m_rows; i++)
    {
        // Calcolo dello 0-esimo elemento della matrice TOP
        if (matrix[i*m_cols] == 0)
            LEGAL_POS(m_rows,m_cols,(i-1)*m_cols) ? (TOP[0] = TOP[0] + 1) : (TOP[0] = 1);
        else
            TOP[0] = 0;

        stack_push(STACK_values,TOP[0]);
        stack_push(STACK_indexes,0);

        for (int j = 1; j < m_cols; j++)
        {
            // Calcolo dello j-esimo elemento della matrice TOP
            if (matrix[i*m_cols + j] == 0)
                LEGAL_POS(m_rows,m_cols,(i-1)*m_cols + j) ? (TOP[j] = TOP[j] + 1) : (TOP[j] = 1);
            else
                TOP[j] = 0;

            // Calcolo della massima area
            index = j;
            value = TOP[j];
            while (!is_empty(STACK_indexes) && !is_empty(STACK_values) && TOP[j] < stack_head(STACK_values))
            {
                stack_pop(STACK_indexes,&index);
                stack_pop(STACK_values,&value);
                area = value*(j-index);
                if (area > max_area)
                    max_area = area;
            }

            stack_push(STACK_values,TOP[j]);
            stack_push(STACK_indexes,index);
        }

        // Calcolo della massima area con valori residui nello stack
        while (!is_empty(STACK_indexes) && !is_empty(STACK_values))
        {
            stack_pop(STACK_indexes,&index);
            stack_pop(STACK_values,&value);
            area = value*(m_cols-index);
            if (area > max_area)
                max_area = area;
        }
    }

    free(TOP);
    delete_stack(STACK_indexes);
    delete_stack(STACK_values);

    return max_area;
}

stack_t *create_stack(int dim)
{
    stack_t *s = malloc(sizeof(stack_t)+sizeof(int)*dim);
    s->index = 0;
    s->dim = dim;
    return s;
}

void delete_stack(stack_t *s)
{
    free(s);
}

void empty_stack(stack_t *s)
{
    s->index = 0;
}

bool is_empty(stack_t *s)
{
    return s->index == 0;
}

void stack_push(stack_t *s, int elem)
{
    s->memory[s->index] = elem;
    s->index = s->index + 1;
}

bool stack_pop(stack_t *s, int *elem)
{
    if (is_empty(s))
        return false;
    
    s->index = s->index - 1;
    *elem = s->memory[s->index];
    return true;
}

int stack_head(stack_t *s)
{
    return s->memory[s->index-1];
}