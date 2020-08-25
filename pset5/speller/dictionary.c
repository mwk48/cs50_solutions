// Implements a dictionary's functionality
#include <stdio.h>
#include <ctype.h>
#include <strings.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "dictionary.h"

unsigned int counter=0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 150000;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int index=hash(word);
    node *head=table[index];
    if (head!=NULL)
    {
        node *temp=head;
        while (1)
        {
            if (strcasecmp(temp->word, word)==0)
            {
                return true;
            }
            if (temp->next==NULL)
            {
                break;
            }
            temp=temp->next;
        }
    }
    return false;
}

// Hashes word to a number
// Source of hash function: https://github.com/hathix/cs50-section/blob/master/code/7/sample-hash-functions/good-hash-function.c
unsigned int hash(const char* word)
 {
     unsigned long hash = 5381;

     for (const char* ptr = word; *ptr != '\0'; ptr++)
     {
         hash = ((hash << 5) + hash) + tolower(*ptr);
     }

     return hash % N;
 }

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *temp = fopen(dictionary, "r");
    char load[LENGTH + 1];
    unsigned int index2;
    if (!temp)
    {
        return false;
    }
    while (fscanf(temp,"%s", load) != EOF)
    {
        node *n=malloc(sizeof(node));
        if (n==NULL)
        {
            return false;
        }
        strcpy(n->word, load);
        index2=hash(load);
        counter+=1;
        if (table[index2]==NULL)
        {
            n->next=NULL;
            table[index2]=n;
        }
        else
        {
            n->next=table[index2];
            table[index2]=n;
        }
    }
    fclose(temp);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i=0; i<N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}