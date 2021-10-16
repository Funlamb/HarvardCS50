#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *left;
    struct node *right;    
}
node;
int search(node *tree, int number);
void freeTree(node *tree);
void addToTree(node *tree, node *n);

int main(void) {
    //add to tree
    node *list = NULL;

    node *n = malloc(sizeof(node));
    if(!n){
        return 1;
    }
    n->number = 10;
    n->left = NULL;
    n->right = NULL;
    list = n;

    n = malloc(sizeof(node));
    if(!n){
        return 1;
    }
    n->number = 15;
    n->left = NULL;
    n->right = NULL;
    addToTree(list, n);

    n = malloc(sizeof(node));
    if (!n)
    {
        return 1;
    }
    n->number = 5;
    n->left = NULL;
    n->right = NULL;
    addToTree(list, n);
    
    //search tree
    printf("%i\n", search(list, 11));
    printf("%i\n", search(list, 15));
    printf("%i\n", search(list, 5));

    //Free the whole tree
    freeTree(list);
    return 0;
}

void addToTree(node *tree, node *n){
    if (tree && n)
    {
        if (tree->number < n->number)
        {
            tree->right = n;
        } else
        {
            tree->left = n;
        }
    }
}

int search(node *tree, int number){
    if(!tree){
        return 0;
    } 
    else if (number > tree->number)
    {

        return search(tree->right, number);
    } else if (number < tree->number)
    {
        return search(tree->left, number);
    } 
    else
    {
        return 1;
    }
}

void freeTree(node *tree){
    printf("\n\n");
    printf("Free Tree\n");//Start here #1
    printf("%i\n", tree->number); //#2
    if(!tree){//The tree is not null so continue
        return;
    }
    while (tree)
    {
        if(tree->left){
            printf("Going Left\n");// why does it go here at the end? #4
            freeTree(tree->left);
        } else if (tree->right)
        {
            printf("Going right\n");
            freeTree(tree->right);
        } else if (tree->right == NULL && tree->left == NULL)//Check if bottom of the tree
        {
            printf("Freed: %i\n", tree->number);// #3
            tree = NULL;
            free(tree);
        }
        
    }
    
}
