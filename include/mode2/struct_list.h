#ifndef STRUCT_LIST_H
#define STRUCT_LIST_H

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

struct struct_node* new_struct(char *name, struct list *members);

struct struct_list* new_struct_list();

void add_last_struct(struct struct_list *l, struct struct_node *n);

void clear_struct_list(struct struct_list *l);

void destroy_struct_list(struct struct_list *l);

#endif