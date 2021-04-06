#include "m3global.h"


Function *find_proto_func(char *id) {
    print("find_proto_func\n");
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

Function *find_declared_func(char *id) {
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

int match_para_size(Function *f1, Function *f2) {
    int n1 = f1->parameters == NULL ? 0 : f1->parameters->size;
    int n2 = f2->parameters == NULL ? 0 : f2->parameters->size;
    return n1 == n2 ? 1 : 0;
}

int match_func_sig(Function *f1, Function *f2) {
    print("match_func_sig\n");
    // check return type
    if (!exact_match_type(f1->return_type, f2->return_type))
        return 0;
    // check parameter types
    if (!match_para_size(f1, f2))
        return 0;
    if (f1->parameters && f2->parameters) {
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
    cur_fn->lineno = m3lineno;
    cur_fn->is_proto = 1;
    cur_fn->local_var_map = m3_local_map;
    m3_local_map = NULL;

    Function *f = find_proto_func(cur_fn->name);
    if (f) {
        if (match_func_sig(f, cur_fn)) {
            list_destroy(f->parameters);
            map_free(f->local_var_map);
            f->parameters = cur_fn->parameters;
            f->local_var_map = cur_fn->local_var_map;
            f->lineno = cur_fn->lineno;
            free(cur_fn->return_type);
            free(cur_fn->name);
            free(cur_fn);
        } else {
            m3err();
            fprintf(stderr, "\tFunction %s already declared:\n\t", f->name);
            print_err_func_sig(f);
            fprintf(stderr, " declared in %s near line %d\n", m3_cur_file_name, f->lineno);
            free_function_ast(cur_fn);
        }
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
    if (cur_fn == NULL)
        return;
    if (cur_type == NULL)
        cur_type = new_type_ast("error", 0, 0, 0);
    if (m3_local_map && map_get(m3_local_map, id)) {
        m3err();
        fprintf(stderr, "\tDuplicate parameter name: %s\n", id);
        return;
    }
    cur_type->is_array = is_array;
    cur_type->lineno = m3lineno;
    if (m3_local_vars == NULL)
        m3_local_vars = list_new(sizeof(Variable), free_variable_ast);
    list_add_last(m3_local_vars, new_variable_ast(id, is_array, 0, m3lineno));
    if (m3_local_map == NULL)
        m3_local_map = new_map();
    cur_type->is_global = 0;
    map_put(m3_local_map, id, cur_type);
}

void print_err_func(Function *f) {
    fprintf(stderr, "Error near %s line %d\n", m3_cur_file_name, cur_fn->lineno);
    fprintf(stderr, "Function %s originally declared with different type:\n", f->name);
    print_err_func_sig(f);
    fprintf(stderr, " declared in %s near line %d\n", m3_cur_file_name, f->lineno);
    fprintf(stderr, "replaced with:\n");
    print_err_func_sig(cur_fn);
    fprintf(stderr, " declared in %s near line %d\n", m3_cur_file_name, cur_fn->lineno);
    free_function_ast(cur_fn);
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


    Function *f1 = find_proto_func(cur_fn->name);
    Function *f2 = find_declared_func(cur_fn->name);

    if (f2) {
        if (match_func_sig(cur_fn, f2)) {
            m3err();
            fprintf(stderr, "\tFunction ");
            print_err_func_sig(f2);
            fprintf(stderr, " already defined\n");
            free_function_ast(cur_fn);
        } else {
            print_err_func(f2);
        }
    } else if (f1) {
        if (!match_func_sig(cur_fn, f1)) {
            print_err_func(f1);
        }
    } else {
        if (m3_global_funcs == NULL)
            m3_global_funcs = list_new(sizeof(Function), free_function_ast);
        list_add_last(m3_global_funcs, cur_fn);
        m4handle_func_def();
    }

    m3_is_global = 1;
    cur_fn = NULL;
}

