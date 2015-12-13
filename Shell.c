#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Shell.h"
#include "String.h"
#include "IO.h"
#include "IOScreen.h"
#include "IOFile.h"

static void arrayShift(char *array[], int length, int index) {
    for (int i = index; i < length - 1; i++) *(array + i) = *(array + i + 1);
}

static String *getFileName(void *_this, int filePos, int *argc, char *argv[]) {
    String *str = newString(argv[filePos]);
    arrayShift(argv, *argc, filePos);
    *argc -= 1;
    return str;
}

static void initializeStandardOut(void * _this, int i, int appendFlag, int *argc, char *argv[]) {
    Shell  *this     = (Shell*)_this;
    String *fileName = getFileName(this, i + 1, argc, argv);
    if (appendFlag) this->output = (IO*)(newIOFile(fileName, "ab"));
    else            this->output = (IO*)(newIOFile(fileName, "wb"));
}

static void initializeErrorOut(void * _this, int i, int appendFlag, int *argc, char *argv[]) {
    Shell  *this     = (Shell*)_this;
    String *fileName = getFileName(this, i + 1, argc, argv);
    if (appendFlag) this->errorOutput = (IO*)(newIOFile(fileName, "ab"));
    else            this->errorOutput = (IO*)(newIOFile(fileName, "wb"));
}

static void initializeFileRead(void * _this, int i, int *argc, char *argv[]) {
    Shell  *this     = (Shell*)_this;
    String *fileName = getFileName(this, i + 1, argc, argv);
    this->input = (IO*)(newIOFile(fileName, "rb"));
    printf("reading from file%s\n", fileName->cString);
}

static void setIO(void * _this, int *argc, char *argv[]) {
    Shell *this = (Shell*)_this;
    for (int i = 1; i < *argc; ++i) {
        if      (strcmp(argv[i], ">"  ) == 0) initializeStandardOut(this, i, 0, argc, argv);
        else if (strcmp(argv[i], ">>" ) == 0) initializeStandardOut(this, i, 1, argc, argv);
        else if (strcmp(argv[i], "2>" ) == 0) initializeErrorOut   (this, i, 0, argc, argv);
        else if (strcmp(argv[i], "2>>") == 0) initializeErrorOut   (this, i, 1, argc, argv);
        else if (strcmp(argv[i], "<"  ) == 0) initializeFileRead   (this, i, argc, argv);
        else continue;
        arrayShift(argv, *argc, i);
        setIO(this, argc, argv);
        return;
    }
}

static void setBgMode(void * _this, int *argc, char *argv[]) {
    Shell *this = (Shell*)_this;
    this->bgMode = (strcmp(argv[*argc - 1], "&") == 0);
    arrayShift(argv, *argc, 8);
    *argc -= 1;
    printf("background mode: %d\n", this->bgMode);
}

static void initFromArgV(void *_this, int argc, char *argv[]) {
    Shell *this = (Shell*)_this;
    setIO(this, &argc, argv);
    setBgMode(this, &argc, argv);
    if (this->output      == 0) this->output      = (IO*)(newIOScreen());
    if (this->errorOutput == 0) this->errorOutput = (IO*)(newIOScreen());
    if (this->input       == 0) this->input       = (IO*)(newIOScreen());

    String *str = newString("testing output");
    this->output->write(this->output, str);
    str = newString("testing error output");
    this->errorOutput->write(this->errorOutput, str);
    deleteString(str);
}


Shell *newShell(int argc, char *argv[]) {
    Shell *this = malloc(sizeof(Shell));
    this->toString = &toString;

    printf("Initializing shell\n");
    this->output      = 0;
    this->errorOutput = 0;
    this->input       = 0;
    initFromArgV(this, argc, argv);
    return this;
}


String *toString(void *_this) {
    // Shell *this = (Shell*)_this;
    String *str = newString("Shell as string:");
    return str;
}
