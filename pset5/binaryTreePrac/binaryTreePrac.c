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
void addToTree(node *root, node *key);
node initNode(int value);

int main(void) {
    //add to tree
    node *list = malloc(sizeof(node));
    list->number = 10;
    list->left = NULL;
    list->right = NULL;

    node *n = malloc(sizeof(node));
    n->number = 15;
    n->left = NULL;
    n->right = NULL;
    addToTree(list, n);

    n = malloc(sizeof(node));
    n->number = 5;
    n->left = NULL;
    n->right = NULL;
    addToTree(list, n);
    
    n = malloc(sizeof(node));
    n->number = 6;
    n->left = NULL;
    n->right = NULL;
    addToTree(list, n);
    
    n = malloc(sizeof(node));
    n->number = 3;
    n->left = NULL;
    n->right = NULL;
    addToTree(list, n);
    
    n = malloc(sizeof(node));
    n->number = 18;
    n->left = NULL;
    n->right = NULL;
    addToTree(list, n);
    
    n = malloc(sizeof(node));
    n->number = 13;
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
node initNode(int value)
{
    node *temp = malloc(sizeof(node));
    temp->number = value;
    temp->left = NULL;
    temp->right = NULL;
    return *temp;
}

void addToTree(node *root, node *key){
    if (root && key)
    {
        //add to the tree
        //Start from the top
        printf("Add to tree\n");
        if(root == 0){
            printf("Zero\n");
            root = malloc(sizeof(node));
            root = key;
            root->left = 0;
            root->right = 0;
        }

        //check if the number is smaller or bigger
        //if bigger add to the right
        else if (root->number < key->number)//If the tree's number is smaller than the number add the number to the right of the tree
        {
            printf("Right\n");
            addToTree(root->right, key);
        } 
        //if smaller add to the left
        else
        {
            printf("Left\n");
            addToTree(root->left, key);
        }
    }
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
