#ifndef ELEMENT_H_INCLUDED
#define ELEMENT_H_INCLUDED

// Definitions

typedef struct Element Element;

// Element categories:
typedef enum majorCtg
{
	Metals,
	NonMetals,
	Metalloids,
	UNKNOWN
} majorCtg;
typedef enum minorCtg
{
	Alkali,
	AlkaliEarth,
	Transition,
	PostTransition,
	Halogens,
	NobleGases,
	Lanthanides,
	Actinides
} minorCtg;

// Element states of aggregation:
typedef enum elemState
{
	Gas,
	Liquid,
	Solid,
	Synthetic
} elemState;


/// FUNCTIONS

// Constructor/Destructor

Element* newElement(int group, int period,
					char* name, char symbol[4],
					int atomicNum, float mass,
					majorCtg, minorCtg, // ctg = category
					elemState // of aggregation
				   );

void delElement(Element**);


// Setters

void setElementGroup	(Element*, int);
void setElementPeriod	(Element*, int);
void setElementName		(Element*, char*);
void setElementSymbol	(Element*, char[4]);
void setElementAtomicNum(Element*, int);
void setElementMass		(Element*, float);
void setElementMajorCtg(Element*, majorCtg);
void setElementMinorCtg(Element*, minorCtg);
void setElementState	(Element*, elemState);

// Getters

int			getElementGroup		(Element*);
int			getElementPeriod	(Element*);
char*		getElementName		(Element*);
char*		getElementSymbol	(Element*);
int			getElementAtomicNum	(Element*);
float		getElementMass		(Element*);
majorCtg	getElementMajorCtg	(Element*);
minorCtg	getElementMinorCtg	(Element*);
elemState	getElementState		(Element*);

// Printing

void showElement_Test(Element*);
void showElement(Element*);

// Others

char* elementToString(Element*);

// Assumes file exists and is already open in write mode
void serializeElement(Element*, FILE*);
// Assumes file exists and is already open in read mode
Element* deserializeElement(FILE*);

/* Modes:
	1. Shows all categories.
	2. Major categories only.
	3. Minor categories only. */
void showElementCategories(int mode);
void showElementStates();

void elementCategories_Menu();
void elementStates_Menu();


#endif // !ELEMENT_H_INCLUDED