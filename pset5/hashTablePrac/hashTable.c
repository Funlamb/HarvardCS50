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
bool testWord(char *c, node **table);
bool testWordRec(node **test, char *c);
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
        for (int i = 0; i < wordLen; i++)
        {
            lowerBuffer[i] = NULL;
        }
    }

    if (feof(dictionaryFile))
    {
        printf("\nEnd of File\n");
    }
    fclose(dictionaryFile);

    //TODO Print the hashtable
    // for (int i = 0; i < N; i++)
    // {
    //     printHashTable(table[i]);
    // }

    //TODO Test word
    // testWord("Alloy", table);
    // printf("%i\n", testWord("Gwar", table));
    printf("Did we find the word? %i\n", testWord("Alloy4567", table));
    printf("Did we find the word? %i\n", testWord("angry", table));
    printf("Did we find the word? %i\n", testWord("dic", table));
    //TODO Unload the hashtable
    char key[] = "help";
    char word[] = "help";
    printf("%i\n", strcmp(key,word)==0);

    return 0;
}

bool testWord(char *c, node **table){
    //find length of word to test
    int testWordLen = strlen(c);
    printf("Str Len: %i\n", testWordLen);
    
    //convert to lower case
    char s[testWordLen];
    for (int i = 0; i < testWordLen; i++)
    {
        s[i] =  tolower((unsigned char) c[i]);
    }
    
    //find which bucket to check
    int bucketToCheck = s[0] - 'a';
    // printf("Str Bucket: %i\n\n", bucketToCheck);
    //check each word till word found
    
    return testWordRec(&table[bucketToCheck], s);
}

bool testWordRec(node **test, char *c){
    //test each letter
    printf("Table: %s \tTest: %s\n", (*test)->word, c);
    if (!(*test)->word)
    {
        return false;
    }
    int len = 0;
    len = strlen(c) - 2;
    int lenToTrue = 0;
    // printf("Len Word to check: %i, Len of word: %i\n", len, strlen((*test)->word));
    if(strcmp(c, (*test)->word) == 0){
        return true;
    }
    testWordRec(&(*test)->next, c);
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
        // printf("New Node Word: %s\n", (*n)->word);
   }
   else // we never get here. Why?
   {
        // printf("Link Node: %s\n", (*n)->word);
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