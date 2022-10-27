#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct tNode{
    int key;
    int priority;
    struct tNode *p;
    struct tNode *l;
    struct tNode *r;
}tNode;

typedef struct Treap{
    tNode *root;
    int n_nodes;
}Treap;


tNode *createNode(int key, int priority){
    tNode *node = malloc(sizeof(tNode));
    node->key = key;
    node->priority = priority;
    node->l = NULL;
    node->p = NULL;
    node->r = NULL;
    return node;
}

Treap *createTreap(){
    Treap *t = malloc(sizeof(Treap));
    t->root = NULL;
    t->n_nodes = 0;
    return t;
}

void printTree(Treap *tree){

    printf("%d ",tree->root->key);
    if (tree->root->l){
        Treap t = {.root = tree->root->l};
        printTree(&t);
    }
    if (tree->root->r){
        Treap t = {.root = tree->root->r};
        printTree(&t);
    }
    

}

void delete_sub_tree(tNode *node){

    if (node->l)
        delete_sub_tree(node->l);

    if (node->r)
        delete_sub_tree(node->r);

    free(node);

}

void deleteTreap(Treap *tree){

    delete_sub_tree(tree->root);

    free(tree);

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
    
    tree->n_nodes++;
    treap_fix(tree,node);
}

