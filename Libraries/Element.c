#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Element.h"


// Definitions

typedef struct Element
{
	int group;
	int period;
	char* name;
	char symbol[3];
	int atomicNum;
	float mass;
	elemType type;
	elemState state;
}
Element;

const char* typeStr[] =
{
	"Noble Gases",
	"Alkali Metals",
	"Alkali Earth Metals",
	"Transition Metals",
	"Semimetals",
	"Non-Metals",
	"Other Metals",
	"Lanthanides",
	"Actinides",
	"Halogens",
	"Antigens"
};

const char* stateStr[] = { "Gas", "Liquid", "Solid", "Synthetic" };

const char* ELEMENT_FORMAT_OUT =
"Element:\n"
"\tGroup: %d\n"
"\tPeriod: %d\n"
"\tName: %s\n"
"\tSymbol: %s\n"
"\tAtomic Number: %d\n"
"\tAtomic Mass: %f\n"
"\tType: %d (%s)\n"
"\tState: %d (%s)\n\n";

const char* ELEMENT_FORMAT_IN =
"Element:\n"
"\tGroup: %d\n"
"\tPeriod: %d\n"
"\tName: %[^\n]\n"
"\tSymbol: %[^\n]\n"
"\tAtomic Number: %d\n"
"\tAtomic Mass: %f\n"
"\tType: %d (%[^)])\n"
"\tState: %d (%[^)])";

const char* ELEMENT_FORMAT_OUT_SHORT =
"%s (%s)\n"
"(%d, %d)\n"
"Atomic Number: %d\n"
"Atomic Mass: %f\n"
"#%s, #%s\n\n";

/// FUNCTIONS

// Constructor/Destructor

Element* newElement(int group, int period, 
					char* name, char symbol[3],
					int atomicNum, float mass,
					elemType type, elemState state)
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
		self->type = type;
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
void setElementSymbol(Element* self, char symbol[3])
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
void setElementType(Element* self, elemType type)
{
	self->type = type;
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
elemType getElementType(Element* self)
{
	return self->type;
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
		self->type, typeStr[self->type],
		self->state, stateStr[self->state]);
}
void showElement(Element* self)
{
	printf(ELEMENT_FORMAT_OUT_SHORT, self->symbol, self->name,
			self->group, self->period,
			self->atomicNum, self->mass,
			typeStr[self->type], stateStr[self->state]);
}

// Others

char* elementToString(Element* self)
{
	char buffer[500] = "";
	char* dest = NULL;

	sprintf(buffer, ELEMENT_FORMAT_OUT, self->group, self->period,
		self->name, self->symbol,
		self->atomicNum, self->mass,
		self->type, typeStr[self->type],
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
		self->type, typeStr[self->type],
		self->state, stateStr[self->state]);
}
Element* deserializeElement(FILE* file)
{
	Element* deserialized = NULL;

	int groupBuffer = -1;
	int periodBuffer = -1;
	char nameBuffer[50] = "";
	char symbolBuffer[3] = "";
	int atomicNumBuffer = -1;
	float massBuffer = -1.0f;
	elemType typeBuffer = -1;
	elemState stateBuffer = -1;

	char dummyStr[100] = ""; // for the type and state strings
	char dummyStr2[100] = ""; // for the type and state strings

	// only if it could successfuly deserialize the element and store its attributes in each variable,
	if(fscanf(file, ELEMENT_FORMAT_IN, &groupBuffer, &periodBuffer,
									   nameBuffer, symbolBuffer,
									   &atomicNumBuffer, &massBuffer,
									   &typeBuffer, dummyStr, &stateBuffer, dummyStr2))
		// we load it in memory
		deserialized = newElement(groupBuffer, periodBuffer,
								  nameBuffer, symbolBuffer,
								  atomicNumBuffer, massBuffer,
								  typeBuffer, stateBuffer);

	return deserialized;
}


#endif // !_CRT_SECURE_NO_WARNINGS