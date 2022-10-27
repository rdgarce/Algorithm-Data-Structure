#include "treaps.c"

int main(){

    Treap *t = createTreap();

    TreapInsert(t,createNode(1,10,"ciao"));


    printTree(t);
    deleteTreap(t);
}