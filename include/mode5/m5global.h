#ifndef M5_GLOBAL_H
#define M5_GLOBAL_H

#include "m4global.h"

/* mode 5 utilties */

extern void print_int(void *n);
extern int *new_int(int num);

extern void m5preprocess();
extern void m5process(char *argv[], int i);
extern void m5postprocess();

#endif