// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "dictionary.h"

#define ALPHA_FACTOR 65

// Number of buckets in hash table
const unsigned int ALPHABET = 26;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Hash table
node *table[ALPHABET];

// var to keep track of word count
unsigned int word_count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //variable to traverse each node, set to equal to first node in appropriate bucket
    node* traverse = table[hash(&word[0])];

    //loop to traverse each node and check if word matches current node
    while (traverse != NULL)
    {
        if (strcasecmp(traverse->word, word))
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
    char tmp_word[sizeof(word)];
    //casts char to int, converts it to uppercase, and subtracts the alpha_factor (65). 
    //through this, the ascii value of A (65) becomes 0, B becomes 1, etc
    strcpy(tmp_word, word);
    return (((int) toupper(tmp_word[0]) - ALPHA_FACTOR) % ALPHABET);
}

// places node element into the front of appropriate linked list 
void add_to_hash(node* n)
{
    n->next = table[hash(n->word)];
    table[hash(n->word)] = n;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //temporary variable to store a single word
    char tmp_word[LENGTH + 1];

    //open file
    FILE* dictionary_file = fopen(dictionary, "r");

    //if successfully opened file,
    if (dictionary_file != NULL)
    {
        //while loop to scan each string in dictionary into tmp_word
        while (fscanf(dictionary_file, "%s", tmp_word) != EOF)
        {
            //increment word count for each iteration
            word_count++;

            //create new node and allocate enough memory
            node* new_node = malloc(sizeof(node));

            //if memory successfully allocated,
            if (new_node != NULL)
            {
                //copy string from tmp_word into the node's word
                strcpy(new_node->word, tmp_word);
                //set  0    `        
                new_node->next = NULL;
                //add new_node to hash table
                add_to_hash(new_node);
            }

            //else error allocating memory
            else
            {
                word_count = 0;
                printf("Memory error, could not load dictionary.\n");
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
    node* tmp_crawler_next;
    node* crawler;

    for (int i = 0; i < ALPHABET; i++)
    {
        crawler = table[i];
        while (crawler->next != NULL)
        {
            tmp_crawler_next = crawler->next;
            free(crawler);
            crawler = tmp_crawler_next;
        }
    }
    return true;
}
