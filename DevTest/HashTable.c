#include "HashTable.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Using the basic hashing function from
// http://pumpkinprogrammer.com/2014/06/21/c-tutorial-intro-to-hash-tables/
int generateHash(hashtable* table, char* key) 
{
    int value = 0;
    for (unsigned int i = 0; i < strlen(key); i++) 
    {
        value += key[i];
    }
    return (value % table->length);
}

hashtable* createTable(int length) 
{
    hashtable* table = malloc(sizeof(*table));
    if (table)
    {
        table->array = malloc(sizeof(*(table->array)) * length);
        if (table->array)
        {
            for (int n = 0; n < length; n++)
            {
                table->array[n] = createList();
            }
            table->length = length;
        }
    }
    return table;
}

bool insertIntoTable(hashtable* table, char* key, char* value) 
{
    int index = generateHash(table, key);
    return addNode(table->array[index], key, value);
}

bool removeFromTable(hashtable* table, char* key) 
{
    int index = generateHash(table, key);
    return removeNode(table->array[index], key);
}

void printTable(hashtable* table) 
{
    for (int n = 0; n < table->length; n++) 
    {
        printf("List %d: ", n);
        printList(table->array[n]);
    }
}

// Only returns the first instance
node* getNodeFromTable(hashtable* table, char* key) 
{
    int index = generateHash(table, key);
    return getNode(table->array[index], key);
}

void printHistogram(hashtable* table) 
{
    printf("Histogram (%d items total):\n", getNumberOfNodes(table));
    for (int i = 0; i < table->length; i++) 
    {
        printf("%d:\t", i + 1);
        for (int n = 0; n < table->array[i]->length; n++) 
        {
            printf("*");
        }
        printf("\n");
    }
}

// Returns the total number of nodes in the hashtable.
int getNumberOfNodes(hashtable* table) 
{
    int count = 0;
    for (int n = 0; n < table->length; n++) 
    {
        count += table->array[n]->length;
    }
    return count;
}

void destroyTable(hashtable** table) 
{
    hashtable* tableToDestroy = *table;
    for (int n = 0; n < tableToDestroy->length; n++) 
    {
        destroyList(&tableToDestroy->array[n]);
    }
    free(tableToDestroy->array);
    free(tableToDestroy);
    (*table) = NULL;
}