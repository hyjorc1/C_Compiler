#ifndef M3_GLOBAL_H
#define M3_GLOBAL_H

#include "global.h"
#include "ast.h"

/* interface to the lexer with prefix 'm3' */
char *m3text;
int m3lineno;

/* interface to the lexer with prefix 'm3' */
int m3lex();
void m3error(const char* msg);
void m3restart(FILE *input_file);

/* interface to the parser with prefix 'm3' */
int m3parse();

/* global data structures and variables for mode 3 */
int m3_err_lineno;
char *m3_cur_file_name;

// struct list *m3_global_vars;
// struct struct_list *m3_global_structs;
// struct func_list *m3_global_funcs;

List *m3_global_vars;

#endif