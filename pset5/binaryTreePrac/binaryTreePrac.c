#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *left;
    struct node *right;    
}
node;

node *initNode(int value);
void addToTree(node *root, node *leaf);
void printTree(node *root);
int search(node *tree, int number);
void freeTree(node *tree);
void printNode(node *n);


int main(void) {
    node *n1 = initNode(10);
    node *n2 = initNode(11);
    node *n3 = initNode(12);
    node *n4 = initNode(13);
    node *n5 = initNode(14);

    addToTree(n1, n5);
    addToTree(n1, n3);
    addToTree(n1, n2);
    addToTree(n1, n4);
    printNode(n1);
    printNode(n2);
    printNode(n3);
    printNode(n4);
    printNode(n5);

    search(n1, 14);
    search(n1, 9);

    free(n1);
    free(n2);
    free(n3);
    free(n4);
    free(n5);
    return 0;
}

void printNode(node *n){
    printf("Node: %i ", n->number);
    if (n->left)
    {
        printf("Left: %i \t", n->left->number);
    } else {
        printf("Left: Empty \t");
    }
    if (n->right == NULL)
    {
        printf("Right: Empty \t");
    } else {
        printf("Right: %i \t", n->right->number);
    }
    printf("\n");
}

void printTree(node *root){
    if (!root)
    {
        printf("Empty\n");
        return;
    }
    printf("Value = %d\n", root->number );
    printf("Left: \n");
    printTree(root->left);
    printf("Right: \n");
    printTree(root->right);
    printf("done\n");
}

node *initNode(int value)
{
    node* temp = malloc(sizeof(node));
    if (temp)
    {
        temp->number = value;
        temp->left = NULL;
        temp->right = NULL;
    }
    return temp;
}

void addToTree(node *root, node *leaf){
    if (root && leaf)
    {
        //if leaf is larger than the root and it to the right
        if (leaf->number > root->number)
        {
            //add leaf to the right if root->right is empty
            if (root->right == NULL)
            {
                root->right = leaf;
            }else
            {
                addToTree(root->right, leaf);
            }
        }
        //if leaf is smaller than the root and it to the left
        else
        {
            if (root->left == NULL)
            {
                root->left = leaf;
            }
            else
            {
                addToTree(root->left, leaf);
            }   
        }
    }
}

int search(node * tree, int number){
    printf("Searching for: %i\n" , number);
    if(tree == NULL){
        printf("No Tree\n");
        return 0;
    } 
    if(tree->number == number){
        printf("found it\n");
        return 1;
    }
    if (number > tree->number)
    {
        printf("going Right\n");
        return search(tree->right, number);
    } else 
    {
        printf("going left\n");
        return search(tree->left, number);
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
