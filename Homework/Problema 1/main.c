#include "ll.c"
#include <stdio.h>

int main(void){

    llHead head = NULL;

    llHead temp = head;

    for (size_t i = 0; i < 10; i++)
    {   

        if (!head)
        {   
            head = createNode("ciao");
            temp = head;
        }
        else
        {
            temp->next = createNode("ciao");
            temp = temp->next;
        }
        


    }

    printList(head);


}