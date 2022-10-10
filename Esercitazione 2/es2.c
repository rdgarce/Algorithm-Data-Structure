#include <stdio.h>
#include <stdlib.h>

#define c2i(char) char - '0'

void algoritmo(int row, int **A);
int tartaglia(int row, int pos);
void print_array(int *A, int len);

int main(){

    int riga;
    int *A;

    scanf("%d",&riga);

    while (riga != 0)
    {
        algoritmo(riga,&A);
        print_array(A,riga);
        free(A);
        scanf("%d",&riga);

    }
    

    

}

void algoritmo(int row, int **A){
    /*         P
              A A
             Z K Z
            X Y Y X
           Q W R W Q
    */ 

    //A e len sono l'array di output e la lunghezza restituita dell'array

    int *array = malloc(sizeof(int) * row);

    if (row % 2 == 0){
        
        for (unsigned int i = 0; i < row/2; i++){
            array[i] = tartaglia(row, i);
        }
            
        for (size_t i = row/2; i < row; i++){
            array[i] = array[row - i - 1];
        }

    }
    else
    {   
        // X Y Z Y X
        for (unsigned int i = 0; i <= row/2; i++){
            array[i] = tartaglia(row, i);
        }
            

        for (size_t i = row/2 + 1; i < row; i++){
            array[i] = array[row - i - 1];
        }
            
    }

    *A = array;

}

int tartaglia(int row, int pos){

    if (row == 1 || row == 2 || pos == 0 || pos == row - 1)
        return 1;
    else
        return tartaglia(row - 1, pos -1) + tartaglia(row - 1, pos);
    
    
}

void print_array(int *A, int len){
    printf("[");
    for(int i=0;i<len;i++)
        printf("%d ", A[i]);
    printf("]");
}