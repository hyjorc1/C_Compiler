#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

/* -------------------- global variables -------------------- */

extern int debug;
extern int mode;

/* -------------------- global methods -------------------- */

extern void print(const char *format, ...);
extern void printusage();
extern void printversion();
extern char *concat(char *s1, char *s2);

extern void mode1(int argc, char *argv[], int fileIdx);
extern void mode2(int argc, char *argv[], int fileIdx);
extern void mode3(int argc, char *argv[], int fileIdx);
extern void mode4(int argc, char *argv[], int fileIdx);

#endif
