#include "treaps.c"
#include <stdlib.h>

int main(){

    Treap *t = createTreap();

    TreapInsert(t,createNode(9,5));
    TreapInsert(t,createNode(18,2));
    TreapInsert(t,createNode(2,9));
    TreapInsert(t,createNode(7,1));
    TreapInsert(t,createNode(3,10));
    TreapInsert(t,createNode(0,3));
    TreapInsert(t,createNode(23,3));
    TreapInsert(t,createNode(38,3));

    printTree(t);
    deleteTreap(t);
    
}