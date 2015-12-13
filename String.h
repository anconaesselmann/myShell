#ifndef STRING_H
#define STRING_H

// #include <stdio.h>
// #include <stdlib.h>

typedef struct {
    long length;
    char *cString;

} String;

long cStringLength(const char *argv);
/**
 * Creates a new cString with the exact lenth of the previous string.
 * Allocates memory.
 * @param  original    A cString
 * @param  destination a char pointer not pointing to anything
 */
long copyCString(const char *original, char **destination);
String *newString(const char _cString[]);

void deleteString(String *str);

int strEqual(String *str1, String *str2);

double cStrToDouble(const char *cString);
long cStrToLong(const char *cString);
int unsigned cStrHexToBinary(const char *cString);


#endif
