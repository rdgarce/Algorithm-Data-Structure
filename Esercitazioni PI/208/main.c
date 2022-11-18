#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void find_paths(bool *map, int map_size, int *partial_solution, int sol_size, int dest_crn, bool *visited, int *number_of_sols);
void construct_candidates(bool *map, int map_size, int *partial_solution, int sol_size, bool *visited, int *array_of_candidates, int *n_candidates);

void print_array(int *next_corners,int n_next_corners);

#define MAX_SIZE 21
int main(){

    bool map[MAX_SIZE][MAX_SIZE];
    memset(map,false,sizeof(bool)*MAX_SIZE*MAX_SIZE);
    bool visited[MAX_SIZE];
    memset(visited,false,sizeof(bool)*MAX_SIZE);

    char buffer[6];

    int temp_obj_crn, temp_crn1, temp_crn2;
    int partial_solution[MAX_SIZE];
    int n_solutions = 0;

    int case_num = 1;
    while ((fgets(buffer,sizeof(buffer),stdin) != NULL) && buffer[0] != '\n')
    {
        sscanf(buffer,"%d",&temp_obj_crn);
        while ((fgets(buffer,sizeof(buffer),stdin) != NULL))
        {
            sscanf(buffer,"%d %d",&temp_crn1,&temp_crn2);
            if (temp_crn1 == 0 && temp_crn2 == 0)
            {
                break;
            }
            map[temp_crn1-1][temp_crn2-1] = true;
            map[temp_crn2-1][temp_crn1-1] = true;

        }
        partial_solution[0] = 1;
        printf("CASE %d:\n",case_num);
        find_paths(map,MAX_SIZE,partial_solution,1,temp_obj_crn,visited,&n_solutions);
        printf("There are %d routes from the firestation to streetcorner %d.\n",n_solutions,temp_obj_crn);
        case_num++;
        memset(map,false,sizeof(bool)*MAX_SIZE*MAX_SIZE);
        memset(visited,false,sizeof(bool)*MAX_SIZE);
        n_solutions = 0;
    }
    

}

void find_paths(bool *map, int map_size, int *partial_solution, int sol_size, int dest_crn, bool *visited, int *number_of_sols){

    visited[partial_solution[sol_size-1]-1] = true;

    if (partial_solution[sol_size-1] == dest_crn)
    {
        (*number_of_sols)++;
        print_array(partial_solution,sol_size);
        visited[partial_solution[sol_size-1]-1] = false;
        return;
    }

    int *next_corners = malloc(sizeof(int)*map_size);
    if (!next_corners)
    {
        exit(-1);
    }
    int n_next_corners = 0;
    construct_candidates(map,map_size,partial_solution,sol_size,visited,next_corners,&n_next_corners);     
    
       
    
    for (int i = 0; i < n_next_corners; i++)
    {
        partial_solution[sol_size] = next_corners[i];
        find_paths(map,map_size,partial_solution,sol_size+1,dest_crn,visited,number_of_sols);
    }
    
    visited[partial_solution[sol_size-1]-1] = false;
    free(next_corners);

}

void construct_candidates(bool *map, int map_size, int *partial_solution, int sol_size, bool *visited, int *array_of_candidates, int *n_candidates){

    int my_pos = (partial_solution[sol_size-1] - 1) * map_size;
    int count = 0;

    for (int i = my_pos+1; i < my_pos+map_size; i++)
    {   
        if (map[i] == false || visited[i%map_size] == true)
        {
            continue;
        }

        array_of_candidates[count] = (i+1)%map_size;
        count++;
    }

    *n_candidates = count;
}

void print_array(int *next_corners,int n_next_corners){
    for (int i = 0; i < n_next_corners; i++)
    {
        printf("%d ",next_corners[i]);
    }
    printf("\n");
    
}