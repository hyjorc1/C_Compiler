#ifndef M2_GLOBAL_H
#define M2_GLOBAL_H

#include  "global.h"

/* interface to the lexer with prefix 'm2' */
extern char *m2text;
extern int m2lineno;

/* interface to the lexer with prefix 'm2' */
extern int m2lex();
extern void m2error(const char* mesg);
extern void m2restart(FILE *input_file);

/* interface to the parser with prefix 'm2' */
extern int m2parse();


/* global data structures and variables for mode 2 */

extern int err_lineno;

struct struct_node {
    char *name;
    gll_t *members;             /* list of char **data */
};

struct func_node {
    int ast_type;
    char *name;
    gll_t *paras;               /* list of char **data */
    gll_t *local_structs;       /* list of struct struct_node *data */
    gll_t *local_vars;          /* list of char **data */
};

extern gll_t *global_structs;   /* list of struct struct_node *data */
extern gll_t *global_vars;      /* list of char **data */
extern gll_t *funcs;            /* list of struct func_node *data */

#endif