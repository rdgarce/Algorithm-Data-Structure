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
        append(list,createNode(buf));
    }
    
    printf("La lista e': ");
    printList(list);

    int result = mirrorList(list,LIST_SIZE/2 +1);
    if (result != -1){
        printf("La nuova lista e': ");
        printList(list);
        printf("E si sono scambiati di posizione %d elementi\n",result);
        
    }
    else
    {
        printf("Errore\n");
    }
    

    
}