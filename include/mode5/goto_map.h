#ifndef GOTO_MAP_H
#define GOTO_MAP_H

/* -------------- Map <int key, int val> --------------- */

struct GotoEntry {
    int key;
    int val;
    struct GotoEntry *next;
};

typedef struct GotoEntry GotoEntry;

typedef struct {
    GotoEntry **data;
    int size;
    int capacity;
} GotoMap;

GotoMap* new_gotomap();

void gotomap_put(GotoMap* map, int key, int val);

int gotomap_get(GotoMap* map, int key);

void gotomap_remove(GotoMap* map, int key);

void gotomap_free(GotoMap* map);

void gotomap_print(GotoMap* map);

#endif