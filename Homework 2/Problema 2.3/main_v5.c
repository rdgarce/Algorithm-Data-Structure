#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct stack_t
{
    int index;
    int memory[];
}stack_t;

stack_t *create_stack(int dim);
void delete_stack(stack_t *s);
void empty_stack(stack_t *s);
bool is_empty(stack_t *s);
void stack_push(stack_t *s, int elem);
bool stack_pop(stack_t *s, int *elem);
int stack_head(stack_t *s);

int max_sub_matrix_size(bool *matrix, int m_rows, int m_cols);

#define LEGAL_POS(m_rows, m_cols, position) ((position) >= 0 && (position) < (m_rows)*(m_cols))
#define SAME_ROW(m_rows, m_cols, position1, position2) ((position1)/(m_cols) == (position2)/(m_cols))
#define MAX(one, two) ((one) > (two) ? (one) : (two))
#define MIN(one, two) ((one) < (two) ? (one) : (two))

/*
1 0 0 
0 1 0 
0 0 1 
1 0 0 
1 1 1
*/

int main(){

    bool m[] = {
            0,0,1,
            1,0,0,
            1,0,0,
            1,1,0,
            0,1,1
            };
    
    int res = max_sub_matrix_size(m,5,3);
    printf("RES: %d\n",res);
}

int max_sub_matrix_size(bool *matrix, int m_rows, int m_cols)
{
    int *TOP = calloc(m_cols,sizeof(int));
    stack_t *STACK_indexes = create_stack(m_cols);
    stack_t *STACK_values = create_stack(m_cols);
    if (!TOP || !STACK_indexes || !STACK_values)
    {
        return -1;
    }
    
    int dummy;
    int area = 0;
    int max_area = 0;

    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            // Calcolo del j-esimo elemento della matrice TOP
            if (matrix[i*m_cols + j] == 0)
            {
                if (LEGAL_POS(m_rows,m_cols,(i-1)*m_cols + j))
                    TOP[j] = TOP[j] + 1;
                else
                    TOP[j] = 1;
            }
            else
            {
                TOP[j] = 0;
            }
            
            // Calcolo della maggiore area possibile
            if (j == 0)
            {
                stack_push(STACK_values,TOP[j]);
                stack_push(STACK_indexes,j);
                continue;
            }

            if (TOP[j] > TOP[j-1])
            {
                stack_push(STACK_values,TOP[j]);
                stack_push(STACK_indexes,j);
            }
            else if (TOP[j] < TOP[j-1])
            {
                int index = 0;
                int value = 0;
                while (!is_empty(STACK_indexes) && !is_empty(STACK_values) && TOP[j] < stack_head(STACK_values))
                {
                    stack_pop(STACK_indexes,&index);
                    stack_pop(STACK_values,&value);
                    area = value*(j-index);
                    if (area > max_area)
                        max_area = area;
                }
            }

        }

        //Stampo TOP ad ogni riga
        for (int i = 0; i < m_cols; i++)
        {
            printf("%d ",TOP[i]);
        }
        printf("\n");


        // Calcolo con eventuali residui nello stack
        int index = 0;
        int value = 0;
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
    stack_t *s = calloc(1,sizeof(stack_t)+dim);
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