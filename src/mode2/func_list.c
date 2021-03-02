#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

#include "m2global.h"

struct func_node* new_func(char *name, struct list *paras, struct list *local_structs, struct list *local_vars, int is_proto) {
    struct func_node *n = (struct func_node*)malloc(sizeof(struct func_node));
    n->name = name;
    n->is_proto = is_proto;
    n->paras = paras;
    n->local_structs = local_structs;
    n->local_vars = local_vars;
    n->prev = NULL;
    n->next = NULL;
    return n;
}

struct func_list* new_func_list() {
    struct func_list *l = (struct func_list*)malloc(sizeof(struct func_list));
    l->size = 0;
    l->first = NULL;
    l->last = NULL;
    return l;
}

void add_last_func(struct func_list *l, struct func_node *n) {
    if (l->size == 0) {
        l->first = n;
        l->last = n;
    } else {
        n->prev = l->last;
        l->last->next = n;
        l->last = n;
    }
    l->size++;
}

void clear_func_list(struct func_list *l) {
    if (l == NULL)
        return;
    struct func_node *cur = l->first;
    while (cur != NULL) {
        struct func_node *next = cur->next;
        free(cur->name);
        destroy_list(cur->paras);
        destroy_list(cur->local_structs);
        destroy_list(cur->local_vars);
        free(cur);
        cur = next;
    }
    l->first = NULL;
    l->last = NULL;
    l->size = 0;
}

void destroy_func_list(struct func_list *l) {
    clear_func_list(l);
    free(l);
}
