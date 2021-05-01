#ifndef DEQUE_H
#define DEQUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct ListNode {
    void *data;                 // need to free data
    struct ListNode *prev;
    struct ListNode *next;
} ListNode;

typedef struct {
    size_t size;                // list size
    size_t data_size;           // data size for each element
    ListNode *first;
    ListNode *last;
    void (*free_data)(void *);  // free function for data
} List;

List *list_new(size_t data_size, void (*free_data)(void *));

void list_destroy(List *l);

void list_destroy_void(void *v);

List *list_add_first(List *l, void *data);

List *list_add_last(List *l, void *data);

void *list_remove_last(List *l);

void list_print(List *l, void (*print_data)(void *));

List* list_merge(List *l1, List *l2);

#endif