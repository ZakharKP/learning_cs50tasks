// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

#include <strings.h>
#include <string.h>

#include <ctype.h>

#include <stdlib.h>

#include <stdio.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 100;

// Hash table
node *table[N];

//size counter;
int sizeCounter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
//take hash of word
    int h = hash(word);
//start checking of table
    for (node *n = table[h]; n != NULL; n = n->next)
    {
        if(strcasecmp(n->word, word) == 0) return true;
    }
    return false;
//iThinkIt'sDoneCounter = 1;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
//find long of word
    int l = strlen(word);
    int h = ((tolower(word[0])+tolower(word[l-1])+l)*31)%N;
// find hash like (very first char + last char + long of word) * 31 % N

    return h;
//iThinkIt'sDoneCounter = 1;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
//check if false
    if(dictionary == NULL) return false;

//try to open dictionary
    FILE *d = fopen(dictionary, "r");
    if(d == NULL)
    {
        fclose(d);
        return false;
    }

//create new word
    char *word = malloc(LENGTH);
    if(word == NULL) return false;


//read file
    while(fscanf(d, "%s", word) != EOF)
    {
    //take hash
        int h = hash(word);

    // create new node
        node *n = malloc(sizeof(node));
        if(n == NULL)
        {
            free(d);
            free(word);
            return false;
        }
    //insetr word to n
        strcpy(n->word, word);
        n->next = NULL;

    //incert n to table
        if(table[h] == NULL)
        {
            table[h] = n;
        }
        else
        {
            n->next = table[h];
            table[h] = n;
        }
    //size counter +1
        sizeCounter++;
    }
//Free dictionary File
    fclose(d);

// free word;
    free(word);


//if everithing is OK return OK
    return true;
//iThinkIt'sDoneCounter = 7;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return sizeCounter;
//iThinkIt'sDoneCounter = 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
//printf("SIZECOUNTER == %i\n", sizeCounter);                                                                //HERE I WAS STOP LAST TIME
//start loop N times
    for(int i = 0; i < N; i++)
    {
    //start free every table linklist
        //for (node *n = table[i]; n != NULL;)
        while(table[i] != NULL)
        {
            node *shreder = table[i]->next;
            free(table[i]);
            table[i] = shreder;
        // size counter -1;
            sizeCounter--;
        }
    }
// chek if everithing was del
//printf("SIZECOUNTER == %i\n", sizeCounter);
    if(sizeCounter == 0) return true;
    else return false;
//iThinkIt'sDoneCounter = 4;
}
