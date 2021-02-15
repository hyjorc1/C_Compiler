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

void printusage() {
    fprintf(stderr, "Usage:\n\t./mycc -mode [options] infile\n\n");
    fprintf(stderr, "Valid modes:\n");
    fprintf(stderr, "\t-0: Version information\n");
    fprintf(stderr, "\t-1: (not implemented yet)\n");
    fprintf(stderr, "\t-2: (not implemented yet)\n");
    fprintf(stderr, "\t-3: (not implemented yet)\n");
    fprintf(stderr, "\t-4: (not implemented yet)\n");
    fprintf(stderr, "\t-5: (not implemented yet)\n");
    fprintf(stderr, "\nValid options:\n");
    fprintf(stderr, "\t-o outfile: write to outfile instead of standard output\n");
}

void printversion() {
    fprintf(stdout, "My bare-bones C compiler (for COM 540)\n");
    fprintf(stdout, "\tWritten by Yijia Huang (hyj@iastate.edu)\n");
    fprintf(stdout, "\tVersion 0.1\n");
    fprintf(stdout, "\t16 Feb, 2021\n");
}