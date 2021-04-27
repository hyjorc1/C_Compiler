#ifndef M5_GLOBAL_H
#define M5_GLOBAL_H

#include "m4global.h"
#include "goto_map.h"

/* mode 5 utilties */

extern void m5preprocess();
extern void m5process(char *argv[], int i);
extern void m5postprocess();

#endif