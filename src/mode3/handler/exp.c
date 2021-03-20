#include "m3global.h"

/* R13: N op N -> N */
Type *handle_ASSIGN(char is_init, Type *t1, char *op, Type *t2) {
    print("handle_ASSIGN\n");
    if (!is_init) {
        if (t1->is_const) { // l_val is const then error
            m3err();
            printf("\tCannot assign to item of type %s%s\n", "const ", t1->name);
            return NULL;
        }
    }
    print("handle_ASSIGN 1\n");
    Type *res = widen_type(t1, t2);
    print("handle_ASSIGN 2\n");
    if (res == NULL || widen_rank(t1) > widen_rank(res)) {
        m3err();
        printf("\ttype mismatch\n");
        return NULL;
    }
    print("handle_ASSIGN 3\n");
    return res;
}

Type *handle_UBANG(Type *t) {
    Type *res = NULL;
    // if (t != NULL && is_type_N(t)) {
    //     res = new_type_ast(strdup("char"), t->is_const, 0, 0);
    //     free_type_ast(t);
    // } else {
    //     m3err();
    //     // printf("Operation not supported: %s %s\n", "!", t == NULL ? "error" t->name);
    // }
    return res;
}