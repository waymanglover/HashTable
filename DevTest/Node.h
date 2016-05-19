#ifndef Node_h
#define Node_h

// Probably should just be a part of LinkedList...
// but I've already separated it out.
typedef struct node 
{
	char* key;
	char* value;
	struct node * next;
} node;

node * createNode(char* key, char* value);

#endif