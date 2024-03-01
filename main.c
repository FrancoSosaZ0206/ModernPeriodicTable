#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Libraries/utilities.h"
#include "Libraries/Element.h"
#include "Libraries/PeriodicTable.h"
#include "Libraries/Menus.h"



int main()
{
	Ptable* table = NULL;
	int op = -1,
		op1 = -1;

	do
	{
		system("cls");
		printMenu("MAIN MENU", true, 2,
			"Create new table",
			"Load existing table");

		scanf("%d", &op);
		clrBuffer();
		system("cls");

		switch (op)
		{
			case 1:
			{
				if (!table)
				{
					table = newPtable();
					printf("New Table created.");
					promptEnter();
				}
				break;
			}
			case 2:
			{
				char path[100] = "";

				printf("Insert absolute path to file: ");
				scanf("%[^\n]", path);
				clrBuffer();

				table = loadPtable(path);
				printf("%s.\n", table ?
					"Table loaded successfully" :
					"ERROR: table couldn't be loaded");
				promptEnter();
				break;
			}
			case 0:
			{
				break;
			}
			default:
			{
				printf("Incorrect option.\n");
				promptEnter();
				break;
			}
		}

		if (op != 0 && table)
		{
			do
			{
				system("cls");
				printMenu("TABLE MANAGEMENT", false, 6,
					"Add element",
					"Remove element",
					"Find element",
					"Show elements",
					"Show table",
					"Save table to file");

				scanf("%d", &op1);
				clrBuffer();
				system("cls");

				switch (op1)
				{
					case 1:
					{
						int group = 0,
							period = 0;
						char nameBuffer[50] = "";
						char symbolBuffer[4] = "";
						int atomicNum = 0;
						float mass = 0.0f;
						elemType eType = -1;
						elemState eState = -1;

						int eTypeOp = -1,
							eStateOp = -1;

						printf("ADDING ELEMENT\n\n");
						printf("--------------------------\n\n");
						printf("Insert group and period\nGROUP, PERIOD >>> ");
						scanf("%d, %d", &group, &period);
						clrBuffer();

						printf("\n\nInsert name and chemical symbol (symbol = 3 characters max)\nNAME, SYMBOL >>> ");
						scanf("%[^,], %[^\n]", nameBuffer, symbolBuffer);
						clrBuffer();

						printf("\n\nInsert atomic number and mass\nATOMIC NUMBER, MASS >>> ");
						scanf("%d, %f", &atomicNum, &mass);
						clrBuffer();

						printf("\n\nSelect the type of the new element:\n");
						elementTypes_Menu();
						do
						{
							scanf("%d", &eTypeOp);
							clrBuffer();
						} while (eTypeOp < 1 || eTypeOp > 11);
						eType = eTypeOp - 1;

						printf("\n\nSelect the aggregation state of the new element:\n");
						elementStates_Menu();
						do
						{
							scanf("%d", &eStateOp);
							clrBuffer();
						} while (eStateOp < 1 || eStateOp > 4);
						eState = eStateOp - 1;

						Element* newElem = newElement(group, period, nameBuffer, symbolBuffer, atomicNum, mass, eType, eState);
						if (!addElement(table, newElem)) exit(1);
						system("cls");
						printf("Element added successfully.");
						promptEnter();

						break;
					}
					case 2:
					{
						int atomicNum = 0;

						printf("REMOVING ELEMENT\n\n");
						printf("Insert atomic number of the element to remove: ");
						scanf("%d", &atomicNum);
						clrBuffer();

						Element* removed = removeElement(table, atomicNum);

						if (removed)
						{
							printf("Element:\n\n");
							showElement(removed);
							printf("Removed successfully.");
							delElement(&removed);
						}
						else
							printf("Element couldn't be removed.");

						promptEnter();
						break;
					}
					case 5:
					{
						printf("SHOWING FULL TABLE:\n\n");
						showPtable(table);
						promptEnter();
						break;
					}
					case 6:
					{
						char path[100] = "";
						printf("Insert absolute path to file: ");
						scanf("%[^\n]", path);
						clrBuffer();
						printf("%s.\n", savePtable(&table, path, false, false) ?
							"Table saved successfully" :
							"ERROR: table couldn't be saved");
						promptEnter();
						break;
					}
					case 0: // confirmation submenu:
					{
						printf("Do you want to save before going back?\n");
						printf("-1 >>> YES\n");
						printf("0 >>> NO\n\n");
						printf("Select an option: ");
						do
						{
							scanf("%d", &op1);
							clrBuffer();
						} while (op1 != -1 && op1 != 0);

						if (op1 == -1)
						{ // same as case 7
							char path[100] = "";
							printf("Insert absolute path to file: ");
							scanf("%[^\n]", path);
							clrBuffer();
							printf("%s.\n", savePtable(&table, path, false, false) ?
								"Table saved successfully" :
								"ERROR: table couldn't be saved");
							promptEnter();
							op1 = 0;
						}

						break;
					}
					default:
					{
						printf("Incorrect option.\n");
						promptEnter();
						break;
					}
				}
			} while (op1 != 0);
		}

	} while (op != 0);

	delPtable(&table, true);

	return 0;
}


#endif // !_CRT_SECURE_NO_WARNINGS