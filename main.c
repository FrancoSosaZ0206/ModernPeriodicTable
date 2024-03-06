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
	int op[5] = { -1, -1, -1, -1, -1};

	do
	{
		system("cls");
		printf("         -------------------\n");
		printf("       ***********************\n");
		printf("        Modern Periodic Table\n");
		printf("       ***********************\n");
		printf("         -------------------\n\n\n\n");
		printMenu("\tMAIN MENU", true, 2,
			"Create new table",
			"Load existing table");

		scanf("%d", &op[0]);
		clrBuffer();
		system("cls");

		switch (op[0])
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
				char path[500] = "";

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
				printf("Incorrect option.");
				promptEnter();
				break;
			}
		}

		if (op[0] != 0 && table)
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

				scanf("%d", &op[1]);
				clrBuffer();
				system("cls");

				switch (op[1])
				{
					case 1:
					{
						int group = 0,
							period = 0;
						char nameBuffer[50] = "";
						char symbolBuffer[4] = "";
						int atomicNum = 0;
						float mass = 0.0f;
						unsigned int elemCtg = 0;
						majorCtg major = -1;
						minorCtg minor = -1;
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

						printf("\n\nSelect the category of the new element:\n");
						elementCategories_Menu();
						do
						{
							scanf("%u", &elemCtg);
							clrBuffer();
						} while (elemCtg < 1 || elemCtg > 10);

						// We'll also assign states in some cases. Can be changed in "Find Element" menu.
						switch (elemCtg)
						{
							case 1:
							{
								major = Metalloids;
								break;
							}
							case 2:
							{
								major = Metals;
								minor = Alkali;
								break;
							}
							case 3:
							{
								major = Metals;
								minor = AlkaliEarth;
								break;
							}
							case 4:
							{
								major = Metals;
								minor = Transition;
								break;
							}
							case 5:
							{
								major = Metals;
								minor = PostTransition;
								break;
							}
							case 6:
							{
								major = NonMetals;
								minor = Halogens;
								eState = Gas;
								break;
							}
							case 7:
							{
								major = NonMetals;
								minor = NobleGases;
								break;
							}
							case 8:
							{
								major = Metals;
								minor = Lanthanides;
								eState = Solid;
								break;
							}
							case 9:
							{
								major = Metals;
								minor = Actinides;
								eState = Solid;
								break;
							}
							case 10:
							{
								major = UNKNOWN;
								break;
							}
						}

						if (eState != -1)
						{
							printf("\n\nSelect the aggregation state of the new element:\n");
							elementStates_Menu();
							do
							{
								scanf("%d", &eStateOp);
								clrBuffer();
							} while (eStateOp < 1 || eStateOp > 4);
							eState = eStateOp - 1;
						}

						Element* newElem = newElement(group, period, nameBuffer, symbolBuffer, atomicNum, mass, major, minor, eState);
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
					case 3:
					{
						do
						{
							system("cls");

							printf("(*): Go to 'Table Management' -> 'Show Table' to see it.\n\n");

							printMenu("FIND ELEMENT", false, 8,
								"By name",
								"By chemical symbol",
								"By atomic number",
								"By atomic mass",
								"By major category",
								"By minor category",
								"By state of aggregation",
								"By index (*)");
							scanf("%d", &op[2]);
							clrBuffer();
							system("cls");

							Element* found = NULL;
							switch (op[2])
							{
								case 1:
								{
									char name[50] = "";
									printf("FIND ELEMENT BY NAME\n\n");
									printf("Insert target element's name: ");
									scanf("%[^\n]", name);
									clrBuffer();
									found = findElement(table, Name, name);
									break;
								}
								case 2:
								{
									char symbol[4] = "";
									printf("FIND ELEMENT BY CHEMICAL SYMBOL\n\n");
									printf("Insert target element's chemical symbol: ");
									scanf("%s", symbol);
									clrBuffer();
									found = findElement(table, Symbol, symbol);
									break;
								}
								case 3:
								{
									int atomicNum = 0;
									printf("FIND ELEMENT BY ATOMIC NUMBER\n\n");
									printf("Insert target element's atomic number: ");
									scanf("%d", &atomicNum);
									clrBuffer();
									found = findElement(table, AtomicNum, &atomicNum);
									break;
								}
								case 4:
								{
									float mass = 0.0f;
									printf("FIND ELEMENT BY ATOMIC MASS\n\n");
									printf("Insert target element's atomic mass: ");
									scanf("%f", &mass);
									clrBuffer();
									found = findElement(table, Mass, &mass);
									break;
								}
								case 5:
								{
									majorCtg major = -1;
									printf("FIND ELEMENT BY MAJOR CATEGORY\n\n");
									showElementCategories(2);
									printf("Insert target element's major category: ");
									scanf("%d", &major);
									clrBuffer();
									found = findElement(table, MajorCtg, &major);
									break;
								}
								case 6:
								{
									minorCtg minor = -1;
									printf("FIND ELEMENT BY MINOR CATEGORY\n\n");
									showElementCategories(3);
									printf("NONE ............. -1\n");
									printf("**************************\n\n");

									printf("Insert target element's minor category: ");
									scanf("%d", &minor);
									clrBuffer();
									found = findElement(table, MinorCtg, &minor);
									break;
								}
								case 7:
								{
									elemState eState = -1;
									printf("FIND ELEMENT BY STATE OF AGGREGATION\n\n");
									showElementStates();
									printf("Insert target element's state of aggregation: ");
									scanf("%d", &eState);
									clrBuffer();
									found = findElement(table, State, &eState);
									break;
								}
								case 8:
								{
									int index = 0;
									printf("FIND ELEMENT BY INDEX (INTERNAL)\n\n");
									printf("Insert target element's internal index: ");
									scanf("%d", &index);
									clrBuffer();
									found = getElement(table, index);
									break;
								}
								case 0:
								{
									break;
								}
								default:
								{
									printf("Incorrect option.");
									promptEnter();
									break;
								}
							}

							if (op[2] > 0 && op[2] <= 7)
							{
								if (!found)
								{
									printf("Element couldn't be found.");
									promptEnter();
								}
								else
								{
									printf("Element found!\n\n");
									do
									{
										system("cls");
										showElement(found);
										printMenu("ACTIONS", false, 10,
											"Edit group",
											"Edit period",
											"Edit name",
											"Edit symbol",
											"Edit atomic number",
											"Edit atomic mass",
											"Edit major category",
											"Edit minor category",
											"Edit state of aggregation",
											"Remove element from table");
										scanf("%d", &op[4]);
										clrBuffer();
										system("cls");

										showElement(found);
										switch (op[4])
										{
											case 1:
											{
												int newGroup = 0;
												printf("Insert new group: ");
												scanf("%d", &newGroup);
												clrBuffer();
												setElementGroup(found, newGroup);
												printf("\n\nElement group edited successfully.");
												promptEnter();
												break;
											}
											case 2:
											{
												int newPeriod = 0;
												printf("Insert new period: ");
												scanf("%d", &newPeriod);
												clrBuffer();
												setElementPeriod(found, newPeriod);
												printf("\n\nElement period edited successfully.");
												promptEnter();
												break;
											}
											case 3:
											{
												char newName[50] = "";
												printf("Insert new name: ");
												scanf("%[^\n]", newName);
												clrBuffer();
												setElementName(found, newName);
												printf("\n\nElement name edited successfully.");
												promptEnter();
												break;
											}
											case 4:
											{
												char newSymbol[4] = "";
												printf("Insert new symbol (3 characters max): ");
												scanf("%[^\n]", newSymbol);
												clrBuffer();
												setElementSymbol(found, newSymbol);
												printf("\n\nElement symbol edited successfully.");
												promptEnter();
												break;
											}
											case 5:
											{
												int newAtomicNum = 0;
												printf("Insert new atomic number: ");
												scanf("%d", &newAtomicNum);
												clrBuffer();
												setElementAtomicNum(found, newAtomicNum);
												printf("\n\nElement atomic number edited successfully.");
												promptEnter();
												break;
											}
											case 6:
											{
												float newMass = 0.0f;
												printf("Insert new atomic mass: ");
												scanf("%f", &newMass);
												clrBuffer();
												setElementMass(found, newMass);
												printf("\n\nElement atomic mass edited successfully.");
												promptEnter();
												break;
											}
											case 7:
											{
												majorCtg newMajor = -1;
												int newMajorOp = -1;

												do
												{
													showElementCategories(2);
													printf("Select new major category: ");
													scanf("%d", &newMajorOp);
													clrBuffer();
													system("cls");
												} while (newMajorOp < 0 || newMajorOp > 10);

												newMajor = newMajorOp - 1;
												setElementMajorCtg(found, newMajor);
												printf("\n\nElement major category edited successfully.");
												promptEnter();

												break;
											}
											case 8:
											{
												minorCtg newMinor = -1;
												int newMinorOp = -1;

												do
												{
													showElementCategories(3);
													printf("NONE ............. -1\n");
													printf("**************************\n\n");
													printf("Select new minor category: ");
													scanf("%d", &newMinorOp);
													clrBuffer();
													system("cls");
												} while (newMinorOp < 0 || newMinorOp > 10);

												newMinor = newMinorOp - 1;
												setElementMinorCtg(found, newMinor);
												printf("\n\nElement minor category edited successfully.");
												promptEnter();

												break;
											}
											case 9:
											{
												elemState newEstate = -1;
												int eStateOp = -1;

												do
												{
													showElementStates();
													printf("Select new state of aggregation: ");
													scanf("%d", &eStateOp);
													clrBuffer();
													system("cls");
												} while (eStateOp < 0 || eStateOp > 4);

												newEstate = eStateOp - 1;
												setElementState(found, newEstate);
												printf("\n\nElement's state of aggregation edited successfully.");
												promptEnter();

												break;
											}
											case 10:
											{
												bool confirm = false;
												int confirmOp = -1;
												printf("Are you sure you want to remove element from table?\n");
												printf("YES >>> select '1'\n");
												printf("NO >>> select '0'");
												do
												{
													printf("\n\nSelect an option: ");
													scanf("%d", &confirmOp);
													clrBuffer();
												} while (confirmOp != 1 && confirmOp != 0);
												confirm = confirmOp;

												if (confirm)
												{
													Element* removed = removeElement(table, getElementAtomicNum(found));
													if (removed && removed == found)
													{
														delElement(&removed);
														found = NULL;
														printf("Element removed successfully.");
														promptEnter();
														op[4] = 0; // we can't keep editing a deleted element, so we go back to the previous menu.
													}
													else
													{
														printf("ERROR: element couldn't be removed.");
														exit(1);
													}
												}
												break;
											}
											case 0:
											{
												break;
											}
											default:
											{
												printf("Incorrect option.");
												promptEnter();
												break;
											}
										}
									} while (op[4] != 0);
								}
							}
						} while (op[2] != 0);
						break;
					}
					case 4:
					{
						Ptable* selected = newPtable();
						bool keepSelecting = false;

						do
						{
							int keepSelectingOp = -1;

							system("cls");

							printf("(*): Go to 'Table Management' -> 'Show Table' to see it.\n\n");

							printMenu("SELECT ELEMENT", false, 8,
								"By name",
								"By chemical symbol",
								"By atomic number",
								"By atomic mass",
								"By major category",
								"By minor category",
								"By state of aggregation",
								"By index (*)");
							scanf("%d", &op[2]);
							clrBuffer();
							system("cls");

							Element* found = NULL;
							switch (op[2])
							{
								case 1:
								{
									char name[50] = "";
									printf("SELECT ELEMENT BY NAME\n\n");
									printf("Insert target element's name: ");
									scanf("%[^\n]", name);
									clrBuffer();
									found = findElement(table, Name, name);
									break;
								}
								case 2:
								{
									char symbol[4] = "";
									printf("SELECT ELEMENT BY CHEMICAL SYMBOL\n\n");
									printf("Insert target element's chemical symbol: ");
									scanf("%s", symbol);
									clrBuffer();
									found = findElement(table, Symbol, symbol);
									break;
								}
								case 3:
								{
									int atomicNum = 0;
									printf("SELECT ELEMENT BY ATOMIC NUMBER\n\n");
									printf("Insert target element's atomic number: ");
									scanf("%d", &atomicNum);
									clrBuffer();
									found = findElement(table, AtomicNum, &atomicNum);
									break;
								}
								case 4:
								{
									float mass = 0.0f;
									printf("SELECT ELEMENT BY ATOMIC MASS\n\n");
									printf("Insert target element's atomic mass: ");
									scanf("%f", &mass);
									clrBuffer();
									found = findElement(table, Mass, &mass);
									break;
								}
								case 5:
								{
									majorCtg major = -1;
									printf("SELECT ELEMENT BY MAJOR CATEGORY\n\n");
									showElementCategories(2);
									printf("Insert target element's major category: ");
									scanf("%d", &major);
									clrBuffer();
									found = findElement(table, MajorCtg, &major);
									break;
								}
								case 6:
								{
									minorCtg minor = -1;
									printf("SELECT ELEMENT BY MINOR CATEGORY\n\n");
									showElementCategories(3);
									printf("NONE ............. -1\n");
									printf("**************************\n\n");

									printf("Insert target element's minor category: ");
									scanf("%d", &minor);
									clrBuffer();
									found = findElement(table, MinorCtg, &minor);
									break;
								}
								case 7:
								{
									elemState eState = -1;
									printf("SELECT ELEMENT BY STATE OF AGGREGATION\n\n");
									showElementStates();
									printf("Insert target element's state of aggregation: ");
									scanf("%d", &eState);
									clrBuffer();
									found = findElement(table, State, &eState);
									break;
								}
								case 8:
								{
									int index = 0;
									printf("SELECT ELEMENT BY INDEX (INTERNAL)\n\n");
									printf("Insert target element's internal index: ");
									scanf("%d", &index);
									clrBuffer();
									found = getElement(table, index);
									break;
								}
								case 0:
								{
									if (!emptyList(selected))
									{
										bool confirm = false;
										int confirmOp = -1;
										printf("Are you sure you want to go back to the previous menu?\n");
										printf("Your selection will be lost.\n");
										printf("YES >>> select '1'\n");
										printf("NO >>> select '0'");
										do
										{
											printf("\n\nSelect an option: ");
											scanf("%d", &confirmOp);
											clrBuffer();
										} while (confirmOp != 1 && confirmOp != 0);
										confirm = confirmOp;

										if (confirm)
											delPtable(&selected, false);
										else
											op[2] = -1;
									}
									break;
								}
								default:
								{
									printf("Incorrect option.");
									promptEnter();
									break;
								}
							}

							if (op[2] > 0 && op[2] <= 7)
							{
								if (!found)
									printf("Element couldn't be found.");
								else
								{
									pushList(selected, found);
									printf("Element found!");
								}
								promptEnter();

								if (selected)
								{
									printf("\n\nKeep selecting?\n");
									printf("YES >>> select '1'\n");
									printf("NO >>> select '0'");
									do
									{
										printf("\n\nSelect an option: ");
										scanf("%d", &keepSelectingOp);
										clrBuffer();
									} while (keepSelectingOp != 1 && keepSelectingOp != 0);
									keepSelecting = keepSelectingOp;
								}
							}
						} while (op[2] != 0 && keepSelecting);

						if (op[2] != 0 && selected)
						{
							system("cls");
							printf("Showing selected elements:\n\n");
							showPtable(selected);
							promptEnter();

							delPtable(&selected, false);
						}
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
						char path[500] = "";
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
						bool confirm = false;
						int confirmOp = -1;
						printf("Are you sure you want to go back to main menu?\n");
						printf("YES >>> select '1'\n");
						printf("NO >>> select '0'");
						do
						{
							printf("\n\nSelect an option: ");
							scanf("%d", &confirmOp);
							clrBuffer();
						} while (confirmOp != 1 && confirmOp != 0);
						confirm = confirmOp;

						if (!confirm)
							op[1] = -1;
						else
						{
							printf("Do you want to save before going back?\n");
							printf("YES >>> select '1'\n");
							printf("NO >>> select '0'");
							do
							{
								printf("\n\nSelect an option: ");
								scanf("%d", &op[1]);
								clrBuffer();
							} while (op[1] != 1 && op[1] != 0);

							if (op[1] == 1)
							{ // same as case 7
								char path[500] = "";
								printf("Insert absolute path to file: ");
								scanf("%[^\n]", path);
								clrBuffer();
								printf("%s.\n", savePtable(&table, path, false, false) ?
									"Table saved successfully" :
									"ERROR: table couldn't be saved");
								promptEnter();
								op[1] = 0;
							}
						}

						break;
					}
					default:
					{
						printf("Incorrect option.");
						promptEnter();
						break;
					}
				}
			} while (op[1] != 0);
		}

	} while (op[0] != 0);

	delPtable(&table, true);

	return 0;
}


#endif // !_CRT_SECURE_NO_WARNINGS