#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <assert.h>
#include "ll.c"

#define c2i(c) (c - '0')

int *pancake_flips(int *A, int size);

int main(){

    LinkedList *results = createEmptyList();

    FILE *f = fopen("test.txt","r");
    assert(f != NULL);

    int c;
    int index = 0;
    int pancakes[30] = {0};
    while (c = getc(f)){
        
        if (c == '\n'){

            int *solution = pancake_flips(pancakes,index);
            llNode *result = createNode(solution);
            append(results,result);
            index = 0;
        }
        else if (c == EOF && index != 0)
        {
            int *solution = pancake_flips(pancakes,index);
            llNode *result = createNode(solution);
            append(results,result);
            break;
        }
        
        
        while (c == ' ')
            c = getc(f);
        
        ungetc(c,f);

        fscanf(f,"%d",&c);

        pancakes[index] = c;
        index++;

    }
    
}

int *pancake_flips(int *A, int size){
    //test: stampo l'array
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ",A[i]);
    }
    printf("\n");
    
    return NULL;
}