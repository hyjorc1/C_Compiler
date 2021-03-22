#include "m3global.h"

/* R13: N op N -> N */
Type *handle_ASSIGN(char is_init, Type *t1, char *op, Type *t2) {
    print("handle_ASSIGN\n");
    Type *res = NULL;
    if (!is_init) {
        if (t1->is_const) { // l_val is const then error
            m3err();
            fprintf(stderr, "\tCannot assign to item of type %s%s\n", "const ", t1->name);
            return NULL;
        }
    }
    if (t1 != NULL && t2 != NULL) {
        res = widen_type(t1, t2);
        if (res == NULL || widen_rank(t1) > widen_rank(res)) {
            m3err();
            fprintf(stderr, "\ttype mismatch\n");
            return NULL;
        }
    } else {
        char *t1_str = t1 == NULL ? strdup("error") : type_to_str(t1);
        char *t2_str = t2 == NULL ? strdup("error") : type_to_str(t2);
        m3err();
        fprintf(stderr, "\tOperation not supported: %s %s %s\n", t1_str, op, t2_str);
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
    //     // fprintf(stderr, "Operation not supported: %s %s\n", "!", t == NULL ? "error" t->name);
    // }
    return res;
}

void handle_cond_exp(char *msg, Type *t) {
    print("handle_cond_exp\n");
    if (t == NULL)
        return;
    if (!is_type_N(t)) {
        m3err();
        char *type_str = type_to_str(t);
        fprintf(stderr, "\tCondition of %s has invalid type: %s\n", msg, type_str);
        free(type_str);
    }
}

Type *handle_func_call(char *id) {
    Function *f = find_proto_func(id);
    return NULL;
}

void handle_exp_list(Type *t) {
    if (t == NULL)
        return;
    if (m3_local_types == NULL)
        m3_local_types = list_new(sizeof(Type), free_type_ast);
    list_add_last(m3_local_types, t);
}