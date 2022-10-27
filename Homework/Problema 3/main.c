#include "treaps.c"

int main(){

    Treap *t = createTreap();

    TreapInsert(t,createNode(1,10));
    TreapInsert(t,createNode(5,10));
    TreapInsert(t,createNode(2,10));
    TreapInsert(t,createNode(9,10));
    TreapInsert(t,createNode(3,10));
    TreapInsert(t,createNode(0,10));


    printTree(t);
    deleteTreap(t);
}