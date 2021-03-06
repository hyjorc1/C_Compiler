#include "deque.h"

ListNode* node_new(void *data, size_t data_size) {
    assert(data_size > 0);
    ListNode *n = (ListNode *)malloc(sizeof(ListNode));
    n->data = data;
    // n->data = (void *)malloc(data_size);
    // memcpy(n->data, data, data_size);
    n->prev = NULL;
    n->next = NULL;
    return n;
}

List *list_new(size_t data_size, void (*free_data)(void *)) {
    assert(data_size > 0);
    List *l = (List *)malloc(sizeof(List));
    l->size = 0;
    l->data_size = data_size;
    l->first = NULL;
    l->last = NULL;
    l->free_data = free_data;
    return l;
}

void list_destroy(List *l) {
    if (l == NULL)
        return;
    ListNode *cur = l->first;
    while (cur != NULL) {
        ListNode *next = cur->next;
        if (l->free_data)
            (*(l->free_data))(cur->data);
        free(cur);
        cur = next;
    }
    free(l);
}

void list_destroy_void(void *v) {
    if (v == NULL)
        return;
    list_destroy((List *)v);
}

List *list_add_first(List *l, void *data) {
    if (l == NULL || data == NULL)
        return l;
    ListNode *n = node_new(data, l->data_size);
    if (l->size == 0) {
        l->first = n;
        l->last = n;
    } else {
        n->next = l->first;
        l->first->prev = n;
        l->first = n;
    }
    l->size++;
    return l;
}

List *list_add_last(List *l, void *data) {
    if (l == NULL || data == NULL)
        return l;
    ListNode *n = node_new(data, l->data_size);
    if (l->size == 0) {
        l->first = n;
        l->last = n;
    } else {
        n->prev = l->last;
        l->last->next = n;
        l->last = n;
    }
    l->size++;
    return l;
}

void *list_remove_last(List *l) {
    if (l == NULL || l->size == 0)
        return NULL;
    ListNode *n = l->last;
    if (l->first == l->last) {
        l->first = NULL;
        l->last = NULL;
    } else {
        n->prev->next = NULL;
        l->last = n->prev;
    }
    l->size--;
    void *data = n->data;
    free(n);
    return data;
}

void list_print(List *l, void (*print_data)(void *)) {
    if (l == NULL)
        return;
    printf("list size %zu: ", l->size);
    ListNode *cur = l->first;
    while (cur != NULL) {
        ListNode *next = cur->next;
        (*print_data)(cur->data);
        if (next != NULL)
            printf(", ");
        cur = next;
    }
    printf("\n");
}

List* list_merge(List *l1, List *l2) {
    if (l1 == NULL || l1->size == 0)
        return l2;
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