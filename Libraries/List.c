#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "utilities.h"


typedef struct List
{
	Node* head; // first data
} List;

// PRIVATE
Node* getNodeList(List*, int);

// PUBLIC
List* newList()
{
	List* self = malloc(sizeof(List));
	if (!self)
	{
		fprintf(stderr, "ERROR: in newList(), list couldn't be created.\n");
		exit(1);
	}
	else
		self->head = NULL;
	return self;
}
void delList(List** self, bool delNodes, bool delData, void (*delDataFunc)(void**))
{
	if (*self)
	{
		if (delNodes)
		{
			while (!emptyList(*self))
			{
				void* data = shiftList(*self);
				if (delData && delDataFunc)
					delDataFunc(&data);
			}
		}

		free(*self);
		*self = NULL;
	}
}

bool emptyList(List* self)
{
	return self && !self->head;
}

//*******************************************
Node* getNodeList(List* self, int pos)
{
	Node* node = self->head;

	if (node)
	{
		int currPos = 0;
		while (currPos < pos && getNext(node))
		{
			currPos++;
			node = getNext(node);
		}
	}

	return node;
}
//*******************************************


int lenList(List* self)
{
	int len = 0;
	if (self)
	{
		Node* node = self->head;

		if (node)
		{
			while (node)
			{
				node = getNext(node);
				len++;
			}
		}
	}
	return len;
}

void* getHeadList(List* self)
{
	void* headData = NULL;
	if (self->head)
		headData = getData(self->head);
	return headData;
}
List* getRestList(List* self)
{
	List* rest = newList();
	if (self->head)
		rest->head = getNext(self->head);
	return rest;
}
void* getDataList(List* self, int pos)
{
	void* data = NULL;
	Node* node = getNodeList(self, pos);

	if(node)
		data = getData(node);

	return data;
}

void addList(List* self, void* data) // adding to the beginning of list
{
	Node* node = newNode(data);
	setNext(node, self->head);
	self->head = node;
}
void pushList(List* self, void* data) // adding to the end of list
{
	if (emptyList(self)) addList(self, data);
	else
	{
		Node* node = newNode(data);
		Node* last = getNodeList(self, lenList(self));
		setNext(last, node);
	}
}
bool insertList(List* self, void* data, int pos)
{
	bool couldInsert = false;
	Node* insert = getNodeList(self, pos);

	if (insert)
	{
		Node* node = newNode(data);
		setNext(node, getNext(insert)); // FIRST we must link insert's next with node, cause otherwise we'd lose it
		setNext(insert, node);
		couldInsert = true;
	}
	return couldInsert;
}
bool insertByHead(List* self, void* data)
{
	bool result = false;
	if (emptyList(self))
		addList(self, data);
	else
	{
		Node* node = newNode(data);
		if (node)
		{
			Node* head = self->head;
			setNext(node, getNext(head));
			setNext(head, node);
			result = true;
		}
	}
	return result;
}

bool addOrderedList(List* self, void* data, bool (*compareData)(void*, void*))
{
	bool result = false;

	if (emptyList(self)) // if there's no data in the list
	{
		addList(self, data);
		result = true;
	}
	else if (compareData(data, getHeadList(self)))
	{
		addList(self, data); // adding to the beginning
		result = true;
	}
	else
	{
		List* prevList = newList();
		mergeLists(prevList, self);
		List* currList = getRestList(prevList);

		bool added = false;
		while (!emptyList(currList) && !added)
		{
			void* prevData = getHeadList(prevList);
			void* currData = getHeadList(currList);

			if (!compareData(data, prevData) && compareData(data, currData))
			{ // adding in the middle
				if (!insertByHead(prevList, data)) exit(1);
				else
				{
					added = true;
					result = true;
				}
			}

			List* temp = prevList;
			prevList = currList;
			currList = getRestList(currList);
			delList(&temp, false, false, NULL);
		}
		// adding at the end (no need to check atomic nums.)
		if (!added)
		{
			if (!insertByHead(prevList, data)) exit(1);
			else result = true;
		}

		delList(&prevList, false, false, NULL);
		delList(&currList, false, false, NULL);
	}

	return result;
}

void* shiftList(List* self) // removing the first data
{
	void* data = NULL;
	if (self->head)
	{
		Node* remove = self->head;
		data = getData(remove);
		self->head = getNext(self->head);
		delNode(&remove);
	}
	return data;
}
void* popList(List* self) // removing the last data
{
	void* data = NULL;
	if (self->head)
	{
		Node* prevRemove = getNodeList(self, lenList(self) - 1);
		Node* remove = getNext(prevRemove);
		data = getData(remove);
		delNode(&remove);
		setNext(prevRemove, NULL); // we must do this manually, otherwise the next pointer of prevNode will be corrupted.
	}
	return data;
}
void* removeList(List* self, int pos)
{
	void* data = NULL;

	if (pos == 0) data = shiftList(self);
	else if (pos == lenList(self)) data = popList(self);

	else if (self->head)
	{
		Node* prevRemove = getNodeList(self, pos - 1);
		Node* remove = getNext(prevRemove);
		setNext(prevRemove, getNext(remove));

		data = getData(remove);
		delNode(&remove);
	}
	return data;
}
void* removeOrderedList(List* self, void* key, bool (*matchData)(void*, void*))
{
	void* removed = NULL;

	if (!emptyList(self))
	{
		if (matchData(key, getHeadList(self)))
			removed = shiftList(self);
		else
		{
			List* prevList = newList();
			mergeLists(prevList, self);
			List* currList = getRestList(prevList);

			while (!emptyList(currList))
			{
				if (matchData(key, getHeadList(currList)))
					removed = removeList(prevList, 1);

				List* temp = prevList;
				prevList = currList;
				currList = getRestList(currList);
				delList(&temp, false, false, NULL);
			}						
									
			delList(&prevList, false, false, NULL);
			delList(&currList, false, false, NULL);
		}
	}

	return removed;
}

void mergeLists(List* dest, List* src) // appends node chain from source list to node chain of destination list
{
	if (!dest->head)
		dest->head = src->head;
	else if (src->head)
	{
		Node* destLast = getNodeList(dest, lenList(dest));
		setNext(destLast, src->head);
	}
}

void showList(List* self, void (*showData)(void*)) // requires function to show the data of the list
{
	if (self && !emptyList(self))
	{
		List* aux = newList();
		mergeLists(aux, self);

		for (int i = 0; !emptyList(aux); i++)
		{
			printf("%d. ", i + 1);
			showData(getHeadList(aux));
			printf(".....................................\n\n");

			List* temp = aux;
			aux = getRestList(aux);
			delList(&temp, false, false, NULL);
		}
		printf("*****************************************\n\n");
		delList(&aux, false, false, NULL);
	}
}

char* listToString(List* self, char* (*dataToString)(void*))
{
	char* strList = NULL;

	if (self && !emptyList(self))
	{
		strList = dynamicString("");

		List* aux = newList();
		mergeLists(aux, self);

		for (int i = 0; !emptyList(aux); i++)
		{
			char buffer[100] = "";
			sprintf(buffer, "%d. ", i + 1);

			myStrcpy(&strList, buffer);

			char* buffer2 = dataToString(getHeadList(aux));
			myStrcat(&strList, buffer2);
			free(buffer2);

			myStrcat(&strList, ".....................................\n\n");

			List* temp = aux;
			aux = getRestList(aux);
			delList(&temp, false, false, NULL);
		}
		myStrcat(&strList, "*****************************************\n\n");
		delList(&aux, false, false, NULL);
	}

	return strList;
}

List* cloneList(List* self, void* (*cloneData)(void*))
{
	List* clone = NULL;
	if (self) {
		clone = newList();

		List* aux = newList();
		mergeLists(aux, self);

		while (!emptyList(aux)) {
			void* dataClone = cloneData(getHeadList(aux));
			if (dataClone)
				pushList(clone, dataClone);

			List* temp = aux;
			aux = getRestList(aux);
			delList(&temp, false, false, NULL);
		}
		delList(&aux, false, false, NULL);
	}
	return clone;
}

List* sortList(List* self, void* (*cloneData)(void*), bool (*compareData)(void*, void*))
{
	List* clone = NULL;
	if (self && !emptyList(self))
	{
		clone = newList();
		List* aux = newList(); // we'll traverse the original list with this one
		mergeLists(aux, self);

		while (!emptyList(aux))
		{
			// 1. Clone each data
			void* dataClone = cloneData(getHeadList(aux));
			if (dataClone)
			{
				switch (lenList(clone))
				{
				case 0: // 2. If list is empty, there's no need to check anything, we simply add it.
					addList(clone, dataClone);
					break;
				case 1:
				{ // 3. If it has only one data, we'll only check if it goes before or after it
					void* first = getHeadList(clone);

					if (compareData(dataClone, first))
						pushList(clone, dataClone);
					else
						addList(clone, dataClone);
					break;
				}
				default:
				{ // 4. If it has more than one...
					void* last = getDataList(clone, lenList(clone) - 1);
					// a. To make less comparisons, first we check if it goes after the last
					if (compareData(dataClone, last))
						pushList(clone, dataClone);
					else
					{ // b. Else, we traverse the cloned list and we insert it where appropriate
						List* lprev = newList();
						mergeLists(lprev, clone);
						List* lcurr = getRestList(lprev);

						bool keepGoing = true; // flag that'll help us traverse
						while (!emptyList(lcurr) && keepGoing)
						{
							void* prev = getHeadList(lprev);
							void* curr = getHeadList(lcurr);

							// We check if it goes before or after curr:
							if (prev == getHeadList(clone) && !compareData(dataClone, prev))
							{ // When it goes at the beginning:
								addList(clone, dataClone);
								keepGoing = false;
							}
							else if (compareData(dataClone, prev) && !compareData(dataClone, curr))
							{ // It goes before curr:
								if (!insertByHead(lprev, dataClone)) exit(1);
								keepGoing = false;
							}
							/*	If it comes later, we still don't know, since it could also come later
								from the next of curr, or from the next of that one, etc.
								Then we have to keep iterating until we find where it goes.
								Here we are always going to insert before the curr, and at most before the end,
								because the case when it goes after the end we already checked in item 4. a. */

							List* temp = lprev;
							lprev = lcurr;
							lcurr = getRestList(lcurr);
							delList(&temp, false, false, NULL);
						}
						delList(&lprev, false, false, NULL);
						delList(&lcurr, false, false, NULL);
					}
					break;
				}
				}
			}
			List* temp = aux;
			aux = getRestList(aux);
			delList(&temp, false, false, NULL);
		}
		delList(&aux, false, false, NULL);
		if (emptyList(clone)) exit(1);
	}
	return clone;
}

void* findList(List* self, void* key, bool (*matchData)(void*, void*))
{
	void* target = NULL;

	if (!emptyList(self))
	{
		List* aux = newList();
		mergeLists(aux, self);

		bool found = false;
		while (!(emptyList(aux) || found))
		{
			if (matchData(key, getHeadList(aux)))
			{
				target = getHeadList(aux);
				found = true;
			}

			List* temp = aux;
			aux = getRestList(aux);
			delList(&temp, false, false, NULL);
		}
		delList(&aux, false, false, NULL);
	}

	return target;
}


#endif // !_CRT_SECURE_NO_WARNINGS