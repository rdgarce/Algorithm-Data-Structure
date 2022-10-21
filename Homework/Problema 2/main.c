#include "utils.c"
#include <stdlib.h>
#include <stdio.h>

int main(){

    int vet[] = {1,1, 2, 3, 4, 5, 6, 9, 10};
    
    merge_sort(vet,0,(sizeof(vet)/sizeof(vet[0]))-1, NULL);

    for (size_t i = 0; i < sizeof(vet)/sizeof(vet[0]); i++)
    {
        printf("%i ",vet[i]);
        
    }
    printf("\n");

    printf("%d\n",binary_search(vet,0,(sizeof(vet)/sizeof(vet[0]))-1,1));
    
}