#include <stdio.h>
#include <assert.h>

int main(){

    FILE *f = fopen("test.txt","r");
    assert(f != NULL);
    int val;
    fscanf(f,"%d",&val);
    
    printf("%d\n",val);

    int car[10];

    for (size_t i = 0; i < 100; i++)
    {
        car[i] = getc(f);
        if (car[i] == EOF)
            break;
        
    }

    for (size_t i = 0; i < 5; i++)
    {
        printf("%d",car[i]);
    }
    
    
}