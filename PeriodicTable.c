#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "PeriodicTable.h"

// PRIVATE

bool compareElements(Element* thisElem, Element* thatElem)
{
	return getElementAtomicNum(thisElem) <= getElementAtomicNum(thatElem);
}

bool matchElementName(char* name, Element* elem)
{
	return strcmp(name, getElementName(elem)) == 0;
}
bool matchElementSymbol(char symbol[3], Element* elem)
{
	return strcmp(symbol, getElementSymbol(elem)) == 0;
}
bool matchElementAtomicNum(int* atomicNum, Element* elem)
{
	return *atomicNum == getElementAtomicNum(elem);
}
bool matchElementMass(int* mass, Element* elem)
{
	return *mass == getElementMass(elem);
}
bool matchElementType(elemType* type, Element* elem)
{
	return *type == getElementType(elem);
}
bool matchElementState(elemState* state, Element* elem)
{
	return *state == getElementState(elem);
}

// PUBLIC

Ptable* newPtable()
{
	return newList();
}
void delPtable(Ptable** self)
{
	delList(self, true);
}

bool savePtable(Ptable** self, char* path, bool deleteTable)
{
	bool result = false;
	if (path && strlen(path) > 0 &&
		*self && !emptyList(*self))
	{
		FILE* file = NULL;
		file = fopen(path, "r");
		if (file) // file exists
			fclose(file);

		file = fopen(path, "w");
		if (!file) exit(1);

		List* aux = newList();
		mergeLists(aux, *self);

		for (int i = 0; !emptyList(aux); i++)
		{
			fprintf(file, "%d. ", i + 1);
			serializeElement(getHeadList(aux), file);
			fprintf(file, ".....................................\n\n");

			List* temp = aux;
			aux = getRestList(aux);
			delList(&temp, false);
		}
		fprintf(file, "*****************************************\n\n");
		delList(&aux, false);

		fclose(file);

		if(deleteTable)
			delPtable(self);
	}
	return result;
}
Ptable* loadPtable(char* path)
{
	Ptable* loaded = NULL;
	if (path && strlen(path) > 0)
	{
		FILE* file = NULL;
		file = fopen(path, "r");

		if (file)
		{
			loaded = newPtable();
			while (!feof(file))
			{
				int i = 0;
				fscanf(file, "%d. ", &i);

				Element* loadedElem = deserializeElement(file);
				if (!loadedElem) exit(1);
				pushList(loaded, loadedElem);

				fscanf(file, ".....................................\n\n");
			}
			fscanf(file, "*****************************************\n\n");

			fclose(file);
		}
	}
	return loaded;
}

bool addElement(Ptable* self, Element* elem)
{
	return addOrderedList(self, elem, compareElements);
}
Element* removeElement(Ptable* self, int atomicNum)
{
	return removeOrderedList(self, &atomicNum, matchElementAtomicNum);
}

Element* getElement(Ptable* self, int pos)
{
	return getDataList(self, pos);
}
Element* findElement(Ptable* self, elemAttribute attr, void* attrValue)
{
	Element* targetElem = NULL;

	if (self && !emptyList(self))
	{
		switch (attr)
		{
		case Name:
			targetElem = findList(self, attrValue, matchElementName);
			break;
		case Symbol:
			targetElem = findList(self, attrValue, matchElementSymbol);
			break;
		case AtomicNum:
			targetElem = findList(self, attrValue, matchElementAtomicNum);
			break;
		case Mass:
			targetElem = findList(self, attrValue, matchElementMass);
			break;
		case Type:
			targetElem = findList(self, attrValue, matchElementType);
			break;
		case State:
			targetElem = findList(self, attrValue, matchElementState);
			break;
		default:
			exit(1);
			break;
		}
	}

	return targetElem;
}

void showPtable(Ptable* self)
{
	showList(self, showElement);
}
void showElements(Ptable* self, unsigned int elemCount, ...)
{
	if (self && !emptyList(self))
	{
		va_list elems;
		// each elem. attribute goes with its respective elemAttribute:
		va_start(elems, elemCount * 2);

		for (int i = 0; i < elemCount; i++)
		{
			Element* elem = findElement(self,	va_arg(elems, elemAttribute),
												va_arg(elems, void*));

			printf("Element %d %s", i + 1, elem ? "(found): " :
												  "(not found)\n\n");
			if (elem) showElement(elem);
			printf(".....................................\n\n");
		}
		printf("*****************************************\n\n");
		va_end(elems);
	}
}


#endif // !_CRT_SECURE_NO_WARNINGS