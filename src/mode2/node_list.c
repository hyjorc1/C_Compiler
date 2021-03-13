#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

#include "m2global.h"

struct node* new_node(char *data) {
    struct node *n = (struct node*)malloc(sizeof(struct node));
    n->data = data;
    n->prev = NULL;
    n->next = NULL;
    return n;
}

struct list* new_list() {
    struct list *l = (struct list*)malloc(sizeof(struct list));
    l->size = 0;
    l->first = NULL;
    l->last = NULL;
    return l;
}

struct list* new_init_list(char *data) {
    struct list *l = new_list();
    add_last(l, data);
    return l;
}

void add_last(struct list *l, char *data) {
    if (l == NULL)
        return;
    struct node *n = new_node(data);
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

void clear_list(struct list *l) {
    if (l == NULL)
        return;
    struct node *cur = l->first;
    while (cur != NULL) {
        struct node *next = cur->next;
        free(cur->data);
        free(cur);
        cur = next;
    }
    l->first = NULL;
    l->last = NULL;
    l->size = 0;
}

void destroy_list(struct list *l) {
    if (l == NULL)
        return;
    clear_list(l);
    free(l);
}

void print_list(struct list *l) {
    if (l == NULL)
        return;
    print("list with size %d: ", l->size);
    struct node *cur = l->first;
    while (cur != NULL) {
        struct node *next = cur->next;
        print("%s", cur->data);
        if (next != NULL)
            print(", ");
        cur = next;
    }
    print("\n");
}

struct list* merge(struct list *l1, struct list *l2) {
    if (l2 == NULL || l2->size == 0)
        return l1;

    l1->last->next = l2->first;
    l2->first->prev = l1->last;
    l1->last = l2->last;
    l1->size += l2->size;

    l2->size = 0;
    l2->first = NULL;
    l2->last = NULL;
    free(l2);

    return l1;
}