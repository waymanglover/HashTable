#ifndef LinkedList_h
#define LinkedList_h

#include <stdbool.h>
#include "Node.h"

// Should probably figure out how to make the member variables 
// private and add a getter for the length. 
// Nobody should be directly touching the member variables --
// that would quickly get the length member variable out of sync
// with reality.
typedef struct linked_list 
{
	node * head;
	int length; 
} linked_list;

linked_list* createList();
void destroyList(linked_list** list);
bool addNode(linked_list* list, char* key, char* value);
bool removeNode(linked_list* list, char* key);
node* findTail(linked_list* list);
node* getNode(linked_list* list, char* key);
void printList(linked_list* list);

#endif