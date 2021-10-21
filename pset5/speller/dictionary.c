// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"

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

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    return 0;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    printf("Trying to dic\n");
    FILE *dictionaryFile = fopen(dictionary, "r");
    if (!dictionaryFile)
    {
        printf("Hello");
        return false;
    }

    while (!feof(dictionaryFile)){
        node *temp = malloc(sizeof(node));
        if (!temp)
        {
            unload();
            fclose(dictionaryFile);
            return false;
        }
        if(fscanf(dictionaryFile,"%s", temp->word) == 1){
            printf("%s", temp->word);
            // printf("Hello\n");
            hash(temp->word);
        }
    }
    if(feof(dictionaryFile)){
        return true;
    }
    fclose(dictionaryFile);
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
