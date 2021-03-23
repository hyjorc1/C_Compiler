#ifndef M2_GLOBAL_H
#define M2_GLOBAL_H

#include  "global.h"
#include  "node_list.h"
#include  "struct_list.h"
#include  "func_list.h"

/* interface to the lexer with prefix 'm2' */
extern char *m2text;
extern int m2lineno;

/* interface to the lexer with prefix 'm2' */
extern int m2lex();
extern void m2error(const char* msg);
extern void m2restart(FILE *input_file);

/* interface to the parser with prefix 'm2' */
extern int m2parse();

/* global data structures and variables for mode 2 */
extern int m2_err_lineno;
extern char *m2_cur_file_name;

extern struct list *m2_global_vars;
extern struct struct_list *m2_global_structs;
extern struct func_list *m2_global_funcs;

#endif