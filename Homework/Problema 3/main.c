#include "treaps.c"
#include <stdlib.h>

int main(){

    Treap *t = createTreap();

    printf("\n*** Stampa dell'albero vuoto ***\n\n");
    printTree(t);
    printf("\n**********\n");

    TreapInsert(t,createNode(9,5));
    printf("\n*** Stampa dell'albero ***\n\n");
    printTree(t);
    printf("\n**********\n");

    TreapInsert(t,createNode(18,2));
    printf("\n*** Stampa dell'albero ***\n\n");
    printTree(t);
    printf("\n**********\n");

    TreapInsert(t,createNode(2,9));
    printf("\n*** Stampa dell'albero ***\n\n");
    printTree(t);
    printf("\n**********\n");

    TreapInsert(t,createNode(7,1));
    printf("\n*** Stampa dell'albero ***\n\n");
    printTree(t);
    printf("\n**********\n");

    TreapInsert(t,createNode(3,10));
    printf("\n*** Stampa dell'albero ***\n\n");
    printTree(t);
    printf("\n**********\n");

    TreapInsert(t,createNode(0,3));
    printf("\n*** Stampa dell'albero ***\n\n");
    printTree(t);
    printf("\n**********\n");

    TreapInsert(t,createNode(23,3));
    printf("\n*** Stampa dell'albero ***\n\n");
    printTree(t);
    printf("\n**********\n");

    TreapInsert(t,createNode(38,3));
    printf("\n*** Stampa dell'albero ***\n\n");
    printTree(t);
    printf("\n**********\n");

    deleteTreap(t);
    
}