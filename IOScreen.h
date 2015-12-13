#ifndef IOSCREEN_H
#define IOSCREEN_H

#include "String.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _IOScreen {
    void (*write)(void *, String *);
    FILE *fp;
} IOScreen;

IOScreen *newIOScreen();

void write(void *, String*);

#endif
