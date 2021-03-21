#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "m3global.h"

/* 2.4 Extra credit: widening  */
int widen_rank(Type *t) {
    if (!strcmp(t->name, float_str))
        return 0;
    if (!strcmp(t->name, int_str))
        return 1;
    if (!strcmp(t->name, char_str))
        return 2;
    return 3;
}

Type *widen_type(Type *t1, Type *t2) {
    printf("widen_type\n");
    printf("widen_type t1: %s, t2: %s\n", t1->name, t2->name);
    if (is_type_N(t1) && is_type_N(t2)) {
        if (t1->is_const && t2->is_const) {
            if (widen_rank(t1) == 0 || widen_rank(t2) == 0)
                return const_float_type;
            if (widen_rank(t1) == 1 || widen_rank(t2) == 1)
                return const_int_type;
            if (widen_rank(t1) == 2 || widen_rank(t2) == 2)
                return const_char_type;
        } else {
            if (widen_rank(t1) == 0 || widen_rank(t2) == 0)
                return float_type;
            if (widen_rank(t1) == 1 || widen_rank(t2) == 1)
                return int_type;
            if (widen_rank(t1) == 2 || widen_rank(t2) == 2)
                return char_type;
        }
    }
    return NULL;
}