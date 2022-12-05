/*

Soluzione:
Nonostante la possibilità di applicare il backtracking, si presenta di seguito un algoritmo con complessità temporale lineare
per il ritrovamento di una sottomatrice di zeri da una matrice.

L'intuizione di base, al netto di tutte le seguenti ottimizzazioni sul consumo di tempo e di memoria, è la seguente:
Si costruisce una matrice ausiliaria delle stesse dimensioni di quella di partenza dove in ogni cella si inserisce l'area
del più grande vettore colonna che è possibile formare dove la cella in esame è l'ultimo elemento in basso.

ES:
Se la matrice binaria di partenza è:

1 0 1 0
1 1 0 0
0 0 1 1
0 0 1 1

Si costruirà una matrice ausiliaria così fatta:

0 1 0 1
0 0 1 2
1 1 0 0
2 2 0 0

Questa matrice ausiliaria ci da l'informazione di quali siano le più lunghe sequenze di zeri in verticale nella matrice.
Una volta costuita questa matrice, per ogni riga si esegue il seguente procedimento:
1) Si trova la coppia di indici (i,j) con i <= j che identificano il sottovettore del vettore [riga] in analisi
   che ha l'area massima. L'area massima è calcolata come: (j-i+1) * MIN(riga[i:j]).
2) La più grande area massima trovata tra tutte le righe corrisponde all'area della più grande sottomatrice di zeri

*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

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

int max_sub_matrix_size(bool *matrix, int m_rows, int m_cols);

#define LEGAL_POS(m_rows, m_cols, position) ((position) >= 0 && (position) < (m_rows)*(m_cols))

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

        printf("L'area della sottomatrice di zeri del #%d caso di test e': %d\n",i+1,max_sub_matrix_size(matrix,m_rows,m_cols));
        free(matrix);
    }
}

/*
* Data la matrice [matrix] di [m_rows] righe e [m_cols] colonne,
* ritorna l'area della massima sottomatrice di zeri presente nella
* matrice, oppure -1 in caso di errore
*/
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