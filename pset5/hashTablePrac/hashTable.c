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

void loadHashTable(node **n, char c[]);
void printHashTable(node *toPrint);

int main(int argc, char *argv[]){
    //Number of buckets for the hast table. 26 letters in the alphabit
    const unsigned int N = 26;
    //hash table
    node *table[N];

    //set everything to null in the table.
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    
    //check for correct usage
    if (argc != 2)
    {
        printf("Usage: hashTable DICTIONARY\n");
        return 1;
    }
    
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
        int wordLen = strlen(buffer);
        for (int i = 0; i < wordLen; i++)
        {
            char ch;
            ch = buffer[i];
            lowerBuffer[i] = (char) tolower(ch);
        }
    
        //load each line to table in correct bucket
        const int REDUCE_TO_BUCKET = 97;
        int correctBucket = lowerBuffer[0] - REDUCE_TO_BUCKET;
        loadHashTable(&table[correctBucket], lowerBuffer);
    }

    if (feof(dictionaryFile))
    {
        printf("\nEnd of File\n");
    }

    //TODO Print the hashtable
    //printHashTable(table[0]);
    printf("%s", table[0]->word);
    //TODO Unload the hashtable

    fclose(dictionaryFile);
    return 0;
}

void loadHashTable(node **n, char c[]){
    if (*n == NULL)
    {
        //create temp node
        node *temp= malloc(sizeof(node));
        if (!temp)
        {
            printf("Could not create node.\n");
        }
        sprintf(temp->word, "%s",  c);//load the word into the temp node
        temp->next = NULL;
        *n = temp;//Why is n not being set here? 
        printf("New Node Word: %s", (*n)->word);
   }
   else // we never get here. Why?
   {
        printf("Link Node: %s", (*n)->word);
        loadHashTable(&((*n)->next), c);
   }
}

void printHashTable(node *toPrint){
    //TODO: Print the hash table
    if (toPrint->word != NULL)
        {
            printf("%s\n", toPrint->word);
            printHashTable(toPrint->next);
        }    
}