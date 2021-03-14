#ifndef FUNC_LIST_H
#define FUNC_LIST_H

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



struct func_node* new_func(char *name, struct list *paras, struct list *local_structs, struct list *local_vars, int is_proto);
struct func_list* new_func_list();
void add_last_func(struct func_list *l, struct func_node *n);
void clear_func_list(struct func_list *l);
void destroy_func_list(struct func_list *l);

#endif