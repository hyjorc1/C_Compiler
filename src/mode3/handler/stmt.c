#include "m3global.h"

void handle_exp_stmt(Type *t) {
    if (t == NULL)
        return;
    if (m3_local_stmts == NULL)
        m3_local_stmts = list_new(sizeof(Statement), free_statement_ast);
    list_add_last(m3_local_stmts, new_statement_ast(m3lineno, t));
}

void handle_return_stmt(Type *t) {
    if (cur_fn == NULL || t == NULL)
        return;
    char *type = type_to_str(t);
    char *return_type = type_to_str(cur_fn->return_type);
    if (strcmp(void_str, t->name) == 0 && strcmp(void_str, cur_fn->return_type->name) != 0) {
        m3err();
        fprintf(stderr, "\tFunction must return a value of type %s\n", return_type);
    } else if (strcmp(void_str, t->name) != 0 && strcmp(void_str, cur_fn->return_type->name) == 0) {
        m3err();
        fprintf(stderr, "\tReturn with a value (type was %s) in a %s function\n", type, return_type);
    } else if (!widen_match_type(t, cur_fn->return_type)) {
        m3err();
        fprintf(stderr, "\tReturn type was %s, function expects %s\n", type, return_type);
    }
    free(type);
    free(return_type);
}


