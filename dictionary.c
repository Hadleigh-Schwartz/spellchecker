/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 * Hash function borrowed from delipity, moderator of CS50's subreddit
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

#define HASHTABLE_SIZE 65536

// prototype for hash function
int hash_it(char* needs_hashing);

// typdef nodes for loading dictionary into hashtable
typedef struct node 
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

// globally declare array of node pointers for hash table
node* hashtable [HASHTABLE_SIZE] = {NULL};

//globally declare int for keeping track of dictionary size
int dict_size = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // make version of word with only lower cases, making sure to conclude new char* with \0
    char lower_word[LENGTH + 1];
    int length = strlen(word);
    for(int i = 0; i < length; i++)
    {
       lower_word[i] = tolower(word[i]);
    }
    lower_word[length] = '\0';
    
    // find hash value of lower cased word
    int hash_value = hash_it(lower_word);
    
    if (hashtable[hash_value] == NULL)
    {
        return false;
    }
    
    // create pointer to traverse linked list
    node* trav = hashtable[hash_value];
    
    while(trav != NULL)
    {
       if(strcmp(lower_word, trav->word) == 0)
       {
           return true;
       }
      
      trav = trav->next; 
      
    }
    
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    
    // try to open dictionary file
    FILE* dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
    
    // create trash array for use while loop
    char word[LENGTH + 1];
    
    while(fscanf(dict, "%s", word) != EOF)
    {
        // load word into node
        node* new_node = malloc(sizeof(node));
        
        strcpy(new_node->word, word);
    
        // hash the word
        int hash_value = hash_it(new_node->word);
    
        // go to hash_value's index in the node array and insert filled node into linked list
        if(hashtable[hash_value] == NULL)
        {
            hashtable[hash_value] = new_node;
            new_node->next = NULL;
        }
        else
        {
        new_node->next = hashtable[hash_value];
        hashtable[hash_value] = new_node;
        }
        
        dict_size++;
    
    }
    
    fclose(dict);
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if(dict_size > 0)
    {
    return dict_size;
    }
    else
    {
    return 0;
    }
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for(int i = 0; i < HASHTABLE_SIZE; i++)
    {
        node* trav = hashtable[i];
        
        while(trav != NULL)
        {
            node* temp = trav;
            trav = trav->next;
            free(temp);
        }
    }
    
    return true;
}

// hashes word 
int hash_it(char* needs_hashing)
{
    unsigned int hash = 0;
    for (int i=0, n=strlen(needs_hashing); i<n; i++)
        hash = (hash << 2) ^ needs_hashing[i];
    return hash % HASHTABLE_SIZE;
}