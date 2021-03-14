#ifndef NODE_LIST_H
#define NODE_LIST_H

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

struct node* new_node(char *data);

struct list* new_init_list(char *data);

struct list* new_list();

void add_last(struct list *l, char *data);

void add_first(struct list *l, char *data);

void clear_list(struct list *l);

void destroy_list(struct list *l);

struct list* merge(struct list *l1, struct list *l2);

void print_list(struct list *l);

#endif