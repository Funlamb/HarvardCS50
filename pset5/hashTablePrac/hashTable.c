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
    char word[46];
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
        //change the word to lower case. Could I be doing this better? Is this part wrong? 
        char lowerBuffer[MAX_LENGTH];
        int wordLen = strlen(buffer);
        for (int i = 0; i < wordLen; i++)//turn string lower case TODO change to test words at lower case 
        {
            char ch;
            ch = buffer[i];
            lowerBuffer[i] = (char) tolower(ch);
        }
    
        //load each line to table in correct bucket
        const int REDUCE_TO_BUCKET = 'a';
        int correctBucket = lowerBuffer[0] - REDUCE_TO_BUCKET;
        loadHashTable(&table[correctBucket], lowerBuffer);
        memset(lowerBuffer, 0, MAX_LENGTH);
        // for (int i = 0; i < wordLen; i++)
        // {
        //     lowerBuffer[i] = NULL;
        // }
    }
    for(int i = 0; i < 26; i++){

        printHashTable(table[i]);
    }

    if (feof(dictionaryFile))
    {
        printf("\nEnd of File\n");
    }
    fclose(dictionaryFile);

    //Test word
    char * word4 = "caps";
    printf("Did we find the word? %i\n\n", testWord(&table[findBucket(word4[0])],word4));//false
    char *word = "alloy";
    printf("Did we find the word? %i\n\n", testWord(&table[findBucket(word[0])],word));//true
    char *word2 = "aunt";
    printf("Did we find the word? %i\n\n", testWord(&table[findBucket(word2[0])],word2));//false
    char * word3 = "Duck";
    printf("Did we find the word? %i\n\n", testWord(&table[findBucket(word3[0])],word3));//false
    char *word5 = "caps";
    // int ptable = (*table[0])
    printf("Did we find the word? %s\n\n", testWord(&table[findBucket(word5[0])], word5) ? "true" : "false");
    //TODO Unload the hashtable
    return 0;
}

int findBucket(char c){
    char b = tolower(c);
    int bucketToCheck = b - 'a';
    return bucketToCheck;
}

//find out how to use **
bool testWord(node **test, char *c){
    // bool myTest = false;
    if (!(*test))
    {
        printf("Are we false.\n");
        return false;
        // return false;
    }

    int len = strlen((*test)->word);
    printf("Table: %s \tTest: %s\n", (*test)->word, c);
    // printf("Is this the word? %i\n", strncmp(c, (*test)->word, len) == 0);
    if(strncmp(c, (*test)->word, len) == 0){
    // if(strncmp(c, "caps", len) == 0){
        printf("About to return true.\n");
        // myTest = true;
        return true;
        //printf("Out.\n");
    }
    printf("Testing next node.\n");
    return testWord(&(*test)->next, c);// Reif is the man!!!
}

bool loadHashTable(node **n, char c[]){ //&table[a], alloy
//alloy -> any -> null
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
   else
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