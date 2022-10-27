#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct tNode{
    int key;
    int priority;
    struct tNode *p;
    struct tNode *l;
    struct tNode *r;
    char elem[];
}tNode;

typedef struct Treap{
    tNode *root;
    int n_elem;
}Treap;


tNode *createNode(int key, int priority, char *elem){
    tNode *node = malloc(sizeof(tNode) + sizeof(char)*(strlen(elem) + 1));
    node->key = key;
    node->priority = priority;
    node->l = NULL;
    node->p = NULL;
    node->r = NULL;
    strcpy(node->elem,elem);
    return node;
}

Treap *createTreap(){
    Treap *t = malloc(sizeof(Treap));
    t->root = NULL;
    t->n_elem = 0;
    return t;
}

void printTree(Treap *tree){

    printf("%s ",tree->root->elem);
    if (tree->root->l){
        Treap t = {.root = tree->root->l};
        printTree(&t);
    }
    if (tree->root->r){
        Treap t = {.root = tree->root->r};
        printTree(&t);
    }
    

}

void deleteTreap(Treap *tree){

    tNode *x = tree->root;

    if (x->l){
        Treap t = {.root = x->l};
        deleteTreap(&t);

    }
    if (x->r){
        Treap t = {.root = x->r};
        deleteTreap(&t);
    }

    free(x);
    free(tree);
    tree = NULL;

}
void treap_fix(Treap *tree, tNode *node){

}

void TreapInsert(Treap *tree, tNode *node){

    tNode *x = tree->root;
    tNode *y = NULL;

    while (x){
        y = x;
        if (x->key <= node->key)
            x = x->r;
        else
            x = x->l;
    }

    node->p = y;

    if (y == NULL)
        tree->root = node;
    else
        if (y->key <= node->key)
            y->r = node;
        else
            y->l = node;
    
    tree->n_elem++;
    treap_fix(tree,node);
}

