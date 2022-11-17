#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 21
int main(){

    bool map[MAX_SIZE][MAX_SIZE];
    memset(map,false,sizeof(bool)*MAX_SIZE*MAX_SIZE);
    bool visited[MAX_SIZE];
    memset(visited,false,sizeof(bool)*MAX_SIZE);


}

void find_paths(bool *map, int map_size, int *partial_solution, int sol_size, bool *visited, int *number_of_sols){



}

void construct_candidates(bool *map, int map_size, int *partial_solution, int sol_size, bool *visited){

    int my_pos = partial_solution[sol_size-1];

    int navigator = (my_pos - 1) * map_size;
}