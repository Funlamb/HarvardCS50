//Linking list practice

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(void) {
    //make a list with NULL ref to avoid the list pointing to a garbage value
    node *list = NULL;

    //malloc a chunk of mem the sive of a node
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return 1;
    }
    
    //Setup first node
    n->number = 1;
    n->next = NULL;
    list = n;

    //make another node
    n = malloc(sizeof(node));
    if (!n)
    {
        free(list);
        return 1;
    }
    n->number = 2;
    n->next = NULL;
    list->next = n;

    n = malloc(sizeof(node));
    if(!n)
    {
        free(list->next);
        free(list);
        return 1;
    }

    n->number = 5;
    n->next = NULL;
    list->next->next= n;
    
    for (node *temp = list; temp != NULL; temp = temp->next )
    {
        printf("%i\n", temp->number);
    }
    
    while(list != NULL){
        node *tmp = list->next;
        free(list);
        list = tmp;
    }
    printf("Made it.\n");
    return 0;
}