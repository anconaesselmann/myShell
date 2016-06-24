#include "IO.h"
#include "IOFile.h"

void file_out(void *_this, String *_str) {
    IOFile *this = (IOFile*)_this;
    String *str = newString(_str->cString);
    fprintf(this->fp, "%s\n", str->cString);
    deleteString(str);
}

IOFile *newIOFile(String *fileName, char mode[]) {
    IOFile *this = malloc(sizeof(IOFile));
    this->out = &file_out;
    this->isFile = 1;
    this->fp = fopen(fileName->cString, mode);
    return this;
}



// const struct io_vtable IOSCREEN[] = { { sound } };