#include <stdio.h>
#include <stdlib.h>
#include "String.h"

long cStringLength(const char *argv) {
    long pos = 0;
    char current;
    while (pos += 1) {
        current = *(argv + pos);
        if (current == 0) break;
    }
    return pos;
}
/**
 * Creates a new cString with the exact lenth of the previous string.
 * Allocates memory.
 * @param  original    A cString
 * @param  destination a char pointer not pointing to anything
 */
long copyCString(const char *original, char **destination) {
    long strLen  = cStringLength(original);
    *destination = calloc(strLen + 1, sizeof(char));
    char current;
    for (long i = 0; i < strLen; i++) {
        current             = *(original + i);
        *(*destination + i) = current;
    }
    *(*destination + strLen) = 0;
    return strLen;
}
String *newString(const char _cString[]) {
    String *str = malloc(sizeof(String));
    str->length = copyCString(_cString, &str->cString);
    return str;
}

void deleteString(String *str) {
    free(str->cString);
    free(str);
}

int strEqual(String *str1, String *str2) {
    char c1, c2;
    int pos = 0;
    while (1) {
        c1 = *(str1->cString + pos);
        c2 = *(str2->cString + pos);
        pos += 1;
        if (c1 == 0 || c2 == 0) {
            if (c1 == 0 && c2 == 0) return 1;
            if (c1 == 0 && c2 != 0) return 0;
            if (c2 == 0 && c1 != 0) return 0;
        }
        if (c1 != c2) return 0;
    }
    return 1;
}

double cStrToDouble(const char *cString) {
    double result;
    sscanf(cString,"%lf",&result);
    return result;
}
long cStrToLong(const char *cString) {
    long result;
    sscanf(cString,"%lu",&result);
    return result;
}
int unsigned cStrHexToBinary(const char *cString) {
    int unsigned result;
    sscanf(cString, "%x", &result);
    return (int unsigned)result;
}
