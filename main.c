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
	/* TESTING ROUTINE 1
	
	Ptable* p1 = newPtable();

	Element* e1 = newElement(1, 1, "Hydrogen", "H", 1, 1.008f, NonMetals, Gas);
	Element* e2 = newElement(18, 1, "Helium", "He", 2, 4.0026f, NobleGases, Gas);
	Element* e3 = newElement(1, 2, "Lithium", "Li", 3, 6.94f, AlkaliMetals, Solid);
	Element* e4 = newElement(2, 2, "Beryllium", "Be", 4, 9.0122f, AlkaliEarthMetals, Solid);
	Element* e5 = newElement(8, 4, "Iron", "Fe", 26, 55.845f, TransitionMetals, Solid);
	Element* e6 = newElement(12, 6, "Mercury", "Hg", 80, 200.59f, TransitionMetals, Liquid);
	Element* e7 = newElement(3, 6, "Neodymium", "Nd", 60, 144.24f, Lanthanides, Solid);
	Element* e8 = newElement(3, 7, "Uranium", "U", 92, 238.03f, Actinides, Solid);

	addElement(p1, e1);
	addElement(p1, e2);
	addElement(p1, e3);
	addElement(p1, e4);
	addElement(p1, e5);
	addElement(p1, e6);
	addElement(p1, e7);
	addElement(p1, e8);

	printf("MY PERIODIC TABLE\n");
	printf("_________________\n\n");
	showPtable(p1);

	if(!savePtable(&p1, "Resources/Saved Files/PeriodicTable.txt", true, true)) exit(1); */

	/* TESTING ROUTINE 2
	Ptable* p1 = loadPtable("Resources/Saved Files/PeriodicTable.txt");
	if (!p1) exit(1);

	showPtable(p1);
	getchar("\n");
	fflush(stdin);
	system("cls");

	int atomicNum = ;

	printf("Removing element: (a.n. = %d)...\n\n", atomicNum);
	getchar("\n");
	fflush(stdin);
	system("cls");

	Element* removed = removeElement(p1, atomicNum);

	printf("%s\n\n", removed ? "Element removed successfully!" : "Couldn't remove element.");
	if (removed) showElement(removed);

	getchar("\n");
	fflush(stdin);
	system("cls");

	printf("Updated Ptable:\n\n");
	showPtable(p1);

	delPtable(&p1, true);
	if (removed) delElement(&removed);*/

	/* TESTING ROUTINE 3

	Ptable* p = NULL;
	char path[100] = "";

	printf("Welcome. Insert path to file to load ptable below:\n");
	scanf("%[^\n]%*c", path);
	fflush(stdin);

	p = loadPtable(path);
	system("cls");
	if (!p)
		printf("ERROR: the path is invalid or the file doesn't exist.");
	else
		printf("Periodic table loaded successfully.");
	getchar();
	system("cls");

	if (p)
	{
		showPtable(p);
		getchar();

		char symbol[4] = "Hg";
		printf("Searching element by symbol (%s)...\n\n", symbol);
		getchar();

		Element* found = findElement(p, Symbol, symbol);
		if (found)
		{
			printf("Element found!\n\n");
			showElement(found);
		}
		else printf("Element could not be found on the table.\n\n");

		getchar();
		system("cls");
		delPtable(&p, true);
	} */

	/* TESTING ROUTINE 4

	Ptable* p = loadPtable("Resources/Saved Files/PeriodicTable.txt");

	if (p)
	{
		printf("Showing full list:\n\n");
		showPtable(p);

		getchar();

		char symbolE1[4] = "H";
		float massE2 = 144.240005f;
		char nameE3[30] = "Lithium";
		printf("Showing attributes to search:\n\n");
		printf("Elem. 1 - Symbol = %s\n", symbolE1);
		printf("Elem. 2 - Atomic Mass = %f\n", massE2);
		printf("Elem. 3 - Name = %s\n\n", nameE3);

		getchar();

		printf("Showing element selection:\n\n");
		showElements(p, 3, Symbol, symbolE1, Mass, &massE2, Name, nameE3);

		delPtable(&p, true);
	} */

	return 0;
}


#endif // !_CRT_SECURE_NO_WARNINGS