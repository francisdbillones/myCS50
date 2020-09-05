// Implements a dictionary's functionality

#include <stdbool.h>

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

// places node element into the front appropriate linked list 
void put_in_hash(node* hash_table[], node* node)
{
    //make a temporary variable for node to be placed
    node* tmp_node = node;
    //set node to point at same node that head is pointing to
    node->next = hash_table[hash(node)]->next;
    //set head to point to node
    hash_table[hash(node)]->next = tmp_node->next;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char word[];
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
    while(fscanf(dictionary_in, "%s", tmp_word))
    {
        //create new node
        node* new_node = malloc(sizeof(node));

        if (new_node != NULL)
        {
            strcpy(new_node->word, tmp_word);
            new_node->next = NULL;
            put_in_hash(table, new_node);
        }

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
