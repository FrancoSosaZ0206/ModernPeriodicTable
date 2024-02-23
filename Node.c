#include <stdlib.h>
#include <stdio.h>

#include "Node.h"


typedef struct Node
{
	void* data;
	struct Node* next;
} Node;

Node* newNode(void* data)
{
	Node* self = malloc(sizeof(Node));
	if (!self)
	{
		fprintf(stderr, "ERROR: in newNode(), node couldn't be created.\n");
		exit(1);
	}

	self->data = data;
	self->next = NULL;

	return self;
}
void delNode(Node** self)
{
	free(*self);
	*self = NULL;
}

void* getData(Node* self)
{
	return self->data;
}
Node* getNext(Node* self)
{
	return self->next;
}

void setData(Node* self, void* data)
{
	self->data = data;
}
void setNext(Node* self, Node* next)
{
	self->next = next;
}
