#ifndef IO_H
#define IO_H

#include <stdlib.h>
#include <stdio.h>
#include "String.h"

typedef struct _IO {
    void (*write)(void *, String *);
    FILE *fp;
} IO;

#endif
