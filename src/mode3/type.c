#include <stdio.h>
#include <stdlib.h>
#include "type.h"

Type *new_type(char *name, char is_const, char is_array) {
    Type *t = (Type *)malloc(sizeof(Type));
    t->name = name;
    t->is_const = is_const;
    t->is_array = is_array;
    return t;
}

void free_type(Type *t) {
    free(t->name);
    free(t);
}