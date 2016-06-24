#ifndef IOSCREEN_H
#define IOSCREEN_H

#include "String.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _IOScreen {
    void (*out)(void *, String *);
    FILE *fp;
    int isFile;
} IOScreen;

IOScreen *newIOScreen();

void out(void *, String*);

#endif
