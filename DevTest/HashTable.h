#ifndef HashTable_h
#define HashTable_h

#include "LinkedList.h"

typedef struct hashtable 
{
    // Our array of linked lists. The bread and butter of this whole operation.
    linked_list** array;
    // Lenght measures the number of buckets in the
    // array. Should never change after a list has
    // been created.
    int length; 
} hashtable;

hashtable* createTable(int length);
void destroyTable(hashtable** table);
int generateHash(hashtable* table, char* key);
bool insertIntoTable(hashtable* hashtable, char* key, char* value);
bool removeFromTable(hashtable* table, char* key);
void printTable(hashtable* table);
node* getNodeFromTable(hashtable* table, char* key);
void printHistogram(hashtable* table);
int getNumberOfNodes(hashtable* table);

#endif
