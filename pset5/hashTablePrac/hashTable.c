//Practice for my hash table
//I don't really inderstand what is going on in the cs50 version because there is just so much to look at so I am making my own.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <string>
#include <string.h>
#include <ctype.h>

int const LENGTH = 45;

typedef struct node {
    char word[LENGTH + 1];
    struct node *next;
} node;

bool loadHashTable(node **n, char c[]);
bool testWord(node **test, char *c);
int findBucket(char c);
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
        return 1;
    }

    //read each line
    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH + 1];
    while (fscanf(dictionaryFile, "%s", buffer) != EOF)
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
        memset(lowerBuffer, 0, MAX_LENGTH);
        // for (int i = 0; i < wordLen; i++)
        // {
        //     lowerBuffer[i] = NULL;
        // }
    }

    if (feof(dictionaryFile))
    {
        printf("\nEnd of File\n");
    }
    fclose(dictionaryFile);

    //Test word
    char *word = "alloy";
    printf("Did we find the word? %i\n\n", testWord(&table[findBucket(word[0])],word));
    char *word2 = "aunt";
    printf("Did we find the word? %i\n\n", testWord(&table[findBucket(word2[0])],word2));
    char * word3 = "Duck";
    printf("Did we find the word? %i\n\n", testWord(&table[findBucket(word3[0])],word3));
    char * word4 = "caps";
    printf("Did we find the word? %i\n\n", testWord(&table[findBucket(word4[0])],word4));
    //TODO Unload the hashtable

    return 0;
}

int findBucket(char c){
    char b = tolower(c);
    int bucketToCheck = b - 'a';
    return bucketToCheck;
}

bool testWord(node **test, char *c){
    if (!(*test))
    {
        return false;
    }

    int len = strlen((*test)->word);
    printf("Table: %s \tTest: %s\n", (*test)->word, c);
    printf("Is this the word? %i\n", strncmp(c, (*test)->word, len) == 0);
    if(strlen(c) == len && strncmp(c, (*test)->word, len) == 0){
        return true;
    }
    testWord(&(*test)->next, c);
    return false;
}

bool loadHashTable(node **n, char c[]){
    if (*n == NULL)
    {
        //create temp node
        node *temp= malloc(sizeof(node));
        if (!temp)
        {
            printf("Could not create node.\n");
            return false;
        }
        strcpy(temp->word, c);
        temp->next = NULL;
        *n = temp;
   }
   else // we never get here. Why?
   {
        loadHashTable(&((*n)->next), c);
   }
   return true;
}

void printHashTable(node *toPrint){
    //TODO: Print the hash table
    if (toPrint)
        {
            printf("%s\n", toPrint->word);
            printHashTable(toPrint->next);
        }
}