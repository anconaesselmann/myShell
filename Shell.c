#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "Shell.h"
#include "String.h"
#include "IO.h"
#include "IOScreen.h"
#include "IOFile.h"

#define BUFFER_SIZE 1024

#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2
static int getLine (char *prmpt, char *buff, size_t sz) {
    int ch, extra;

    // Get line with buffer overrun protection.
    if (prmpt != NULL) {
        printf ("%s", prmpt);
        fflush (stdout);
    }
    if (fgets (buff, sz, stdin) == NULL)
        return NO_INPUT;

    // If it was too long, there'll be no newline. In that case, we flush
    // to end of line so that excess doesn't affect the next call.
    if (buff[strlen(buff)-1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }

    // Otherwise remove newline and give string back to caller.
    buff[strlen(buff)-1] = '\0';
    return OK;
}

static void arrayShift(char *array[], int *length, int index) {
    for (int i = index; i < *length - 1; i++) *(array + i) = *(array + i + 1);
    *length -= 1;
}

static String *getFileName(void *_this, int filePos, int *argc, char *argv[]) {
    String *str = newString(argv[filePos]);
    arrayShift(argv, argc, filePos);
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
        arrayShift(argv, argc, i);
        setIO(this, argc, argv);
        return;
    }
}

static void setBgMode(void * _this, int *argc, char *argv[]) {
    Shell *this = (Shell*)_this;
    this->bgMode = (strcmp(argv[*argc - 1], "&") == 0);
    arrayShift(argv, argc, *argc - 1);
    printf("background mode: %d\n", this->bgMode);
}

void parseArgs(void * _this, String *str, int *argc, char **argv) {
    *argc         = 0;
    int pos       = 0;
    int bufferPos = 0;
    char buffer[1024];

    char current;
    do {
        current = str->cString[pos];
        if (current == ' ' || current == 0) {
            buffer[bufferPos] = 0;
            strcpy(argv[*argc], buffer);
            bufferPos = 0;
            *argc += 1;
        } else {
            buffer[bufferPos] = current;
            bufferPos += 1;
        }
        pos += 1;
    } while (current);
}

static void initFromArgV(void *_this, char *userInput) {
    Shell *this = (Shell*)_this;
    int argc;
    char **argv = malloc(1024 * sizeof(char));
    for (int i = 0; i < 1024; i++) {
        *(argv + i) = malloc(1024 * sizeof(char));
    }

    parseArgs(
        this,
        // newString(userInput), //"ls -l 2>> standardErrorOutAppend2.txt >> standardOutAppend2.txt < inputFile.txt &"
        newString("ls -l 2>> standardErrorOutAppend2.txt >> standardOutAppend2.txt < inputFile.txt &"),
        &argc,
        argv
    );

    this->output      = 0;
    this->errorOutput = 0;
    this->input       = 0;

    setIO(this, &argc, argv);
    setBgMode(this, &argc, argv);
    if (this->output      == 0) this->output      = (IO*)(newIOScreen());
    if (this->errorOutput == 0) this->errorOutput = (IO*)(newIOScreen());
    if (this->input       == 0) this->input       = (IO*)(newIOScreen());
    argv[argc] = 0;
    this->args = argv;
    this->argc = argc;
}

Shell *newShell() {
    Shell *this = malloc(sizeof(Shell));
    this->userPrompt = &userPrompt;
    return this;
}

int userPrompt(void *_this) {
    Shell *this = (Shell*)_this;
    char buffer[1024];
    char prompt[] = "$";
    getLine(prompt, buffer, BUFFER_SIZE);
    printf("%s\n", buffer);
    initFromArgV(this, buffer);
    pid_t  pid = fork();
    if(pid == 0) {
        execvp(this->args[0], this->args);
        exit(0);
    } else {
        int status;
        waitpid(pid, &status, 0);
        if (status == 0) {
            // this->userPrompt(this);
        } else {
            printf("an error occured.\n");
        }
    }
    return 0;
}
