#ifndef M2_GLOBAL_H
#define M2_GLOBAL_H

#include  "global.h"
#include  "node_list.h"
#include  "struct_list.h"
#include  "func_list.h"

/* interface to the lexer with prefix 'm2' */
char *m2text;
int m2lineno;

/* interface to the lexer with prefix 'm2' */
int m2lex();
void m2error(const char* msg);
void m2restart(FILE *input_file);

/* interface to the parser with prefix 'm2' */
int m2parse();

/* global data structures and variables for mode 2 */
int m2_err_lineno;
char *m2_cur_file_name;

struct list *m2_global_vars;
struct struct_list *m2_global_structs;
struct func_list *m2_global_funcs;

#endif