#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct llNode
{
    struct llNode *next;
    char elem[];
}llNode;

typedef struct LinkedList{
    llNode *head;
}LinkedList;

LinkedList *createEmptyList(){
    LinkedList *list = malloc(sizeof(LinkedList));
    list->head = NULL;
    return list;
}

llNode *createNode(char *elem){
        
        llNode *node = malloc(sizeof(llNode) + sizeof(char) * strlen(elem));
        strcpy(node->elem,elem);
        node->next = NULL;
        return node;
    }

void printList(LinkedList *list){
    
    llNode *head = list->head;
    while (head){
        printf("%s | ",head->elem);
        head = head->next;
    }
    printf("\n");
    
}

void add(LinkedList *list, llNode *node){
    /*
    * Add a new [node] element at the start of the [list]
    */
    node->next = list->head;
    list->head = node;

}

int mirrorList(LinkedList *list, int n){
    /*
    * Mirror the sub-list of the [list] starting from the ([n]+1)-th element.
    * If [n] equals 0, the result will be the whole [list] being mirrored.
    * [n] must be less or equals to the lenght of the list - 2.
    * Returns -1 if the operation has errors of any kind or the number of the mirrored nodes.
    */
    llNode *node = list->head;
    size_t i = 0;
    size_t count = 0;

    while (node && i<n){
        node = node->next;
        i++;
    }

    if (node == NULL && i<n-1)
    //Error: [n] > size of [list]
        return -1;
    

    llNode *temp = node->next;

    if (temp == NULL)
        //Error: No node to mirror
        return -1;
    
    llNode *temp1 = temp->next;

    if (temp1 == NULL)
        //Info: Mirroring just the last node
        return 0;

    llNode *temp2;

    while (temp1){
        temp2 = temp1->next;
        temp1->next = temp;
        temp = temp1;
        temp1 = temp2;
        count++;
    }

    node->next->next = NULL;
    node->next = temp;

    return count;

}