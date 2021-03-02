#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

#include "m2global.h"

struct struct_node* new_struct(char *name, struct list *members) {
    struct struct_node *n = (struct struct_node*)malloc(sizeof(struct struct_node));
    n->name = name;
    n->members = members;
    n->prev = NULL;
    n->next = NULL;
    return n;
}

struct struct_list* new_struct_list() {
    struct struct_list *l = (struct struct_list*)malloc(sizeof(struct struct_list));
    l->size = 0;
    l->first = NULL;
    l->last = NULL;
    return l;
}

void add_last_struct(struct struct_list *l, struct struct_node *n) {
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

void clear_struct_list(struct struct_list *l) {
    if (l == NULL)
        return;
    struct struct_node *cur = l->first;
    while (cur != NULL) {
        struct struct_node *next = cur->next;
        free(cur->name);
        destroy_list(cur->members);
        free(cur);
        cur = next;
    }
    l->first = NULL;
    l->last = NULL;
    l->size = 0;
}

void destroy_struct_list(struct struct_list *l) {
    if (l == NULL)
        return;
    clear_struct_list(l);
    free(l);
}
