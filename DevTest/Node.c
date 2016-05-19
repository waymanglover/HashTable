#include <stdio.h>
#include <stdlib.h>
#include "Node.h"

// Creates a node with a given key, value pair.
// Note: does not update the length of the list.
// When using a linked_list, it's expected that nodes
// are added through linked_list's addNode().
node * createNode(char* key, char* value) 
{
	node * newNode = malloc(sizeof(*newNode));
	if (newNode) {
		newNode->key = key;
		newNode->value = value;
		newNode->next = NULL;
		return newNode;
	}
	return newNode;
}
