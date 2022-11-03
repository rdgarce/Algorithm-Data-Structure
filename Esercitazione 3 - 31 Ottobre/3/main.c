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
    while ((c = getc(f)) != EOF){
        
        if (c == '\n'){
            int *solution = pancake_flips(pancakes,index+1);
            llNode *result = createNode(solution);
            append(results,result);
            index = 0;
        }
        
        while (c == ' ')
            c = getc(f);
        
        int sum = 0;
        while (c <= '9' && c >= '0'){
            sum = sum + c2i(c);
            c = getc(f);
        }

        pancakes[index] = sum;
        index++;

    }
    
}