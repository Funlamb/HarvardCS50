//Practice for my hash table
//I don't really inderstand what is going on in the cs50 version because there is just so much to look at so I am making my own.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int const LENGTH = 45;

typedef struct node {
    char word[LENGTH + 1];
    struct node *next;
} node;

//Number of buckets for the hast table
const unsigned int N = 26;
//hash table
node *table[N];

int main(int argc, char *argv[]){
    
    //check for correct usage
    if (argc != 2)
    {
        printf("Usage: hashTable DICTIONARY\n");
        return 1;
    }
    
    //TODO Load a hashtable
    //open a file
    char *fileName = argv[1];
    FILE *dictionaryFile = fopen(fileName, "r");
    if (!dictionaryFile)
    {
        printf("Can not open file: %s\n", argv[1]);
    }
    //read each line
    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];
    while (fgets(buffer, MAX_LENGTH, dictionaryFile))
    {
        //change the word to lower case
        char lowerBuffer[MAX_LENGTH];
        for (int i = 0; i < MAX_LENGTH; i++)
        {
            char ch;
            ch = buffer[i];
            lowerBuffer[i] = (char) tolower(ch);
        }
       
        const int REDUCE_TO_BUCKET = 97;
        int correctBucket = lowerBuffer[0] - REDUCE_TO_BUCKET;
        // printf("%i:\t", lowerBuffer[0] - REDUCE_TO_BUCKET);
        // printf("%s", lowerBuffer);
        //create a node from line
        node *temp= malloc(sizeof(node));
        if (!temp)
        {
            printf("Could not create node.\n");
            return 1;
        }
        sprintf(temp->word, lowerBuffer);
        // temp->word = lowerBuffer;
        printf("Printing: %s", temp->word);
        //load each line to table
        //get the bucket it is supposed to go in. 
        //put it in that bucket
        // table[correctBucket]->next =         
        //if there is something there already link them together. 

    }

    if (feof(dictionaryFile))
    {
        printf("\nEnd of File\n");
    }
    
    
    //TODO Unload a hashtable
    
    //TODO Print a hashtable

    fclose(dictionaryFile);
    return 0;
}