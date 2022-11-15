#include <stdlib.h>
#include <stdio.h>

int main(){

    int edges[] = {2,0,0,2};
    int result = edgeScore(edges,4);
    printf("%d",result);
}
int edgeScore(int* edges, int edgesSize){
    
    int *sup_vec = malloc(sizeof(int)*edgesSize);
    for (int i = 0; i< edgesSize; i++)
    {
        sup_vec[i] = 0;
    }
    
    for (int i = 0; i< edgesSize; i++)
    {
        sup_vec[edges[i]] += i;
    }   

    int max = -1;
    int arg_max = -1;
    for (int i=0; i< edgesSize; i++)
    {
        if (sup_vec[i]>max)
        {
            max = sup_vec[i];
            arg_max = i;
        }
        
    }
    return arg_max;
}