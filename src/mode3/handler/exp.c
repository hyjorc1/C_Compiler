#include "m3global.h"

/* R13: N op N -> N */
Type *handle_ASSIGN(char is_init, Type *t1, char *op, Type *t2) {
    print("handle_ASSIGN\n");
    Type *res = NULL;
    if (!is_init) {
        if (t1->is_const) { // l_val is const then error
            m3err();
            printf("\tCannot assign to item of type %s%s\n", "const ", t1->name);
            return NULL;
        }
    }
    if (t1 != NULL && t2 != NULL) {
        res = widen_type(t1, t2);
        if (res == NULL || widen_rank(t1) > widen_rank(res)) {
            m3err();
            printf("\ttype mismatch\n");
            return NULL;
        }
    } else {
        char *t1_str = t1 == NULL ? strdup("error") : type_to_str(t1);
        char *t2_str = t2 == NULL ? strdup("error") : type_to_str(t2);
        m3err();
        printf("\tOperation not supported: %s %s %s\n", t1_str, op, t2_str);
        return NULL;
    }
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