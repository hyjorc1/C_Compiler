#ifndef GLOBAL_H
#define GLOBAL_H

/* -------------------- global variables -------------------- */

extern int debug;
/* -------------------- global methods -------------------- */

extern void print(const char *format, ...);
extern void printusage();
extern void printversion();

extern void mode1(int argc, char *argv[], int fileIdx);

extern void mode2(int argc, char *argv[], int fileIdx);

#endif