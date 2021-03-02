#ifndef M2_GLOBAL_H
#define M2_GLOBAL_H

#include  "global.h"

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

extern int err_lineno;
extern char *cur_file_name;

/* -------------- node and list -------------------- */

struct node {
    char* data;
    struct node *prev;
    struct node *next;
};

struct list {
    int size;
    struct node *first;
    struct node *last;
};

extern struct list *global_vars;

extern struct node* new_node(char *data);
extern struct list* new_init_list(char *data);
extern struct list* new_list();
extern void add_last(struct list *l, char *data);
extern void clear_list(struct list *l);
extern void destroy_list(struct list *l);
extern struct list* merge(struct list *l1, struct list *l2);

extern void print_list(struct list *l);

/* -------------- struct node and list -------------------- */

struct struct_node {
    char* name;
    struct list *members;
    struct struct_node *prev;
    struct struct_node *next;
};

struct struct_list {
    int size;
    struct struct_node *first;
    struct struct_node *last;
};

extern struct struct_list *global_structs;

extern struct struct_node* new_struct(char *name, struct list *members);
extern struct struct_list* new_struct_list();
extern void add_last_struct(struct struct_list *l, struct struct_node *n);
extern void clear_struct_list(struct struct_list *l);
extern void destroy_struct_list(struct struct_list *l);

/* -------------- function node and list -------------------- */

struct func_node {
    char* name;
    int is_proto;
    struct list *paras;
    struct list *local_structs;
    struct list *local_vars;
    struct func_node *prev;
    struct func_node *next;
};

struct func_list {
    int size;
    struct func_node *first;
    struct func_node *last;
};

extern struct func_list *global_funcs;

extern struct func_node* new_func(char *name, struct list *paras, struct list *local_structs, struct list *local_vars, int is_proto);
extern struct func_list* new_func_list();
extern void add_last_func(struct func_list *l, struct func_node *n);
extern void clear_func_list(struct func_list *l);
extern void destroy_func_list(struct func_list *l);

/* -------------- function node and list -------------------- */

#endif