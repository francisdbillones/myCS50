// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

#define ALPHA_FACTOR 65

// Number of buckets in hash table
const unsigned int N = 65536;

// Number of words in dictionary
unsigned int word_count = 0;

// Hash table
node *table[N];

void add_to_hash(node* node)
{
    //set node's next pointer to first element in appropriate hash bucket
    node->next = table[hash(node->word)];
    //set the node as the new first element in the hash bucket
    table[hash(node->word)] = node;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //initialize traverse function and set it to first element in appropriate hash bucket
    node* traverse = table[hash(word)];

    //while traverse isn't the end of the bucket yet,
    while (traverse != NULL)
    {
        //check if the current traverse node is equal to word
        if (strcasecmp(traverse->word, word) == 0)
        {
            return true;
        }

        //else, move on to next node
        traverse = traverse->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash_value = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash_value = (hash_value << 2) ^ word[i];
    }
    return hash_value % N; //N is size of hashtable
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //open dictionary file
    FILE* dictionary_in = fopen(dictionary, "r");

    //check if file open was successful
    if (dictionary_in != NULL)
    {
        //buffer to store string from fscanf
        char buffer[LENGTH + 1];

        //iterate over every string until reached end of file
        while (fscanf(dictionary_in, "%s", buffer) != EOF)
        {  
            //increment word count for every iteration
            word_count++;

            //allocate new memory for a new node
            node* new_node = malloc(sizeof(node));

            //check if memory allocation was successful
            if (new_node != NULL)
            {
                //set the new node's next pointer to NULL for now
                new_node->next = NULL;

                //copy the string from buffer to the new_node's word container
                strcpy(new_node->word, buffer);

                //add the node to the hash table
                add_to_hash(new_node);
            }

            //if error in allocating memory,
            else
            {
                //reset word count to indicate error in loading
                word_count = 0;

                printf("Memory error\n");
                return false;
            }
        }
        //close dictionary file and check if closing was successful, then return true
        if (fclose(dictionary_in) != EOF) 
            return true;
    }

    //if file open was not successful, return false
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
    //node var to "crawl" through each node in hash table
    node* crawler;
    //node var to store crawler's next pointer, since the original will be lost after free()
    node* crawler_next;

    //iterate through each bucket in hash table
    for (int i = 0; i < N; i++)
    {
        //set crawler to first element in bucket
        crawler = table[i];

        //while crawler isn't the end of bucket,
        while (crawler != NULL)
        {
            //store the next pointer
            crawler_next = crawler->next;

            //free the current node
            free(crawler);

            //"crawl" to the next node
            crawler = crawler_next;
        }
    }
    return true;
}
