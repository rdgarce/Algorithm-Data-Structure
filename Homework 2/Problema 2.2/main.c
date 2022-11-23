/*

Soluzione:
La formula della ricorrenza può essere inferita guardando all'evoluzione dell'output tra (n-1) ed (n).
L'aggiunta dello (n)-esimo elemento produce:
1) Gli stessi sottoinsiemi che si avevano per (n-1) con l'aggiunta dello (n)-esimo elemento non accoppiato con nessuno
   dei precedenti.
2) Altri sottoinsiemi derivanti dagli (n-1) modi di accoppiare il nuovo elemento con i precedenti moltiplicato per il numero
   di sottinsiemi generati dalle combinazioni dei rimanenti (n-2) elementi.

Formalmente, la ricorrenza si esprime come:
R(n) = R(n-1) + (n-1)*R(n-2)

Casi base:
R(1) = 1
R(2) = 2

Il problema viene risolto con la DP utilizzando un approccio iterativo che consente di avere una complessità spaziale costante.
NOTA BENE: Data la rappresentazione in interi su 4 byte, input maggiori di MAX_SAFE_VALUE generano valori errati a causa overflow.

*/

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