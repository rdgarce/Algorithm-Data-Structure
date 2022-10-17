#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct llNode
{
    struct llNode *next;
    char elem[];
}llNode;

typedef llNode *llHead;

llNode *createNode(char *elem){
        
        llNode *node = malloc(sizeof(llNode) + sizeof(char) + strlen(elem));
        //memcpy(node->elem,elem,elem_size);
        strcpy(node->elem,elem);
        node->next = NULL;
        return node;
    }

void printList(llHead head){
    
    while (head){
        printf("%s ",head->elem);
        head = head->next;
    }
    printf("\n");
    
}