#include <stdlib.h>
#include <stdio.h>
#include "goto_map.h"

#define SIZE 100

GotoEntry *new_gotoentry(int key, int val) {
    GotoEntry *n = (GotoEntry *)malloc(sizeof(GotoEntry));
    n->key = key;
    n->val = val;
    n->next = NULL;
    return n;
}

GotoMap* new_gotomap() {
    GotoMap *map = (GotoMap *)malloc(sizeof(GotoMap));
    map->size = 0;
    map->capacity = SIZE;
    map->data = (GotoEntry **)malloc(sizeof(GotoEntry *) * SIZE);
    for (int i = 0; i < SIZE; i++)
        map->data[i] = new_gotoentry(-1, -1);
    return map;
}

struct GotoEntry *findPrev(GotoMap* map, int key) {
    GotoEntry *prev = map->data[key % map->capacity];
    while (prev->next != NULL && prev->next->key != key)
        prev = prev->next;
    return prev;
}

void gotomap_put(GotoMap* map, int key, int val) {
    GotoEntry *prev = findPrev(map, key);
    if (prev->next == NULL)
        prev->next = new_gotoentry(key, val);
    else
        prev->next->val = val;
}

int gotomap_get(GotoMap* map, int key) {
    GotoEntry *cur = findPrev(map, key)->next;
    return cur == NULL ? -1 : cur->val;
}

void gotomap_remove(GotoMap* map, int key) {
    GotoEntry *prev = findPrev(map, key);
    if (prev->next != NULL) {
        GotoEntry *cur = prev->next;
        prev->next = cur->next;
        free(cur);
    }
}

void gotomap_free(GotoMap* map) {
    if (map == NULL)
        return;
    for (int i = 0; i < SIZE; i++) {
        GotoEntry *cur = map->data[i];
        while (cur != NULL) {
            GotoEntry *next = cur->next;
            free(cur);
            cur = next;
        }
    }
    free(map);
}

void gotomap_print(GotoMap* map) {
    if (map == NULL)
        return;
    for (int i = 0; i < map->capacity; i++) {
        GotoEntry *cur = map->data[i]->next;
        while (cur != NULL) {
            printf("map key: %d, val: %d\n", cur->key, cur->val);
            cur = cur->next;
        }
    }
}