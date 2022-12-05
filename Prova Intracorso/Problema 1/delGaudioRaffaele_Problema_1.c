/*
* Analisi della compessita del Problema 1:
* La funzione prodotta, ovvero [count_occurences], segue un andamento temporale
* esprimibile secondo da seguente ricorrenza: T(n) = 2*T(n/2) + O(1).
* Segue che la complessità totale è O(n) in quanto corrisponde ad una visita 
* di tutti i nodi di un albero, ovvero l'equivalente di scorrere il vettore in input una volta.
*/

#include <stdio.h>
#include <stdlib.h>

int count_occurences(int *vector, int start_index, int end_index, int elem);

int main()
{
    int *vector;
    int n_tests;
    int n_to_find;
    int v_size;
    int res;

    scanf("%d",&n_tests);

    for (int i = 0; i < n_tests; i++)
    {
        scanf("%d",&n_to_find);
        scanf("%d",&v_size);

        vector = malloc(sizeof(int)*v_size);

        for (int i = 0; i < v_size; i++)
        {
            scanf("%d",&vector[i]);
        }

        res = count_occurences(vector,0,v_size-1,n_to_find);
        printf("%d\n",res);

        free(vector);
    }
}

int count_occurences(int *vector, int start_index, int end_index, int elem)
{
    // Caso base
    if (start_index == end_index)
        return vector[start_index] == elem ? 1 : 0;

    // Safe rispetto ad overflow per grandi size del vettore
    int center = start_index + (end_index-start_index) / 2;

    int c_1 = count_occurences(vector,start_index,center,elem);
    int c_2 = count_occurences(vector,center+1,end_index,elem);
    
    return c_1 + c_2;
}