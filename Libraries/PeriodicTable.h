#ifndef PERIODIC_TABLE_H_DEFINED
#define PERIODIC_TABLE_H_DEFINED

#include <stdbool.h>
#include <stdarg.h>

#include "List.h"
#include "Element.h"

typedef List Ptable; // List and Ptable are synonymes

typedef enum elemAttribute
{
	Name,
	Symbol,		// Chemical Symbol
	AtomicNum,	// Atomic Number
	Mass,		// Atomic Mass
	Type,		// Element Type or Property (see Element.h)
	State		// Aggregation State (see Element.h)
} elemAttribute;

Ptable* newPtable();
void delPtable(Ptable**, bool delElements);

/* Serializes the file.
	path = absolute path to
		   existent file, or to folder in which the file
		   will be created.
		   If path is NULL, default path "Resources/default/periodicTable.txt" will be used.
	deleteTable = true if you want to also delete the Ptable struct, false otherwise.
Returns true if could save table to file, false otherwise. */
bool savePtable(Ptable**, char* path, bool deleteTable, bool delElements);
/* Deserializes the file.path = absolute path to the file with elements.
Returns loaded Periodic Table struct, NULL if there's a failure. */
Ptable* loadPtable(char* path);

/* Adds a new element to the Periodic Table
returns true if could add element, false otherwise.*/
bool addElement(Ptable*, Element*);
/* Removes an element from the Periodic Table
returns removed element if successful, NULL otherwise. */
Element* removeElement(Ptable*, int atomicNum);

/* Gets an element from the Periodic Table.
pos = internal position index of the element in the list.
	DO NOT CONFUSE WITH ATOMIC NUMBER!!!
Returns the element found or NULL if not found. */
Element* getElement(Ptable*, int pos);
/* Searches an element from the Periodic Table
by a given element attribute.
elemAttribute = type of the element's attribute to search with
attrValue = the actual value of the target element's attribute.
			ALWAYS SEND A POINTER TO THE VALUE, NOT THE LITERAL.
Returns the element found or NULL if not found. */
Element* findElement(Ptable*, elemAttribute, void* attrValue);

void showPtable(Ptable*);
/* Displays a selection of elements from the Table.
elemCount = the amount of selected elements to display.
... = for each element, send:
	attribute type (elemAttribute)
	POINTER TO the value of that attribute. */
void showElements(Ptable*, unsigned int elemCount, ...);


#endif // !PERIODIC_TABLE_H_DEFINED