#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <assert.h>
#include "ll.c"

#define MAX_PANCAKES 30

void print_array(int *A, int len);
void flip(int *pancake_vector, int p_vector_size, int flip_index);
int pancake_flips(int *pancakes_vector, int p_vector_size, int *solution_vector);
int find_index_max(int *A, int start, int end);

int main(){

    FILE *f = fopen("test.txt","r");
    assert(f != NULL);

    int c;
    int index = 0;
    int pancakes[MAX_PANCAKES] = {0};
    int solution[2*MAX_PANCAKES] = {0};
    int solution_size;
    while (c = getc(f)){
        
        if (c == '\n'){

            solution_size = pancake_flips(pancakes,index,solution);
            print_array(solution,solution_size);
            printf("\n");
            index = 0;
            solution_size = 0;
        }
        else if (c == EOF && index != 0)
        {

            solution_size = pancake_flips(pancakes,index,solution);
            print_array(solution,solution_size);
            printf("\n");
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

/*
* Returns the index of the max elem of [A] from the [start] to the [end] index included
*/
int find_index_max(int *A, int start, int end){
    
    int index_max = start;

    for (int i = start+1; i <= end; i++)
        if (A[i]> A[index_max])
            index_max = i;
    
    return index_max;
    
}

void flip(int *pancake_vector, int p_vector_size, int flip_index){

    if (flip_index == 0)
        return;

    int adj_flip_index = p_vector_size - flip_index;
    
    if (adj_flip_index % 2 == 0)
        adj_flip_index = adj_flip_index/2;
    else
        adj_flip_index = adj_flip_index/2 + 1;
    
    int temp;
    for (int i = 0; i <= adj_flip_index; i++){

        temp = pancake_vector[i];
        pancake_vector[i] = pancake_vector[adj_flip_index-i];
        pancake_vector[adj_flip_index-i] = temp;
    }
    
}

int pancake_flips(int *pancakes_vector, int p_vector_size, int *solution_vector){
    
    int s_vector_size = 0;
    int max_pos;

    for (int i = 0; i < p_vector_size; i++){

        max_pos = find_index_max(pancakes_vector,0,p_vector_size-i);
        if (max_pos != p_vector_size-i-1){

            //Qui effettuo i flip
            flip(pancakes_vector,p_vector_size,max_pos+1);
            solution_vector[s_vector_size] = max_pos+1;
            s_vector_size++;
            flip(pancakes_vector,p_vector_size,1);
            solution_vector[s_vector_size] = 1;
            s_vector_size++;
        }
        
    }

    return s_vector_size;
    
}

void print_array(int *A, int len){
    printf("[");
    for(int i=0;i<len;i++)
        printf("%d ", A[i]);
    printf("]");
}