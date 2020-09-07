// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

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
    node* traverse = table[hash(&word[0])]->next;
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
    //casts char to int, converts it to uppercase, and subtracts the alpha_factor (65). 
    //through this, the ascii value of A (65) becomes 0, B becomes 1, etc
    return ((int) (toupper(word[0])) - ALPHA_FACTOR);
}

// places node element into the front of appropriate linked list 
void add_to_hash(node* hash_table[], node* node)
{
    //sets node's next pointer to point at the same thing head is pointing to
    node->next = table[hash(&node->word[0])]->next;
    //sets head to point at node
    table[hash(&node->word[0])]->next = node;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //open dictionary file
    FILE *dictionary_in = fopen(argv[1], "r");

    //checking for file open error
    if (dictionary_in == NULL)
    {
        printf("Error opening dictionary file\n");
        return false;
    }

    //temporary word store
    char tmp_word[LENGTH + 1];

    //loop to scan each string in dictionary
    while(fscanf(dictionary_in, "%s", tmp_word) != EOF)
    {
        //increment the value of word_count
        word_count++;

        //create new node
        node* new_node = malloc(sizeof(node));

        //checks that memory was allocated properly
        if (new_node != NULL)
        {
            //copy from tmp_word into new_node->word
            strcpy(new_node->word, tmp_word);
            //set new_node->next to NULL for now
            new_node->next = NULL;
            //insert new_node into appropriate position in hash table
            add_to_hash(table, new_node);
        }
        //if error in allocating memory, return false
        else
        {
            printf("Error loading dictionary\n");
            word_count = 0;
            return false;
        }

    }


    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    free(table);
    return true;
}
