#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "global.h"

void print(const char *format, ...) {
    if (debug) {
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    }
}

