#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED

#include <stdarg.h>
#include <stdbool.h>

/* Menu printing function (Generic function)
Prints menu title and options
MENU ACTIONS HAVE TO BE MANAGED EXTERNALLY.
title = string representing the title of the menu
isMainMenu = if it's a main menu, send true, else send false.
nOptions = the number of options of the menu
... = strings representing each option text. */
void printMenu(char* title, bool isMainMenu, unsigned int nOptions, ...);


#endif // !MENUS_H_INCLUDED