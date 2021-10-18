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
node *initNode(int value);
void printTree(node *root);
int main(void) {
    node *n1 = initNode(10);
    node *n2 = initNode(14);
    node *n3 = initNode(7);
    node *n4 = initNode(123);
    node *n5 = initNode(4);

    n1->left = n5;
    n1->right = n4;
    n5->right = n2;
    n4->left = n3;

    printTree(n1);

    free(n1);
    free(n2);
    free(n3);
    free(n4);
    free(n5);
    return 0;
}

void printTree(node *root){
    if (!root)
    {
        printf("Empty\n");
    }
    printf("Value = %d\n", root->number );
    printf("Left: \n");
    printTree(root->left);
    printf("Right: \n");
    printTree(root->right);
}

node *initNode(int value)
{
    node *temp = malloc(sizeof(node));
    if (!temp)
    {
        temp->number = value;
        temp->left = NULL;
        temp->right = NULL;
    }
    return temp;
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
