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
    if (!match_type_ast(cur_fn->return_type, t)) {
        char *type = type_to_str(t);
        char *return_type = type_to_str(cur_fn->return_type);
        m3err();
        fprintf(stderr, "\tReturn %s in a function of type %s\n", type, return_type);
        free(type);
        free(return_type);
    }
}


