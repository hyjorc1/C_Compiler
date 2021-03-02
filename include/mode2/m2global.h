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

extern struct node* new_node(char *data);
extern struct list* new_list_data(char *data);
extern struct list* new_list();
extern void add_first(struct list *l, char *data);
extern void add_last(struct list *l, char *data);
extern void clear_list(struct list *l);
extern void destroy_list(struct list *l);
extern void print_list(struct list *l);
extern struct list* merge(struct list *l1, struct list *l2);

// struct struct_node {
//     char *name;
//     gll_t *members;             /* list of char **data */
// };

// struct func_node {
//     int ast_type;               /* 0 for prototype and 1 for function */
//     char *name;
//     gll_t *paras;               /* list of char **data */
//     gll_t *local_structs;       /* list of char **data */
//     gll_t *local_vars;          /* list of char **data */
// };

// extern gll_t *global_structs;   /* list of struct struct_node **data */
// extern gll_t *global_vars;      /* list of char **data */
// extern gll_t *funcs;            /* list of struct func_node **data */

// extern gll_t *gll_init_str(char *str);

// extern void print_gll(gll_t *list);

extern struct list *global_vars;

#endif