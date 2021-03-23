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

/* Statements */
List *m3_local_stmts;
List *m3_arg_types;

const char *char_str;
const char *int_str;
const char *float_str;
const char *void_str;
const char *error_str;

/* interface to the parser with prefix 'm3' */
int m3parse();
void m3error(const char* msg);
void m3err();
void m3dprint(const char* s1, const char* s2);

void preprocess();
void postprocess();

char is_type_N(Type *t);
char is_type_I(Type *t);

/* 2.4 Extra credit: widening  */
int widen_rank(Type *t);
Type *widen_type(Type *t1, Type *t2);
char widen_match_type(Type *from, Type *to);

/* variable handler */
Type *find_global_type(char *id);
Type *find_local_type(char *id);
void update_var_list(Variable *var);
Variable *update_type_map(Variable *var);
Variable *handle_init_var(Variable *var, Type *r_type);
Variable *handle_var_ident(char *id, char is_array);

/* struct handler */
Struct *find_global_struct(char *id);
Struct *find_local_struct(char *id);
void handle_struct_name_decl(char *id);
void update_struct_vars(Variable *v);
void update_structs();
Variable *handle_noinit_var_ident(char *id, char is_array);
Type *handle_struct_type_var(char *id);

/* function handler */
Function *find_proto_func(char *id);
Function *find_func(char *id);
void handle_func_proto();
void handle_func_name(char *id);
void handle_para(char *id, char is_array);
void handle_func_decl();
void handle_func_def();

/* statement handler */
void handle_exp_stmt(Type *t);
void handle_return_stmt(Type *t);

/* expression handlers */
Type *handle_ternary_exp(Type *t1, Type *t2, Type *t3);
Type *handle_utilde(Type *t);
Type *handle_uminus(Type *t);
Type *handle_ubang(Type *t);
Type *handle_cast_exp(Type *t2);
Type *handle_r8_exp(Type *t1, char *op, Type *t2);
Type *handle_r9_exp(Type *t1, char *op, Type *t2);
Type *handle_r10_exp(Type *t1, char *op, Type *t2);
Type *handle_r11_exp(char *op, Type *t2);
Type *handle_r12_exp(Type *t1, char *op);
Type *handle_assign_exp(char is_init, Type *t1, char *op, Type *t2);
Type *handle_l_array_access(char *id, Type *op);
Type *handle_l_member(Type *mt, char *m);
Type *handle_l_array_member(Type *st, char *m, Type *op);

void handle_cond_exp(char *msg, Type *t);
Type *handle_func_call_exp(char *id);
void handle_exp_list(Type *t);

Type *handle_l_ident(char *id);


#endif