#ifndef M2_GLOBAL_H
#define M2_GLOBAL_H

#include  "global.h"

/* -------------------- global variables -------------------- */

/* interface to the lexer with prefix 'm2' */
extern char *m2text;
extern int m2lineno;

/* -------------------- global methods -------------------- */

/* interface to the lexer with prefix 'm2' */
extern int m2lex();
extern void m2error(const char* mesg);
extern void m2restart(FILE *input_file);

/* interface to the parser with prefix 'm2' */
extern int m2parse();

#endif