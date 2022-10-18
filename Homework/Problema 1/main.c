#include "ll.c"
#include <stdio.h>

#define SIZE 128
#define LIST_SIZE 6

int main(void){

    char temp;

    LinkedList *list = createEmptyList();

    for (size_t i = 0; i < LIST_SIZE; i++)
    {
        char buf[SIZE];
        scanf("%[^\n]",buf);
        scanf("%c",&temp);
        add(list,createNode(buf));
    }
    
    printf("La lista e': ");
    printList(list);

    if (mirrorList(list,0) != -1){
        printf("La nuova lista e': ");
        printList(list);
    }
    else
    {
        printf("Errore\n");
    }
    

    
}