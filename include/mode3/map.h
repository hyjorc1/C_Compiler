#ifndef MAP_H
#define MAP_H

struct Entry {
    char *key;
    char *val;
    struct Entry *next;
};

typedef struct {
    struct Entry **data;
    int size;
    int capacity;
} HashMap;

HashMap* new_map();

int map_hash(char *key);

void map_put(HashMap* map, char *key, char *value);

char *map_get(HashMap* map, char *key);

void map_remove(HashMap* map, char *key);

void map_free(HashMap* map);

#endif