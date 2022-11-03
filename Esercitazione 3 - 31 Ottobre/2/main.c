#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "ll.c"

int main(){

    LinkedList *results = createEmptyList();

    int num_marbles, num_queries;
    
    while (1){

        scanf("%d %d",&num_marbles,&num_queries);
        if (num_marbles == 0 && num_queries == 0)
            break;
        
        int marbles[10000] = {0};
        int marbles_int[10000];
        int *queries = malloc(sizeof(int)*num_queries);
        int *queries_results = malloc(sizeof(int)*num_queries);
        
        int marble;
        int max_marble = INT_MIN;
        
        // Lettura delle biglie
        for (int i = 0; i < num_marbles; i++){
            scanf("%d",&marble);
            if (marble >= max_marble)
                max_marble = marble;
            marbles[marble]++;
        }        

        // Lettura delle query
        for (int i = 0; i < num_queries; i++)
            scanf("%d",&queries[i]);
        
        // Calcolo del vettore "integrale"
        marbles_int[0] = marbles[0];
        for (int i = 1; i <= max_marble; i++)
            marbles_int[i] = marbles[i] + marbles_int[i-1];
        
        //Esecuzione delle query
        for (int i = 0; i < num_queries; i++)
            queries_results[i] = marbles[queries[i]] != 0 ? marbles_int[queries[i]-1] + 1 : -1;
        
        llNode *node = createNode(num_queries,queries,queries_results);
        append(results,node);

    }

    //Stampa dei risultati
    int i=1;
    llNode *x = results->head;
    while (x){

        printf("CASE# %d:\n",i);

        for (int j = 0; j < x->num_queries; j++){
            if (x->queries_results[j] != -1)
                printf("%d found at %d\n",x->queries[j],x->queries_results[j]);
            else
                printf("%d not found\n",x->queries[j]);
            
        }

        x=x->next;
        i++;
    }

    deleteLL(results);
    
}