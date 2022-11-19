#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../Prova Intracorso/utils.c"

#define MAX_SIZE 100000

int main(){

    int input[MAX_SIZE];
    int n_exchanges = 0;
    int input_size;

    while (1)
    {
        scanf("%d",&input_size);
        if (input_size == 0)
        {
            break;
        }
        for (int i = 0; i < input_size; i++)
        {
            scanf("%d",&input[i]);
        }

        mergeSort(input,0,input_size-1,&n_exchanges);
        (n_exchanges % 2) == 0 ? printf("Carlos\n") : printf("Marcelo\n");

    }
    
}
