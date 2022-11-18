#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Buon a parte qualche piccola miglioria di carattere costante sul tempo asintotico.

bool is_jolly(int *sequence, int s_size);

int main(){

    int a[] = {1, 4, 2, -1, 6};
    int res = is_jolly(a,5);

    printf("%d",res);

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