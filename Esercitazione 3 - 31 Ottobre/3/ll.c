#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct llNode
{
    struct llNode *next;
    int *solution;
}llNode;

typedef struct LinkedList{
    llNode *head;
}LinkedList;

LinkedList *createEmptyList(){
    LinkedList *list = malloc(sizeof(LinkedList));
    list->head = NULL;
    return list;
}

void deleteLL(LinkedList *list){

    llNode *head = list->head;
    llNode *temp;
    while (head){

        temp = head;
        head = head->next;
        free(temp->solution);
        free(temp);
    }

    free(list);
    
}

llNode *createNode(int *solution){
        
        llNode *node = malloc(sizeof(llNode));
        node->next = NULL;
        node->solution = solution;
        return node;
    }

/*
* Add a new [node] element at the start of the [list]
*/
void add(LinkedList *list, llNode *node){
    node->next = list->head;
    list->head = node;

}

/*
* Append a new [node] element at the end of the [list]
*/
void append(LinkedList *list, llNode *node){
    
    llNode *my_node = list->head;

    if (my_node == NULL){
        add(list,node);
        return;
    }

    while (my_node->next)
        my_node = my_node->next;
    
    my_node->next = node;   

}