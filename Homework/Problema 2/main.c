#include "utils.c"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Number of tests to execute defined here
#define NUM_TESTS 3

int main(){

    // Test genetarion
    int *tests[NUM_TESTS];
    int sizes[NUM_TESTS];

    srand(time(NULL));

    for (int i = 0; i < NUM_TESTS; i++){
        int size = (rand()%10) + 1;
        sizes[i] = size;
        tests[i] = malloc(sizeof(int)*size);

        for (int k = 0; k < size; k++)
            tests[i][k] = rand()%20;
        
    }
    // End of test generation

    int *results[NUM_TESTS];

    // Execute algorithm
    for (int i = 0; i < NUM_TESTS; i++)
        results[i] = algoritmo_v1(tests[i],sizes[i]);

    // Print of the input and results arrays
    for (int i = 0; i < NUM_TESTS; i++){

        printf("Stampo l'array di input numero %d e sotto il relativo risultato dell'esecuzione:\n",i+1);
        for (int k = 0; k < sizes[i]; k++)
            printf("%d ",tests[i][k]);
        printf("\n");
        for (int k = 0; k < sizes[i]; k++)
            printf("%d ",results[i][k]);
        printf("\n");
        printf("----------");
        printf("\n");

    }

    for (int i = 0; i < NUM_TESTS; i++){
        free(tests[i]);
        free(results[i]);
    }

}