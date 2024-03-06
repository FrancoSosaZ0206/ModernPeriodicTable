#include <stdio.h>
#include "Menus.h"

void printMenu(char* title, bool isMainMenu, unsigned int nOptions, ...)
{
	if (title)
	{
		printf("%s\n", title);
		printf("--------------------------\n\n");

		va_list args;
		va_start(args, nOptions);

		for (unsigned int i = 0; i < nOptions; i++)
		{
			char* optionStr = va_arg(args, char*);
			printf("%s ............. select '%d'\n", optionStr, i + 1);
		}

		va_end(args);

		printf("%s ............. select '0'\n", isMainMenu ? "EXIT" : "BACK");
		printf("--------------------------\n\n");
		printf("Select an option: ");
	}
}