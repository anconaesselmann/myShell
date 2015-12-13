#ifndef SHELL_H
#define SHELL_H

#include "String.h"
#include "IO.h"

typedef struct _Shell {
    const struct shell_vtable *vtable;
    int (*userPrompt)(void *_this);
    String *programName;
    int bgMode;
    int opMode; // 0 is to the screen, 1 is to new file, 2 is append to file
    IO *output;
    IO *errorOutput;
    IO *input;
    char **args;
    int argc;
} Shell;


// Shell *newShell(int argc, char *argv[]);
Shell *newShell();
// Shell *newShell();

String *toString(void *this);
int userPrompt(void *_this);

// void deleteShell(PageTable *pt);

#endif
