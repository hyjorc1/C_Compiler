#ifndef TYPE_H
#define TYPE_H

typedef struct {
    char *name;
    char is_const;
    char is_array;
} Type;

Type *new_type(char *name, char is_const, char is_array);

void free_type(Type *t);

#endif