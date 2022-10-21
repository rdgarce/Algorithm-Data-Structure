#include "utils.c"
#include <stdlib.h>
#include <stdio.h>

int main(){

    int vet[] = {5,5,5,5,5,5,5,5};
    
    int *b = algoritmo_v1(vet, sizeof(vet)/sizeof(vet[0]));

    for (size_t i = 0; i < sizeof(vet)/sizeof(vet[0]); i++)
    {
        printf("%d ", b[i]);
    }
    printf("\n");
    
    
}