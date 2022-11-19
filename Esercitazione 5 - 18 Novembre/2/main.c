#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Buon a parte qualche piccola miglioria di carattere costante sul tempo asintotico.

#define MAX_SIZE 3000
bool is_jolly(int *sequence, int s_size);

int main(){

    int array[MAX_SIZE];
    char t_buff;
    int a_size = 0;

    while ((t_buff = getc(stdin)) != EOF && t_buff != '\n')
    {
        ungetc(t_buff,stdin);
        scanf("%d",&a_size);
        for (int i = 0; i < a_size; i++)
        {
            scanf("%d",&array[i]);
        }
        is_jolly(array,a_size) ? printf("Jolly\n") : printf("Not jolly\n");
    }

}

bool is_jolly(int *sequence, int s_size){
    
    bool *diff_visited = malloc(sizeof(bool)*s_size-1);
    memset(diff_visited,false,sizeof(bool)*s_size-1);

    int count = 0;
    int pos;
    for (int i = 1; i < s_size; i++)
    {
        pos = abs(sequence[i]-sequence[i-1]);

        if (pos == 0 || pos > s_size-1 || diff_visited[pos] == true)
        {
            return false;
        }

        diff_visited[pos] == true;
        
    }
    
    return true;
    
}