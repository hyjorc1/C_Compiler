#include "m3global.h"


Function *find_proto_func(char *id) {
    if (m3_global_funcs == NULL)
        return NULL;
    ListNode *cur = m3_global_funcs->first;
    while (cur != NULL) {
        ListNode *next = cur->next;
        Function *f = (Function *)cur->data;
        if (!strcmp(f->name, id) && f->is_proto)
            return f;
        cur = next;
    }
    return NULL;
}

Function *find_func(char *id) {
    if (m3_global_funcs == NULL)
        return NULL;
    ListNode *cur = m3_global_funcs->first;
    while (cur != NULL) {
        ListNode *next = cur->next;
        Function *f = (Function *)cur->data;
        if (!strcmp(f->name, id) && !f->is_proto)
            return f;
        cur = next;
    }
    return NULL;
}

Type *get_func_local_var_type(Function *f, Variable *v) {
    return map_get(f->local_var_map, v->name);
}

int match_func_sig(Function *f1, Function *f2) {
    // check return type
    if (!exact_match_type(f1->return_type, f2->return_type))
        return 0;
    // check parameter types
    if (f1->parameters->size != f2->parameters->size)
        return 0;
    ListNode *n1 = f1->parameters->first;
    ListNode *n2 = f2->parameters->first;
    while (n1 != NULL) {
        Type *t1 = get_func_local_var_type(f1, (Variable *)n1->data);
        Type *t2 = get_func_local_var_type(f2, (Variable *)n2->data);
        if (!exact_match_type(t1, t2))
            return 0;
        n1 = n1->next;
        n2 = n2->next;
    }
    return 1;
}

void handle_func_decl() {
    print("handle_func_decl\n");
    if (cur_fn == NULL)
        return;
    
    cur_fn->parameters = m3_local_vars;
    m3_local_vars = NULL;
}

void handle_func_proto() {
    print("handle_func_proto\n");
    if (cur_fn == NULL)
        return;

    cur_fn->is_proto = 1;
    cur_fn->local_var_map = m3_local_map;
    m3_local_map = NULL;

    Function *f = find_proto_func(cur_fn->name);
    if (f && match_func_sig(f, cur_fn)) {
        m3err();
        fprintf(stderr, "\tProto func %s is already declared\n", cur_fn->name);
        free_function_ast(cur_fn);
    } else {
        if (m3_global_funcs == NULL)
            m3_global_funcs = list_new(sizeof(Function), free_function_ast);
        list_add_last(m3_global_funcs, cur_fn);
    }
    m3_is_global = 1;
    cur_fn = NULL;
}

void handle_func_name(char *id) {
    print("handle_func_name\n");
    if (cur_type == NULL)
        return;

    cur_fn = new_function_ast(cur_type, id, m3lineno);
    cur_type = NULL;
    m3_is_global = 0;
}

void handle_para(char *id, char is_array) {
    print("handle_para\n");
    if (cur_type == NULL || cur_fn == NULL)
        return;
    if (m3_local_map && map_get(m3_local_map, id)) {
        m3err();
        fprintf(stderr, "\tparameter name %s is already defined\n", id);
        return;
    }
    cur_type->is_array = is_array;
    if (m3_local_vars == NULL)
        m3_local_vars = list_new(sizeof(Variable), free_variable_ast);
    list_add_last(m3_local_vars, new_variable_ast(id, is_array, 0));
    if (m3_local_map == NULL)
        m3_local_map = new_map();
    map_put(m3_local_map, id, cur_type);
}

void handle_func_def() {
    print("handle_func_def\n");
    if (cur_fn == NULL)
        return;

    cur_fn->local_var_map = m3_local_map;
    m3_local_map = NULL;
    cur_fn->local_structs = m3_local_structs;
    m3_local_structs = NULL;
    cur_fn->local_vars = m3_local_vars;
    m3_local_vars = NULL;
    cur_fn->statements = m3_local_stmts;
    m3_local_stmts = NULL;

    Function *f = find_func(cur_fn->name);
    if (f) {
        m3err();
        fprintf(stderr, "\tFunction definition %s is already declared\n", cur_fn->name);
        free_function_ast(cur_fn);
    } else {
        if (m3_global_funcs == NULL)
            m3_global_funcs = list_new(sizeof(Function), free_function_ast);
        list_add_last(m3_global_funcs, cur_fn);
    }
    m3_is_global = 1;
    cur_fn = NULL;
}

