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

void printNode(tNode *node){

    if (node)
        printf("(%d,%d) ", node->key, node->priority);
    
}

void printTree(Treap *tree){

    int depth = 1;
    tNode *node = tree->root;
    tNode **A = malloc(sizeof(tNode)*depth);
    tNode **B;
    int A_size = 0;
    int B_size = 0;
    int B_index = 0;

    A[0] = node;
    A_size++;

    while (node && A_size != 0){

        B = malloc(sizeof(tNode)*2*depth);

        for (int i = 0; i < A_size; i++){
            if (A[i])
                //printf("%d ",A[i]->key);
                printNode(A[i]);
            else
                printf("- ");
            if (i%2 == 1 && i+1<A_size)
                printf("| ");            
            
            if (A[i] && A[i]->l){
                B[B_index] = A[i]->l;
                B_index++;
                B_size = B_index;
            }
            else{
                B[B_index] = NULL;
                B_index++;
            }

            if (A[i] && A[i]->r){
                B[B_index] = A[i]->r;
                B_index++;
                B_size = B_index;
            }
            else{
                B[B_index] = NULL;
                B_index++;
            }

        }
        printf("\n");

        free(A);
        A = B;
        A_size = B_size;
        B_size = 0;
        B_index = 0;
        depth++;

    }
    
    free(B);

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

void left_rotate(Treap *tree, tNode *node){

    //assert node.p.r != NULL
    tNode *right_son = node->r;
    right_son->p = node->p;
    
    if (tree->root == node)
        tree->root = right_son;
    else if (node == node->p->r)
        node->p->r = right_son;
    else
        node->p->l = right_son;
    
    node->r = right_son->l;
    if (right_son->l)
        right_son->l->p = node;

    right_son->l = node;
    node->p = right_son;

}

void right_rotate(Treap *tree, tNode *node){

    //assert node.p.l != NULL
    tNode *left_son = node->l;
    left_son->p = node->p;
    
    if (tree->root == node)
        tree->root = left_son;
    else if (node == node->p->r)
        node->p->r = left_son;
    else
        node->p->l = left_son;
    
    node->l = left_son->r;
    if (left_son->r)
        left_son->r->p = node;

    left_son->r = node;
    node->p = left_son;

}

void treap_fix(Treap *tree, tNode *node){

    while (node != tree->root && node->priority < node->p->priority){

        if (node == node->p->r)
            left_rotate(tree,node->p);
        else
            right_rotate(tree,node->r);
    }
    

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

