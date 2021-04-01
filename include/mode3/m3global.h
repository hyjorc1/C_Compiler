#ifndef M3_GLOBAL_H
#define M3_GLOBAL_H

#include "global.h"
#include "ast.h"

/* interface to the lexer with prefix 'm3' */
extern char *m3text;
extern int m3lineno;
extern int m3_err_lineno;

/* interface to the lexer with prefix 'm3' */
extern int m3lex();
extern void m3restart(FILE *input_file);

/* global data structures and variables for mode 3 */
extern char *m3_cur_file_name;
extern char m3_is_global;

/* Variables */ 
extern Type *cur_type;
extern List *m3_global_vars;
extern HashMap *m3_global_map;

extern List *m3_local_vars;
extern HashMap *m3_local_map;

/* Structs */
extern Struct *cur_struct;
extern List *m3_global_structs;
extern List *m3_local_structs;

/* Functions */
extern Function *cur_fn;
extern List *m3_global_funcs;

/* Statements */
extern List *m3_local_stmts;

/* constant strings for types */
extern const char *char_str;
extern const char *int_str;
extern const char *float_str;
extern const char *void_str;
extern const char *error_str;

/* interface to the parser with prefix 'm3' */
extern int m3parse();
extern void m3error(const char* msg);
extern void m3err();
extern void m3dprint(const char* s1, const char* s2);

extern void preprocess();
extern void postprocess();

extern char is_type_N(Type *t);
extern char is_type_I(Type *t);

/* 2.4 Extra credit: widening  */
extern int widen_rank(Type *t);
extern Type *widen_type(Type *t1, Type *t2);
extern char widen_match_type(Type *from, Type *to);

/* variable handler */
extern Type *find_global_type(char *id);
extern Type *find_local_type(char *id);
extern void update_var_list(Variable *var);
extern Variable *update_type_map(Variable *var);
extern Variable *handle_init_var(Variable *var, Type *r_type);
extern Variable *handle_var_ident(char *id, char is_array);

/* struct handler */
extern Struct *find_global_struct(char *id);
extern Struct *find_local_struct(char *id);
extern void handle_struct_name_decl(char *id);
extern void update_struct_vars(Variable *v);
extern void update_structs();
extern Variable *handle_noinit_var_ident(char *id, char is_array);
extern Type *handle_struct_type_var(char *id);

/* function handler */
extern Function *find_proto_func(char *id);
extern Function *find_declared_func(char *id);
extern void handle_func_proto();
extern void handle_func_name(char *id);
extern void handle_para(char *id, char is_array);
extern void handle_func_decl();
extern void handle_func_def();

/* statement handler */
extern void handle_exp_stmt(Type *t);
extern void handle_return_stmt(Type *t);

/* expression handlers */
extern Type *handle_ternary_exp(Type *t1, Type *t2, Type *t3);
extern Type *handle_utilde(Type *t);
extern Type *handle_uminus(Type *t);
extern Type *handle_ubang(Type *t);
extern Type *handle_cast_exp(Type *t2);
extern Type *handle_r8_exp(Type *t1, char *op, Type *t2);
extern Type *handle_r9_exp(Type *t1, char *op, Type *t2);
extern Type *handle_r10_exp(Type *t1, char *op, Type *t2);
extern Type *handle_r11_exp(char *op, Type *t2);
extern Type *handle_r12_exp(Type *t1, char *op);
extern Type *handle_assign_exp(char is_init, Type *t1, char *op, Type *t2);
extern Type *handle_l_array_access(char *id, Type *op);
extern Type *handle_l_member(Type *mt, char *m);
extern Type *handle_l_array_member(Type *st, char *m, Type *op);

extern void handle_cond_exp(char *msg, Type *t);
extern Type *handle_func_call_exp(char *id, List *arg_types);
extern List *handle_single_type(Type *t);

extern Type *handle_l_ident(char *id);

extern void print_err_func_sig(Function *f);


#endif