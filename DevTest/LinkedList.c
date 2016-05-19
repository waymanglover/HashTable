#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"
#include "Node.h"

// Creates a linked_list object, allocating the required memory.
linked_list* createList() 
{
    linked_list * newList = malloc(sizeof(*newList));
    if (newList) 
    {
        newList->head = NULL;
        newList->length = 0;
    }
    return newList;
}

// Loops through the items in a linked list,
// freeing the memory allocated for each.
void destroyList(linked_list ** list) 
{
    linked_list * listToDestroy = *list;
    node * current = listToDestroy->head;
    node * next = NULL;
    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
    free(listToDestroy);
    *list = NULL;
}

// Add a node to the end of the list.
// Dynamically allocates the memory for the node.
bool addNode(linked_list* list, char* key, char* value) 
{
    bool result = false;
	node * newNode = createNode(key, value);
	if (newNode) 
    {
		node * tail = findTail(list);
		if (tail) 
        {
			tail->next = newNode;
			list->length++;
		}
		else 
        {
			// We have an empty list. Add the new node as the head.
			list->head = newNode;
			list->length++;
		}
		result = true;
	}
	return result;
}

// Remove a key/value pair by key
// Returns true on success (item found and removed)
// and false on failure.
bool removeNode(linked_list* list, char* key) 
{
    bool result = false;
    if (list->head) 
    {
        node* current = list->head;
        node* previous = NULL;
        int match = strcmp(current->key, key) == 0;
        while (!match && current->next) 
        {
            previous = current;
            current = current->next;
            match = strcmp(current->key, key) == 0;
        }
        if (match) 
        {
            // Repoint the previous node to the deleted node's next node
            // unless the deleted node is the head.
            if (previous) previous->next = current->next;
            else list->head = current->next;
            free(current);
            list->length--;
            result = true;
        }
    }
    return result;
}

// Given a linked list, find the tail node
// If there is no head node for the list, returns NULL.
node* findTail (linked_list* list) 
{
    node * current = NULL;
	if (list->head) 
    {
		current = list->head;
		while (current->next) 
        {
			current = current->next;
		}
	}
	return current;
}

// Given a key and a linked list, find the first node with a key that matches.
node* getNode(linked_list* list, char* key) 
{
    node* result = NULL;
	if (list->head) {
		node* current = list->head;
        int match = strcmp(current->key, key) == 0;
		while (!match && current->next) 
        {
			// While the current key doesn't match the key we're looking for,
			// and there is a next node, continue looping through the list.
			current = current->next;
            match = strcmp(current->key, key) == 0;
		}
		if (match) result = current;
	}
	return result;
}

// Prints a given linked_list to the console
// in the format Key -> Value.
// If there is no head node for the list,
// "List is empty" is printed instead.
void printList(linked_list* list) 
{
	if (!list->head) 
    {
		printf("List is empty.\n");
	}
    else 
    {
        node* current = list->head;
        while (current) 
        {
            printf("%s -> %s", current->key, current->value);
            if (current->next) printf(", ");
            current = current->next;
        }
        printf("\n");
    }
}