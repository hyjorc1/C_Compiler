#ifndef M3_GLOBAL_H
#define M3_GLOBAL_H

#include "global.h"
#include "ast.h"

/* interface to the lexer with prefix 'm3' */
char *m3text;
int m3lineno;
int m3_err_lineno;

/* interface to the lexer with prefix 'm3' */
int m3lex();
void m3restart(FILE *input_file);

/* global data structures and variables for mode 3 */
char *m3_cur_file_name;
char m3_is_global;

/* Variables */ 
Type *cur_type;
List *m3_global_vars;
HashMap *m3_global_map;

List *m3_local_vars;
HashMap *m3_local_map;

/* Structs */
Struct *cur_struct;
List *m3_global_structs;
List *m3_local_structs;

/* Functions */
Function *cur_fn;
List *m3_global_funcs;
List *m3_local_stmts;

/* constant types */
Type *char_type;
Type *const_char_type;
Type *const_string_type;
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

/* variable handler */
void update_var_list(Variable *var);
Variable *update_type_map(Variable *var);
Variable *handle_init_var(Variable *var, Type *r_type);
Variable *handle_var_ident(char *id, char is_array);

/* struct handler */
void handle_struct_name_decl(char *id);
void update_struct_vars(Variable *v);
void update_structs();
Variable *handle_noinit_var_ident(char *id, char is_array);
Type *handle_struct_type_var(char *id);

/* function handler */
void handle_func_proto();
void handle_func_name(char *id);
void handle_para(char *id, char is_array);

/* expression handlers */
Type *handle_ASSIGN(char is_init, Type *t1, char *op, Type *t2);

Type *handle_UBANG(Type *t);


#endif