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
void addToTree(node *tree, int key);

int main(void) {
    //add to tree
    node *list = 0;

    // node *n = malloc(sizeof(node));
    // if(!n){
    //     return 1;
    // }
    // n->number = 10;
    // n->left = 0;
    // n->right = 0;
    int n = 10;
    addToTree(list, n);
    // list = n;

    // n = malloc(sizeof(node));
    // if(!n){
    //     return 1;
    // }
    // n->number = 15;
    // n->left = 0;
    // n->right = 0;
    n = 15;
    addToTree(list, n);

    // n = malloc(sizeof(node));
    // if (!n)
    // {
    //     return 1;
    // }
    // n->number = 5;
    // n->left = 0;
    // n->right = 0;
    n = 5;
    addToTree(list, n);

    // n = malloc(sizeof(node));
    // if (!n)
    // {
    //     return 1;
    // }
    // n->number = 7;
    // n->left = 0;
    // n->right = 0;
    n = 7;
    addToTree(list, n);

    // n = malloc(sizeof(node));
    // if (!n)
    // {
    //     return 1;
    // }
    // n->number = 9;
    // n->left = 0;
    // n->right = 0;
    n = 9;
    addToTree(list, n);
    
    // n = malloc(sizeof(node));
    // if (!n)
    // {
    //     return 1;
    // }
    // n->number = 45;
    // n->left = 0;
    // n->right = 0;
    n = 45;
    addToTree(list, n);
    
    // n = malloc(sizeof(node));
    // if (!n)
    // {
    //     return 1;
    // }
    // n->number = 35;
    // n->left = 0;
    // n->right = 0;
    n = 35;
    addToTree(list, n);
        
    // n = malloc(sizeof(node));
    // if (!n)
    // {
    //     return 1;
    // }
    // n->number = 12;
    // n->left = 0;
    // n->right = 0;
    n = 12;
    addToTree(list, n);

    //search tree
    printf("%i\n", search(list, 11));
    printf("%i\n", search(list, 15));
    printf("%i\n", search(list, 5));

    //Free the whole tree
    freeTree(list);
    return 0;
}

void addToTree(node *tree, int key){
    // if (tree && n)
    // {
        // add to the tree
        //Start from the top
        printf("Add to tree\n");
        if(tree == 0){
            printf("Zero\n");
            tree = malloc(sizeof(node));
            tree->number = key;
            tree->left = 0;
            tree->right = 0;
        }

        //check if the number is smaller or bigger
        //if bigger add to the right
        else if (tree->number < key)//If the tree's number is smaller than the number add the number to the right of the tree
        {
            printf("Right\n");
            addToTree(tree->right, key);
        } 
        //if smaller add to the left
        else
        {
            printf("Left\n");
            addToTree(tree->left, key);
        }
    // }
}

int search(node *tree, int number){
    printf("%i, %i\n" , number, tree->number);
    if(!tree){
        printf("Here");
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
    printf("\n");
    printf("Free Tree\n");//Start here #1
    printf("%i\n", tree->number); //#2
    if(!tree){//The tree is not null so continue
        return;
    }
    if(tree->left)
    {
        // printf("Going Left\n");// why does it go here at the end? #4
        freeTree(tree->left);
        free(tree->left);
    } 
    if (tree->right)
    {
        // printf("Going right\n");
        freeTree(tree->right);
        free(tree->right);
    } 
    // else if (tree->right == NULL && tree->left == NULL)//Check if bottom of the tree
    {
        printf("Freed: %i\n", tree->number);// #3
        // tree = NULL;
        free(tree);
    }
}
