// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include <string.h>
#include <strings.h>
#include <ctype.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

unsigned int numberOfWordsInDictionary = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int hashValue = hash(word);
    node *cursor = table[hashValue];
    while(cursor){
        if(strcasecmp(word, cursor->word) ==0) {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    char b = tolower(word[0]);
    int bucketToCheck = b - 'a';
    return bucketToCheck;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    printf("Trying to locd dic\n");
    FILE *dictionaryFile = fopen(dictionary, "r");
    if (!dictionaryFile)
    {
        printf("No dictionary file.\n");
        return false;
    }
    char word[LENGTH + 1];
    while (fscanf(dictionaryFile, "%s", word) != EOF){
        node *temp = malloc(sizeof(node));
        if (!temp)
        {
            unload();
            fclose(dictionaryFile);
            return false;
        }
        strcpy(temp->word, word);
        unsigned int hashValue = hash(word);
        temp->next = table[hashValue];
        table[hashValue] = temp;
        numberOfWordsInDictionary++;
    }

    fclose(dictionaryFile);
    return true;
}


// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return numberOfWordsInDictionary;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for(int i = 0; i < N; i++){
        node *cursor = table[i];

        while(cursor){
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
        if((i == N -1) && cursor == NULL){
            return true;
        }

    }
    return false;
}
