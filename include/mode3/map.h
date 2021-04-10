#ifndef MAP_H
#define MAP_H
/* -------------------- Type AST -------------------- */

typedef struct {
    char *name;
    char is_const;
    char is_struct;
    char is_array;
    int lineno;
    // mode 4
    int addr;
    char *id;
    int is_global;
    int array_access;
} Type;

Type *new_type_ast(char *name, char is_const, char is_struct, char is_array);

Type *deep_copy_type_ast(Type *t);

void free_type_ast(void *p);

char *type_to_str(Type *t);

char exact_match_type(Type *from, Type *to);

/* -------------- Map <char *key, Type *value> --------------- */

struct Entry {
    char *id;
    Type *type;
    struct Entry *next;
};
typedef struct Entry Entry;

typedef struct {
    struct Entry **data;
    int size;
    int capacity;
} HashMap;

HashMap* new_map();

int map_hash(char *id);

void map_put(HashMap* map, char *id, Type *type);

Type *map_get(HashMap* map, char *id);

void map_remove(HashMap* map, char *id);

void map_free(HashMap* map);

void map_print(HashMap* map);

#endif