#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stdbool.h>
#include "Node.h"

typedef struct List List;

List* newList();
/* Claims allocated memmory for a list.
List** = pointer to ADDRESS of list.
delNodes = true if you want to also delete
			each node from the list, false otherwise.
delData = true if you want to also delete
			the data inside each node.
delDataFunc: if delData == true, send a destructor
			function for the data stored on the list.
			else, send NULL. The argument will be ignored. */
void delList(List**, bool delNodes, bool delData, void (*delDataFunc)(void**));

/* Returns true if the list is empty
and if the pointer to the list isn't NULL. */
bool emptyList(List*);
/* Calculates the amount of elements of the list.
Returns 0 if the list is empty or if the pointer
to the list is NULL. */
int lenList(List*);

void* getHeadList(List*);
List* getRestList(List*);
void* getDataList(List*, int);

// adding to the beginning of list
void addList(List*, void*);
// adding to the end of list
void pushList(List*, void*);
// inserts after position, returns true if successfully inserted.
bool insertList(List* self, void* data, int pos);
/** OPERATION: insert data at the head of a list
PRECONDITION: the list must have been created.
POSTCONDITION: the data is inserted AFTER THE HEADER
				of the list, that is, in the second place.
PARAMETERS:
	- list: pointer to the list
	- data: pointer to the data to be inserted
RETURNS: true if it was able to insert, false otherwise. */
bool insertByHead(List*, void*);

// Adds an element to a sorted list under certain criteria.
bool addOrderedList(List*, void*, bool (*compareData)(void*, void*));

// removing the first element
void* shiftList(List*);
// removing the last element
void* popList(List*);
void* removeList(List*, int pos);
/* Searches an element from a list with certain criteria.
If found, removes and returns it. Otherwise, returns NULL. */
void* removeOrderedList(List*, void* key, bool (*matchData)(void*, void*));

// appends node chain from source list to node chain of destination list
void mergeLists(List* dest, List* src);

// requires function to show the element of the list
void showList(List*, void (*showData)(void*));

/* Transforms list into a string.
Assumes elemToString() returns a dynamic string. */
char* listToString(List*, char* (*dataToString)(void*));

bool serializeList(List**, FILE*, void (*serializeData)(void*, FILE*));
List* deseializeList(FILE*, void (*deserializeData)(void*, FILE*));

// Requires function to clone each element.
List* cloneList(List*, void* (*cloneData)(void*));

/* Orders a list according to certain criteria.
Requires a cloning function for each element, as well as a
function to compare elements under certain criteria.
Returns cloned list if successful, NULL otherwise. */
List* sortList(List*, void* (*cloneData)(void*), bool (*compareData)(void*, void*));

/* Searches an element inside the list,
according to a certain criteria.
Requires a function to compare the key value
with the rest of the elements of the list. */
void* findList(List*, void* key, bool (*matchData)(void*, void*));


#endif // !LIST_H_INCLUDED