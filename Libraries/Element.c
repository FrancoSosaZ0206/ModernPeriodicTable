#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Element.h"


// Definitions

typedef struct elemCtg
{
	majorCtg major;
	minorCtg minor;
}
elemCtg; // ctg = category (metal, nonmetal, metalloid, halogen, etc.)

typedef struct Element
{
	int group;
	int period;
	char* name;
	char symbol[4];
	int atomicNum;
	float mass;
	elemCtg category;
	elemState state;
}
Element;

const char* majorCtgStr[] =
{
	"Metals",
	"Non-Metals",
	"Metalloids",
	"UNKNOWN"
};
const int majorCtgCount = 4;

const char* minorCtgStr[] =
{
	"Alkali",
	"AlkaliEarth",
	"Transition",
	"PostTransition",
	"Halogens",
	"NobleGases",
	"Lanthanides",
	"Actinides"
};
const int minorCtgCount = 8;

const char* stateStr[] = { "Gas", "Liquid", "Solid", "Synthetic" };
const int stateCount = 4;

const char* ELEMENT_FORMAT_OUT =
"Element:\n"
"\tGroup: %d\n"
"\tPeriod: %d\n"
"\tName: %s\n"
"\tSymbol: %s\n"
"\tAtomic Number: %d\n"
"\tAtomic Mass: %f\n"
"\tCategories:\n"
"\t\tMajor: %s (%d)\n"
"\t\tMinor: %s (%d)\n"
"\tState: %s (%d)\n\n";

const char* ELEMENT_FORMAT_IN =
"Element:\n"
"\tGroup: %d\n"
"\tPeriod: %d\n"
"\tName: %[^\n]\n"
"\tSymbol: %[^\n]\n"
"\tAtomic Number: %d\n"
"\tAtomic Mass: %f\n"
"\tCategories:\n"
"\t\tMajor: %[^(] (%d)\n"
"\t\tMinor: %[^(] (%d)\n"
"\tState: %[^(] (%d)\n\n";

const char* ELEMENT_FORMAT_OUT_SHORT =
"%s (%s)\n"
"(%d, %d)\n"
"Atomic Number: %d\n"
"Atomic Mass: %f\n"
"#%s, #%s\n"
"#%s\n\n";

/// FUNCTIONS

// Constructor/Destructor

Element* newElement(int group, int period, 
					char* name, char symbol[4],
					int atomicNum, float mass,
					majorCtg major, minorCtg minor,
					elemState state)
{
	Element* self = malloc(sizeof(Element));
	
	if (self)
	{
		self->group = group;
		self->period = period;

		self->name = malloc(sizeof(char) * strlen(name) + 1);
		if(self->name)
			strcpy(self->name, name);
		strcpy(self->symbol, symbol); // we don't need to malloc this one, since we know its length.

		self->atomicNum = atomicNum;
		self->mass = mass;

		self->category.major = major;
		self->category.minor = minor;

		self->state = state;
	}

	return self;
}

void delElement(Element** self)
{
	free((*self)->name);

	free(*self);
	*self = NULL;
}


// Setters

void setElementGroup(Element* self, int group)
{
	self->group = group;
}
void setElementPeriod(Element* self, int period)
{
	self->period = period;
}
void setElementName(Element* self, char* name)
{
	free(self->name);
	self->name = malloc(sizeof(char) * strlen(name) + 1);
	if(self->name)
		strcpy(self->name, name);
}
void setElementSymbol(Element* self, char symbol[4])
{
	strcpy(self->symbol, symbol);
}
void setElementAtomicNum(Element* self, int atomicNum)
{
	self->atomicNum = atomicNum;
}
void setElementMass(Element* self, float mass)
{
	self->mass = mass;
}
void setElementMajorCtg(Element* self, majorCtg major)
{
	self->category.major = major;
}
void setElementMinorCtg(Element* self, minorCtg minor)
{
	self->category.minor = minor;
}
void setElementState(Element* self, elemState state)
{
	self->state = state;
}

// Getters

int getElementGroup(Element* self)
{
	return self->group;
}
int getElementPeriod(Element* self)
{
	return self->period;
}
char* getElementName(Element* self)
{
	return self->name;
}
char* getElementSymbol(Element* self)
{
	return self->symbol;
}
int	getElementAtomicNum(Element* self)
{
	return self->atomicNum;
}
float getElementMass(Element* self)
{
	return self->mass;
}
majorCtg getElementMajorCtg(Element* self)
{
	return self->category.major;
}
minorCtg getElementMinorCtg(Element* self)
{
	return self->category.minor;
}
elemState getElementState(Element* self)
{
	return self->state;
}

// Printing

void showElement_Test(Element* self)
{
	printf(ELEMENT_FORMAT_OUT, self->group, self->period,
		self->name, self->symbol,
		self->atomicNum, self->mass,
		majorCtgStr[self->category.major], self->category.major,
		self->category.minor == -1 ? "[NONE]" : minorCtgStr[self->category.minor], self->category.minor,
		self->state, stateStr[self->state]);
}
void showElement(Element* self)
{
	printf(ELEMENT_FORMAT_OUT_SHORT, self->symbol, self->name,
			self->group, self->period,
			self->atomicNum, self->mass,
			majorCtgStr[self->category.major],
			self->category.minor == -1 ? "[NONE]" : minorCtgStr[self->category.minor],
			stateStr[self->state]);
}

// Others

char* elementToString(Element* self)
{
	char buffer[500] = "";
	char* dest = NULL;

	sprintf(buffer, ELEMENT_FORMAT_OUT, self->group, self->period,
		self->name, self->symbol,
		self->atomicNum, self->mass,
		majorCtgStr[self->category.major], self->category.major,
		self->category.minor == -1 ? "[NONE]" : minorCtgStr[self->category.minor], self->category.minor,
		self->state, stateStr[self->state]);

	dest = malloc(sizeof(char) * strlen(buffer) + 1);
	if(dest)
		strcpy(dest, buffer);
	return dest;
}

void serializeElement(Element* self, FILE* file)
{
	fprintf(file, ELEMENT_FORMAT_OUT, self->group, self->period,
		self->name, self->symbol,
		self->atomicNum, self->mass,
		majorCtgStr[self->category.major], self->category.major,
		self->category.minor == -1 ? "[NONE]" : minorCtgStr[self->category.minor], self->category.minor,
		stateStr[self->state], self->state);
}
Element* deserializeElement(FILE* file)
{
	Element* deserialized = NULL;

	int groupBuffer = -1;
	int periodBuffer = -1;
	char nameBuffer[50] = "";
	char symbolBuffer[4] = "";
	int atomicNumBuffer = -1;
	float massBuffer = -1.0f;
	majorCtg majorBuffer = -1;
	minorCtg minorBuffer = -1;
	elemState stateBuffer = -1;

	char majorStr[100] = ""; // for the type and state strings
	char minorStr[100] = ""; // for the type and state strings
	char stateStr[100] = ""; // for the type and state strings

	// only if it could successfuly deserialize the element and store its attributes in each variable,
	if(fscanf(file, ELEMENT_FORMAT_IN, &groupBuffer, &periodBuffer,
									   nameBuffer, symbolBuffer,
									   &atomicNumBuffer, &massBuffer,
									   majorStr, &majorBuffer,
									   minorStr, &majorBuffer,
									   stateStr, &stateBuffer))
		// we load it in memory
		deserialized = newElement(groupBuffer, periodBuffer,
								  nameBuffer, symbolBuffer,
								  atomicNumBuffer, massBuffer,
								  majorBuffer, minorBuffer,
								  stateBuffer);

	return deserialized;
}


void showElementCategories(int mode)
{
	if (mode < 1 || mode > 3) return;

	printf("ELEMENT CATEGORIES\n");
	printf("**************************\n\n");

	if (mode != 3)
	{
		printf("Major Categories:\n");
		printf("--------------------------\n\n");
		for (int i = 0; i < majorCtgCount; i++)
			printf("%s ............. %d\n", majorCtgStr[i], i + 1);
	}

	if (mode != 2)
	{
		printf("--------------------------\n\n");

		printf("Minor Categories:\n");
		printf("--------------------------\n\n");
		for (int i = 0; i < minorCtgCount; i++)
			printf("%s ............. %d\n", minorCtgStr[i], i + 1);
	}

	printf("**************************\n\n");
}
void showElementStates()
{
	printf("STATES OF AGGREGATION\n");
	printf("--------------------------\n\n");
	for (int i = 0; i < stateCount; i++)
		printf("%s ............. %d\n", stateStr[i], i + 1);
	printf("--------------------------\n\n");
}

void elementCategories_Menu()
{
	printf("**************************\n\n");

	printf("Element Categories:\n");
	printf("--------------------------\n\n");
	
	printf("Metalloids ............. select '1'\n");
	for (int i = 0; i < minorCtgCount; i++)
		printf("%s ............. select '%d'\n", minorCtgStr[i], i + 2);

	printf("--------------------------\n");
	printf("UNKNOWN ............. select '10'\n\n");
	printf("**************************\n\n");

	printf("Select an option: \n");
}
void elementStates_Menu()
{
	printf("--------------------------\n\n");
	for (int i = 0; i < stateCount; i++)
		printf("%s ............. select '%d'\n", stateStr[i], i + 1);
	printf("--------------------------\n\n");
	printf("Select an option: ");
}


#endif // !_CRT_SECURE_NO_WARNINGS