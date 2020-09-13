// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <ctype.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

#define ALPHA_FACTOR 65
#define ALPHABET 26

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
    node* traverse = table[hash(word)];
    while (traverse != NULL)
    {
        if (strcasecmp(traverse->word, word) == 0)
        {
            return true;
        }
        traverse = traverse->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    char buffer = word[0];
    return (((int) (toupper(buffer)) - ALPHA_FACTOR) % ALPHABET);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE* dictionary_in = fopen(dictionary, "r");
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
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node* crawler;
    node* crawler_next;

    for (int i = 0; i < ALPHABET; i++)
    {
        crawler = table[i];
        while (crawler != NULL)
        {
            crawler_next = crawler->next;
            free(crawler);
            crawler = crawler_next;
        }
    }
    return true;
}
