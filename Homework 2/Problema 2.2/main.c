#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int number_of_couples(int n);

#define MAX_SAFE_VALUE 19

int main(){

    int n_tests;
    int num;

    printf("Inserire il numero di casi di test\n");
    scanf("%d",&n_tests);
    for (int i = 0; i < n_tests; i++)
    {
        printf("Inserire la cardinalita' dell'insieme del #%d caso di test\n",i+1);
        scanf("%d",&num);

        if (num <= MAX_SAFE_VALUE)
        {
            printf("Il risultato del #%d caso di test e': %d\n",i+1,number_of_couples(num));
        }
        else
        {
            printf("Il risultato del #%d caso di test non e' calcolabile poiche' la cardinalita' inserita è troppo grande\n",i+1);
        }
    }
}

/*
* Dato un gruppo di [n] elementi, con [n] >= 0,
* restituisce il numero totale di modi in cui 
* gli [n] elementi possono rimanere singoli o essere accoppiati
*/
int number_of_couples(int n)
{
    if (n <= 2)
        return n;
    
    int memo[2] = {1,2};
    int result;

    for (int i = 3; i <= n; i++)
    {
        result  = memo[1] + (i-1)*memo[0];
        memo[0] = memo[1];
        memo[1] = result;
    }

    return result;
}