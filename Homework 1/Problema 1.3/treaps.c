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

/*
* Node creation function.
* The priority has to be chosen by the caller
*/
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

void print_node(tNode *node){

    if (node)
        printf("(%d,%d) ", node->key, node->priority);
    
}

/*
* Print the [tree] nodes in the following form:
* (key,priority) or - if there is no node in that position.
*/
void printTree(Treap *tree){

    if (tree->root == NULL){
        printf("-\n");
        return;
    }

    int depth = 1;
    tNode *node = tree->root;
    tNode **A = malloc(sizeof(tNode)*depth);
    tNode **B = NULL;
    int A_size = 0;
    int B_size = 0;
    int B_index = 0;

    A[0] = node;
    A_size++;

    while (node && A_size != 0){

        B = malloc(sizeof(tNode)*2*depth);

        for (int i = 0; i < A_size; i++){
            if (A[i])
                print_node(A[i]);
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
    
    if (B)
        free(B);

    

}

void delete_sub_tree(tNode *node){

    if (node->l)
        delete_sub_tree(node->l);

    if (node->r)
        delete_sub_tree(node->r);

    free(node);

}

/*
* Deletes the [tree] and frees the memory
*/
void deleteTreap(Treap *tree){

    delete_sub_tree(tree->root);
    free(tree);

}

/*
* Applies a left rotation to the [node] of the [tree].
*/
void left_rotate(Treap *tree, tNode *node){

    //assert node.r != NULL
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

/*
* Applies a right rotation to the [node] of the [tree].
*/
void right_rotate(Treap *tree, tNode *node){

    //assert node.l != NULL
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

/*
* Restores the Treap properties of the [tree] all the way up
* starting from the [node]
*/
void treap_fix(Treap *tree, tNode *node){

    while (node != tree->root && node->priority < node->p->priority){

        if (node == node->p->r)
            left_rotate(tree,node->p);
        else
            right_rotate(tree,node->p);
    }
    
}

/*
* Insert the [node] in the [tree] and then rearrange the nodes
* in order to respect the Treap properties
*/
void TreapInsert(Treap *tree, tNode *node){

    tNode *x = tree->root;
    tNode *y = NULL;

    // Iteration to a leaf of the tree => O(logn) since this is a Treap
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

    // Treap fix procedure => O(logn) in the worst case when the node goes up to the root
    treap_fix(tree,node);

    // Total cost T(n) = O(2logn) = O(logn)

}