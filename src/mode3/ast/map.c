#include "global.h"
#include "map.h"

/* -------------------- Type AST -------------------- */
Type *new_type_ast(char *name, char is_const, char is_struct, char is_array) {
    Type *t = (Type *)malloc(sizeof(Type));
    t->name = name;
    t->is_const = is_const;
    t->is_struct = is_struct;
    t->is_array = is_array;
    return t;
}

Type *deep_copy_type_ast(Type *t) {
    if (t == NULL)
        return NULL;
    Type *copy = (Type *)malloc(sizeof(Type));
    copy->name = strdup(t->name);
    copy->is_const = t->is_const;
    copy->is_struct = t->is_struct;
    copy->is_array = t->is_array;
    return copy;
}

void free_type_ast(void *p) {
    if (!p)
        return;
    // print(">>>>>>>>free_type_ast 1\n");
    Type *t = (Type *)p;
    // print(">>>>>>>>free_type_ast 2\n");
    free(t->name);
    // print(">>>>>>>>free_type_ast 3\n");
    free(p);
    // print(">>>>>>>>free_type_ast 4\n");
}

/* caller needs to free the return string */
char *type_to_str(Type *t) {
    if (t == NULL)
        return NULL;
    int len = 0;
    if (t->is_const) len += 6;
    if (t->is_struct) len += 7;
    if (t->is_array) len += 2;
    len += strlen(t->name) + 2;
    char *str = (char *)malloc(sizeof(char) * len);
    strcpy(str, "");
    if (t->is_const) strcat(str, "const ");
    if (t->is_struct) strcat(str, "struct ");
    strcat(str, t->name);
    strcat(str, t->is_array ? "[]" : "");
    return str;
}

char exact_match_type(Type *from, Type *to) {
    if (from == NULL || to == NULL
        || strcmp(from->name, to->name)
        || from->is_array != to->is_array
        || from->is_struct != to->is_struct)
        return 0;
    return 1;
}

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