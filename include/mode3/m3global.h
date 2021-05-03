#ifndef M3_GLOBAL_H
#define M3_GLOBAL_H

#include "global.h"
#include "ast.h"
#include "goto_map.h"

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
extern char m3_error;
extern char m3_return_error;

/* Variables */ 
extern Type *cur_type;
extern Type *cast_type;
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
extern void m3warn();
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
extern Type *handle_ternary_exp(Type *t1, int true_label, Type *t2, List *true_next, int false_label, Type *t3, int end_label);
extern Type *handle_utilde(Type *t);
extern Type *handle_uminus(Type *t);
extern Type *handle_ubang(Type *t);
extern Type *handle_cast_exp(Type *t2);
extern Type *handle_r8_exp(Type *t1, char *op, Type *t2);
extern Type *handle_r9_exp(Type *t1, char *op, Type *t2);
extern Type *handle_r10_exp(Type *t1, char *op, Type *t2);
extern Type *handle_r10_marker(Type *t1, char *op, int label, Type *t2);
extern Type *handle_r11_exp(char *op, Type *t2);
extern Type *handle_r12_exp(Type *t1, char *op);
extern Type *handle_assign_exp(char is_init, Type *t1, char *op, Type *t2);
extern Type *handle_l_array_access(Type *t, Type *op);
extern Type *handle_l_member(Type *mt, char *m);
extern Type *handle_l_array_member(Type *st, char *m, Type *op);

extern Type *handle_cond_exp(char *msg, Type *t);
extern Type *handle_func_call_exp(char *id, List *arg_types);
extern List *handle_single_type(Type *t);

extern Type *handle_l_ident(char *id);

extern void print_err_func_sig(Function *f);

/* ---------------- mode 4  --------------------- */
extern char binary_assign;
extern int return_count;
extern const char *ident4;
extern const char *ident8;

extern void m4handle_arr_init(char *id, char *num);
extern void m4handle_global_var(char *id);
extern void m4handle_global_var_init(char *id);

extern void m4handle_func_def();

extern void m4handle_return_stmt(Type *t);
extern void m4handle_exp_stmt();
extern void m4handle_comment(char *cmt);


/* ---------------- mode 4 exp functions --------------------- */

extern void m4handle_int(char *val);
extern void m4handle_real(char *val);
extern void m4handle_str(char *val);
extern void m4handle_char(char *val);

extern void m4handle_assign_exp(Type *res, Type *lt, char *op, Type *rt);

extern void m4handle_func_call_exp(Function *fn);

extern Type *m4handle_lval(Type *t);

extern void m4handle_r11_exp(char *op, Type *t2);
extern void m4handle_r12_exp(Type *t1, char *op);

extern void m4handle_utilde();
extern void m4hanlde_uminus(Type *t);

extern void m4handle_cast_exp(Type *t1, Type *t2);
extern void m4handle_r8_exp(Type *t, char *op);
extern void m4handle_r9_exp(Type *t, char *op);

/* ---------------- mode 5  --------------------- */
extern int instr_line;
extern int instr_label;
extern GotoMap *gotomap;

extern void backpatch(List *list, int label);

extern void m5handle_loop();

/* ---------------- mode 5 stmt functions --------------------- */
extern List *m5handle_if(Type *b, int true_label, List *s_list);
extern List *m5handle_ifelse(Type *b, int true_label, List *true_list, List *next_list, int false_label, List *false_list);
extern List *m5handle_while(int cond_label, Type *b, int do_label, List *s_list);
extern List *m5handle_do(int do_label, List *s_list, int cond_label, Type *b);
extern List *m5handle_for(int cond_label, Type *b, int post_label, List *pos_next, int stmt_label, List *s_list);
extern Type *m5hanlde_for_cond(Type *b);
extern void m5handle_break();
extern void m5handle_continue();

/* ---------------- mode 5 exp functions --------------------- */
extern int m5handle_label();
extern List *m5handle_next_line();

extern Type *m5handle_cond_exp(Type *t);
extern void m5handle_ubang(Type *res, Type *t);
extern void m5handle_r10_exp(Type *res, char *op);
extern void m5handle_r10_marker(Type *res, Type *t1, char *op, int label, Type *t2);

extern void m5handle_ternary_exp(Type *b, int true_label, List *true_next, int false_label, int end_label);

#endif