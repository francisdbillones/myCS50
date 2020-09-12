// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

#define ALPHA_FACTOR 65;
#define ALPHABET 26;

// var to store amount of words in dictionary
unsigned int word_count = 0;

// Hash table
node *table[ALPHABET];

void add_to_hash(node* node)
{
    node->next = table[hash(node->word)];
    table[hash(node->word)] = node;
}

// Returns true if word is in dictionary else false
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

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    dictionary_in = fopen(dictionary, "r");
    if (dictionary_in != NULL)
    {
        char buffer[LENGTH + 1];
        
        while (fscanf(dictionary_in, "%s", buffer) != EOF)
        {
            word_count++;
            node* new_node = malloc(sizeof(node));

            if (new_node != NULL)
            {
                new_node->next = NULL;
                strcpy(new_node->word, buffer);
                add_to_hash(new_node);
            }
            else
            {
                word_count = 0;
                printf("Memory error\n");
                return false;
            }
        }
        return true;
    }
    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}
