#ifndef IOSFILE_H
#define IOSFILE_H

#include "String.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _IOFile {
    void (*out)(void *, String *);
    FILE *fp;
    int isFile;
} IOFile;

IOFile *newIOFile(String *fileName, char mode[]);

void out(void *, String*);

#endif
