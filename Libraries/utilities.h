#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

typedef char* string;

void* myMalloc(size_t size, size_t count);
void* myCalloc(size_t size, size_t count);
void* myRealloc(void* variable, size_t size, size_t count);

string dynamicString(string literal);
void myStrcpy(string* dest, string src);
void myStrcat(string* dest, string src);

// Clears the input buffer. Use it after taking user imput (i.e. scanf, getchar, etc.).
void clrBuffer();
// Pauses the program and shows "Press enter to continue" until the user presses enter.
void promptEnter();

#endif // !UTILITIES_H_INCLUDED
