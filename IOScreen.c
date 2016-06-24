#include "IO.h"
#include "IOScreen.h"

void screen_out(void *_this, String *_str) {
    // IOScreen *this = (IOScreen*)_this;
    String *str = newString(_str->cString);
    printf("%s\n", str->cString);
    deleteString(str);
}

IOScreen *newIOScreen() {
    IOScreen *this = malloc(sizeof(IOScreen));
    this->out = &screen_out;
    this->isFile = 0;
    return this;
}



// const struct io_vtable IOSCREEN[] = { { sound } };
