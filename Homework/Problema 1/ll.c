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

/*
* Mirror the sub-list of the [list] starting from the [n]-th element.
* If [n] equals 0, the result will be the whole [list] being mirrored.
* Returns -1 if the operation has errors of any kind or the number of the mirrored nodes.
*/
int mirrorList(LinkedList *list, int n){
    
    llNode *node = list->head;

    int i = 0;
    int count = 0;

    while (node && i<n-1){
        node = node->next;
        i++;
    }

    if (node == NULL && i<n){
        //Error: [n] > size of [list]
        return -1;
    }
        
    llNode *temp = node->next;

    if (temp == NULL){
    //Info: Just one element to mirror
        return 1;
    }
    
    llNode *temp1 = temp->next;
    llNode *temp2;

    while (temp1){
        temp2 = temp1->next;
        temp1->next = temp;
        temp = temp1;
        temp1 = temp2;
        count++;
    }

    if (n != 0){
        node->next->next = NULL;
        node->next = temp;
        return count + 1;
    }
    
    list->head=temp;
    node->next->next = node;
    node->next = NULL;
    return count + 1;
    

}