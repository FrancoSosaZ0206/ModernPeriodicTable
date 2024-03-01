#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilities.h"

void* myMalloc(size_t size, size_t count)
{
	void* var = malloc(size * count);
	if (!var) exit(1);
	return var;
}
void* myCalloc(size_t size, size_t count)
{
	void* var = calloc(count, size);
	if (!var) exit(1);
	return var;
}
void* myRealloc(void* variable, size_t size, size_t count)
{
	variable = realloc(variable, count * size);
	if (variable == NULL) exit(1);
	return variable;
}

string dynamicString(string literal)
{
	string str = myCalloc(sizeof(char), strlen(literal) + 1);
	strcpy(str, literal);
	return str;
}
void myStrcpy(string* dest, string src)
{
	if (*dest && src)
	{
		*dest = myRealloc(*dest, sizeof(char), strlen(*dest) + strlen(src) + 1);
		strcpy(*dest, src);
	}
}
void myStrcat(string* dest, string src)
{
	if (*dest && src)
	{
		*dest = myRealloc(*dest, sizeof(char), strlen(*dest) + strlen(src) + 1);
		strcat(*dest, src);
	}
}

void clrBuffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
	{
		// Discard characters by reading them w/getchar()
		// Dischard characters == DO NOTHING
	}
}

void promptEnter()
{
	printf("\n\nPress enter to continue...\n\n");
	// Same as clrBuffer():
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
}


#endif // !_CRT_SECURE_NO_WARNINGS