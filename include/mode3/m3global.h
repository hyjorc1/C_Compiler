#ifndef M3_GLOBAL_H
#define M3_GLOBAL_H

#include "global.h"
#include "ast.h"

/* interface to the lexer with prefix 'm3' */
char *m3text;
int m3lineno;

/* interface to the lexer with prefix 'm3' */
int m3lex();
void m3restart(FILE *input_file);

/* global data structures and variables for mode 3 */
int m3_err_lineno;
char *m3_cur_file_name;


Vars *m3_global_vars;
List *m3_global_structs;
List *m3_global_funcs;

int m3_is_global;
Type *cur_type;
Struct *cur_struct;

List *m3_local_structs;
Vars *m3_local_vars;
List *m3_local_stmts;

/* constant types */
Type *char_type;
Type *const_char_type;
Type *int_type;
Type *const_int_type;
Type *float_type;
Type *const_float_type;

const char *char_str;
const char *int_str;
const char *float_str;

/* interface to the parser with prefix 'm3' */
int m3parse();
void m3error(const char* msg);
void m3err();
void m3dprint(const char* s1, const char* s2);

void preprocess_const_types();
void free_const_types();

char is_type_N(Type *t);
char is_type_I(Type *t);


/* 2.4 Extra credit: widening  */
int widen_rank(Type *t);
Type *widen_type(Type *t1, Type *t2);

/* variable handlers */
Type *find_global_type(char *id);
Type *find_local_type(char *id);

void update_var_list(Variable *var);
Variable *update_type_map(Variable *var);
Variable *handle_init_var(Variable *var, Type *r_type);
Variable *handle_var_ident(char *id, char is_array);

/* struct handlers */
void handle_struct_name_decl(char *id);
void update_struct_var(Variable *v);
void handle_struct_decl();

/* expression handlers */
Type *handle_ASSIGN(char is_init, Type *t1, char *op, Type *t2);

Type *handle_UBANG(Type *t);


#endif