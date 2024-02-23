#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

typedef struct Node Node;

Node* newNode(void*);
void delNode(Node**);

void* getData(Node*);
Node* getNext(Node*);

void setData(Node*, void*);
void setNext(Node*, Node*);


#endif // !NODE_H_INCLUDED