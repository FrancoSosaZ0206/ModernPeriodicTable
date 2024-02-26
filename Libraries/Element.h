#ifndef ELEMENT_H_INCLUDED
#define ELEMENT_H_INCLUDED

// Definitions

typedef struct Element Element;

typedef enum elemType
{
	NobleGases,
	AlkaliMetals,
	AlkaliEarthMetals,
	TransitionMetals,
	Semimetals,
	NonMetals,
	OtherMetals,
	Lanthanides,
	Actinides,
	Halogens,
	Antigens
} elemType;

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
					elemType, elemState // of aggregation
				   );

void delElement(Element**);


// Setters

void setElementGroup	(Element*, int);
void setElementPeriod	(Element*, int);
void setElementName		(Element*, char*);
void setElementSymbol	(Element*, char[4]);
void setElementAtomicNum(Element*, int);
void setElementMass		(Element*, float);
void setElementType		(Element*, elemType);
void setElementState	(Element*, elemState);

// Getters

int			getElementGroup		(Element*);
int			getElementPeriod	(Element*);
char*		getElementName		(Element*);
char*		getElementSymbol	(Element*);
int			getElementAtomicNum	(Element*);
float		getElementMass		(Element*);
elemType	getElementType		(Element*);
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



#endif // !ELEMENT_H_INCLUDED