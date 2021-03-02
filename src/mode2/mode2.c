#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

#include "m2global.h"



struct node* new_node(char *data) {
    struct node *n = (struct node*) malloc(sizeof(struct node));
    n->data = data;
    n->prev = NULL;
    n->next = NULL;
    return n;
}

struct list* new_list() {
    struct list *l = (struct list*) malloc(sizeof(struct list));
    l->size = 0;
    l->first = NULL;
    l->last = NULL;
    return l;
}

struct list* new_list_data(char *data) {
    struct list *l = new_list();
    add_first(l, data);
    return l;
}

void add_first(struct list *l, char *data) {
    struct node *n = new_node(data);
    if (l->size == 0) {
        l->first = n;
        l->last = n;
    } else {
        n->next = l->first;
        l->first->prev = n;
        l->first = n;
    }
    l->size++;
}

void add_last(struct list *l, char *data) {
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
    if (l2->size == 0)
        return NULL;

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

void print_global_vars() {
    if (global_vars == NULL)
        return;
    printf("Global variables\n\t");
    struct node *cur = global_vars->first;
    while (cur != NULL) {
        struct node *next = cur->next;
        printf("%s", cur->data);
        if (next != NULL)
            printf(", ");
        cur = next;
    }
    printf("\n");
}

void mode2(int argc, char *argv[], int fileIdx) {

    // struct list *l = new_list();
    // add_last(l, strdup("1"));
    // add_last(l, strdup("2"));
    // add_last(l, strdup("3"));

    // add_first(l, strdup("1"));
    // add_first(l, strdup("2"));
    // add_first(l, strdup("3"));

    // print_list(l);

    // print("%s %s\n", l->first->data, l->last->data);

    // struct list *l1 = new_list();
    // add_last(l1, strdup("4"));
    // add_last(l1, strdup("5"));
    // add_last(l1, strdup("6"));

    // merge(l, l1);


    for (int i = fileIdx; i < argc; i++) {
        print("\nstart file %s\n", argv[i]);
        FILE *f = fopen(argv[i], "r");
        if (!f)
            perror(argv[i]);
        m2restart(f);
        m2parse();

        // print_global_structs();

        print_global_vars();

        // print_funcs();

        fclose(f);
    }

}





