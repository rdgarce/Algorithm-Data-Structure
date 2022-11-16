#include "treaps.c"
#include <stdlib.h>

int main(){

    Treap *t = createTreap();

    printf("\n*** Stampa dell'albero vuoto ***\n\n");
    printTree(t);
    printf("\n**********\n");

    TreapInsert(t,createNode(500,2000));
    printf("\n*** Stampa dell'albero ***\n\n");
    printTree(t);
    printf("\n**********\n");

    TreapInsert(t,createNode(1000,4000));
    printf("\n*** Stampa dell'albero ***\n\n");
    printTree(t);
    printf("\n**********\n");

    TreapInsert(t,createNode(1100,3000));
    printf("\n*** Stampa dell'albero ***\n\n");
    printTree(t);
    printf("\n**********\n");

    TreapInsert(t,createNode(2000,1900));
    printf("\n*** Stampa dell'albero ***\n\n");
    printTree(t);
    printf("\n**********\n");

    TreapInsert(t,createNode(6000,2100));
    printf("\n*** Stampa dell'albero ***\n\n");
    printTree(t);
    printf("\n**********\n");

    TreapInsert(t,createNode(6000,2000));
    printf("\n*** Stampa dell'albero ***\n\n");
    printTree(t);
    printf("\n**********\n");

    TreapInsert(t,createNode(6000,1200));
    printf("\n*** Stampa dell'albero ***\n\n");
    printTree(t);
    printf("\n**********\n");

    TreapInsert(t,createNode(6008,1300));
    printf("\n*** Stampa dell'albero ***\n\n");
    printTree(t);
    printf("\n**********\n");

    TreapInsert(t,createNode(8000,1400));
    printf("\n*** Stampa dell'albero ***\n\n");
    printTree(t);
    printf("\n**********\n");

    deleteTreap(t);
    
}