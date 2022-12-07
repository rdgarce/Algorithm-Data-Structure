/*

Soluzione:
Il problema viene risolto mediante la programmazione dinamica.

Di seguito i 5 step dell'analisi che è stata fatta:
1) Il sottoproblema è quello di trovare la più lunga sottosequenza
   palindroma nella sottostringa [i:j]
   1.1) Il numero dei sottoproblemi è N^2 dove N è la lunghezza della stringa
2) Se stringa[i] == stringa[j] non ci sono scelte da fare, altrimenti si sceglie
   il massimo risultato ottenuto tra il sottoproblema DP(i+1,j) e DP(i,j-1)
   2.1) Il numero di scelte è <= 2, quindi il tempo per sottoproblema è O(1)
3) La ricorrenza è la seguente:
   DP(i,j) = {
                2 + DP(i+1,j-1), se stringa[i] == stringa[j]
                max{DP(i+1,j), DP(i,j-1)}, se stringa[i] != stringa[j]
             }
   Caso base: DP(k,k) = 1
4) Il grafo dei sottoproblemi è aciclico e il tempo totale di eseguzione è O(1)*N^2 = O(N^2)
5) Il problema originario viene risolto con DP(0,N-1)

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX(one, two) ((one) >= (two) ? (one) : (two))

int max_pal_sub_seq(char *string);

int main()
{
    char buf[128];
    int n_tests;
    
    printf("Inserire il numero di casi di test\n");
    scanf("%d",&n_tests);
    for (int i = 0; i < n_tests; i++)
    {
        printf("Inserire la stringa del #%d caso di test\n", i+1);
        scanf("%s",buf);
        printf("La lunghezza della massima sottosequenza palindroma del #%d caso di test e': %d\n",i+1,max_pal_sub_seq(buf));
    }
}

/*
* Data la stringa [string], ritorna la lunghezza della più lunga
* sottosequenza palindroma oppure -1 se si è verificato un errore
*/
int max_pal_sub_seq(char *string)
{
    size_t s_size = strlen(string);
    int (*memo)[s_size] = calloc(1,sizeof(int)*s_size*s_size);
    if (!memo)
        return -1;
    
    // Scrittura in memo dei casi base sulla diagonale
    for (int i = 0; i < s_size; i++)
        memo[i][i] = 1;

    for (int j = 1; j < s_size; j++)
    {
        for (int i = j-1; i >= 0; i--)
        {
            if (string[i] != string[j])
            {
                memo[i][j] = MAX(memo[i+1][j],memo[i][j-1]);
            }
            else if (string[i] == string[j] && j-i >= 2)
            {
                memo[i][j] = 2 + memo[i+1][j-1];
            }
            else
            {
                memo[i][j] = 2;
            }
        }
    }

    int res = memo[0][s_size-1];
    free(memo);
    return res;
}