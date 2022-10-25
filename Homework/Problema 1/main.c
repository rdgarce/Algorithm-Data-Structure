#include "ll.c"
#include "names.c"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Number of tests to execute
#define NUM_TESTS 3

int main(void){

    srand(time(NULL));
    
    // Test generation
    LinkedList *tests[NUM_TESTS];
    int sizes[NUM_TESTS];

    for (int i = 0; i < NUM_TESTS; i++){
        
        tests[i] = createEmptyList();
        // Numero casuale pari
        int size = ((rand() % 4) + 1)*2;
        sizes[i] = size;

        for (int k = 0; k < size; k++)
            append(tests[i],createNode(get_name()));
        
    }
    // End test generation

    // Execute algorithm and print list before and after
    for (int i = 0; i < NUM_TESTS; i++){
        
        printf("Stampo la lista di input numero %d e sotto il relativo risultato dell'esecuzione:\n",i+1);
        printList(tests[i]);
        int exc = mirrorList(tests[i],sizes[i]/2);
        printList(tests[i]);
        printf("> Sono stati scambiati di posizione %d nome\\i\n",exc);
        printf("----------");
        printf("\n");
    }

    // Free memory
    for (int i = 0; i < NUM_TESTS; i++)
        deleteLL(tests[i]);
    
    
}