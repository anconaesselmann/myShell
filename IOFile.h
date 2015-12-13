#ifndef IOSFILE_H
#define IOSFILE_H

#include "String.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _IOFile {
    void (*write)(void *, String *);
    FILE *fp;
} IOFile;

IOFile *newIOFile(String *fileName, char mode[]);

void write(void *, String*);

#endif
