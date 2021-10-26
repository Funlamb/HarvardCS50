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

//Number of buckets for the hast table. 26 letters in the alphabit
const unsigned int N = 26;
//hash table
node *table[N];
loadHashTable(node *temp);//My own function to create the hash table

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
        //change the word to lower case. Could I be doing this better?
        char lowerBuffer[MAX_LENGTH];
        for (int i = 0; i < MAX_LENGTH; i++)
        {
            char ch;
            ch = buffer[i];
            lowerBuffer[i] = (char) tolower(ch);
        }
       
        const int REDUCE_TO_BUCKET = 97;
        int correctBucket = lowerBuffer[0] - REDUCE_TO_BUCKET;

        //create a node from line
        node *temp= malloc(sizeof(node));
        if (!temp)
        {
            printf("Could not create node.\n");
            return 1;
        }
        sprintf(temp->word, lowerBuffer);//load the word into the temp node
        temp->next = NULL;
        //load each line to table
        loadHashTable(temp);
        free(temp);
    }

    if (feof(dictionaryFile))
    {
        printf("\nEnd of File\n");
    }

    //TODO Print the hashtable
    printHashTable(table[0]);
    //TODO Unload the hashtable

    fclose(dictionaryFile);
    return 0;
}

loadHashTable(node *temp){
    printf("Temp Word: %s", temp->word);//Test that the word is in the temp node

    //get the bucket it is supposed to go in.
    const int REDUCE_TO_BUCKET = 97;
    int correctBucket = temp->word[0] - REDUCE_TO_BUCKET;
    
    //put it in that bucket
    if (table[correctBucket]->next == NULL)
    {
        /* code */
    }
    
    temp->next = table[correctBucket]->next;
    table[correctBucket] = temp;

    //TODO: Link the table when there is a collision in the hash table
}

printHashTable(node *toPrint){
    if (toPrint->word)
        {
            printf("%s\n", toPrint->word);
            printHashTable(toPrint->next);
        }    
}