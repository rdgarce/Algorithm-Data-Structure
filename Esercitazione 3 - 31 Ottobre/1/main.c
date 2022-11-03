#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define left(i) (2*i)
#define right(i) (2*i +1)


int where_is_the_ball(int D, int I);
int calculate_pos(int node, int num_nodes, int I);

int main(){

    int num_tests;
    scanf("%d",&num_tests);

    int *D = malloc(sizeof(int)*2*num_tests);
    int *I = &D[num_tests];

    for (size_t i = 0; i < num_tests; i++)
        scanf("%d %d",&D[i],&I[i]);
    
    for (size_t i = 0; i < num_tests; i++)
        printf("%d\n",where_is_the_ball(D[i],I[i]));

    free(D);
}

int where_is_the_ball(int D, int I){

    int num_nodes = (int)pow(2,D) - 1;
    return calculate_pos(1, num_nodes, I);

}

int calculate_pos(int node, int num_nodes, int I){

    if (left(node) > num_nodes || right(node) > num_nodes)
        return node;

    if (I % 2 == 0)
        return calculate_pos(right(node),num_nodes,ceil((float)I/(float)2));
    else
        return calculate_pos(left(node),num_nodes,ceil((float)I/(float)2));
    
}
