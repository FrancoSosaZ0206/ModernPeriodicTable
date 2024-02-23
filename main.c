#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Libraries/utilities.h"
#include "Libraries/Element.h"
#include "Libraries/PeriodicTable.h"

int main()
{
	Ptable* p1 = newPtable();
	Element* e1 = newElement(1, 1, "Hydrogen", "H", 1, 1.008f, NonMetals, Gas);
	
	if (!(p1 && e1))
		fprintf(stderr, "ERROR: table and/or element could not be created.\n\n");
	
	if(!addElement(p1, e1))
		fprintf(stderr, "ERROR: fail to add element to table.\n\n");
	else
	{
		printf("MY PERIODIC TABLE\n");
		printf("_________________\n\n");
		showPtable(p1);
	}


	delPtable(&p1);
	delElement(&e1);

	return 0;
}


#endif // !_CRT_SECURE_NO_WARNINGS