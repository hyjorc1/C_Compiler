#include "map.h"
#include "ast.h"

/* -------------- Map <char *key, Type *value> --------------- */

#define SIZE 20

Entry *new_entry(char *id, Type *type) {
    Entry *n = (Entry *)malloc(sizeof(Entry));
    n->id = id == NULL ? NULL : strdup(id);
    n->type = deep_copy_type_ast(type);
    n->next = NULL;
    return n;
}

HashMap* new_map() {
    HashMap *map = (HashMap *)malloc(sizeof(HashMap));
    map->size = 0;
    map->capacity = SIZE;
    map->data = (Entry **)malloc(sizeof(Entry *) * SIZE);
    for (int i = 0; i < SIZE; i++)
        map->data[i] = new_entry(NULL, NULL);
    return map;
}

Entry *find_prev(HashMap* map, char *id) {
    Entry *prev = map->data[map_hash(id) % SIZE];
    while (prev->next != NULL && strcmp(prev->next->id, id)) {
        prev = prev->next;
    }
    return prev;
}

int map_hash(char *id) {
    unsigned int hash = 0;
    unsigned c;
    while ((c = *id++))
        hash = hash * 7 ^ c;
    return hash;
}

void map_put(HashMap* map, char *id, Type *type) {
    Entry *prev = find_prev(map, id);
    if (prev->next == NULL) {
        prev->next = new_entry(id, type);
        map->size++;
    } else {
        prev->next->type = type;
    }
}

Type *map_get(HashMap* map, char *id) {
    Entry *cur = find_prev(map, id)->next;
    return cur == NULL ? NULL : cur->type;
}

void free_entry(Entry *e) {
    free(e->id);
    free_type_ast(e->type);
    free(e);
}

void map_remove(HashMap* map, char *id) {
    Entry *prev = find_prev(map, id);
    if (prev->next != NULL) {
        Entry *cur = prev->next;
        prev->next = cur->next;
        free_entry(cur);
        map->size--;
    }
}

void map_free(HashMap* map) {
    if (map == NULL)
        return;
    for (int i = 0; i < SIZE; i++) {
        Entry *cur = map->data[i];
        while (cur != NULL) {
            Entry *next = cur->next;
            free_entry(cur);
            cur = next;
        }
    }
    free(map);
}

void map_clear(HashMap* map) {
    if (map == NULL)
        return;
    for (int i = 0; i < SIZE; i++) {
        Entry *cur = map->data[i];
        while (cur != NULL) {
            Entry *next = cur->next;
            free_entry(cur);
            cur = next;
        }
        map->data[i]->next = NULL;
    }
}

void map_print(HashMap* map) {
    if (map == NULL)
        return;
    for (int i = 0; i < map->capacity; i++) {
        Entry *cur = map->data[i]->next;
        while (cur != NULL) {
            char* type = type_to_str(cur->type);
            printf("map key: %s,\tval: %s\n", cur->id, type);
            free(type);
            cur = cur->next;
        }
    }
}