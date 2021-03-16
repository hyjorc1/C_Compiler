#include <stdio.h>
#include <stdlib.h>
#include "map.h"

#define SIZE 100

struct Entry *new_entry(char *key, char *val) {
    struct Entry *n = (struct Entry *)malloc(sizeof(struct Entry));
    n->key = key;
    n->val = val;
    n->next = NULL;
    return n;
}

HashMap* new_map() {
    HashMap *map = (HashMap *)malloc(sizeof(HashMap));
    map->size = 0;
    map->capacity = SIZE;
    map->data = (struct Entry **)malloc(sizeof(struct Entry *) * SIZE);
    for (int i = 0; i < SIZE; i++)
        map->data[i] = new_entry(NULL, NULL);
    return map;
}

struct Entry *find_prev(HashMap* map, char *key) {
    struct Entry *prev = map->data[map_hash(key)];
    while (prev->next != NULL && prev->next->key != key)
        prev = prev->next;
    return prev;
}

int map_hash(char *key) {
    unsigned int hash = 0;
    unsigned c;
    while ((c = *key++))
        hash = hash * 7 ^ c;
    return hash;
}

void map_put(HashMap* map, char *key, char *value) {
    struct Entry *prev = find_prev(map, key);
    if (prev->next == NULL)
        prev->next = new_entry(key, value);
    else
        prev->next->val = value;
}

char *map_get(HashMap* map, char *key) {
    struct Entry *cur = find_prev(map, key)->next;
    return cur == NULL ? NULL : cur->val;
}

void free_entry(struct Entry *e) {
    free(e->key);
    free(e->val);
    free(e);
}

void map_remove(HashMap* map, char *key) {
    struct Entry *prev = find_prev(map, key);
    if (prev->next != NULL) {
        struct Entry *cur = prev->next;
        prev->next = cur->next;
        free_entry(cur);
    }
}

void map_free(HashMap* map) {
    for (int i = 0; i < SIZE; i++) {
        struct Entry *cur = map->data[i];
        while (cur != NULL) {
            struct Entry *next = cur->next;
            free_entry(cur);
            cur = next;
        }
    }
    free(map);
}