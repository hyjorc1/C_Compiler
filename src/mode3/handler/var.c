#include "m3global.h"

Type *find_global_type(char *id) {
    if (m3_global_map != NULL)
        return map_get(m3_global_map, id);
    return NULL;
}

Type *find_local_type(char *id) {
    if (m3_local_map != NULL)
        return map_get(m3_local_map, id);
    return NULL;
}

void update_var_list(Variable *var) {
    print("update_var_list\n");
    if (var == NULL)
        return;
    if (m3_is_global) {
        print("update m3_global_vars\n");
        if (m3_global_vars == NULL)
            m3_global_vars = list_new(sizeof(Variable), free_variable_ast);
        list_add_last(m3_global_vars, var);
    } else {
        print("update m3_local_vars\n");
        if (m3_local_vars == NULL)
            m3_local_vars = list_new(sizeof(Variable), free_variable_ast);
        list_add_last(m3_local_vars, var);
    }
}

Variable *update_type_map(Variable *var) {
    print("update_type_map\n");
    if (var == NULL || cur_type == NULL)
        return NULL;
    cur_type->is_array = var->is_array;
    cur_type->lineno = var->lineno;
    if (m3_is_global) {
        print("update m3_global_map\n");
        if (m3_global_map == NULL)
            m3_global_map = new_map();
        cur_type->is_global = 1;
        map_put(m3_global_map, var->name, cur_type);
        m4handle_global_var(var->name);
    } else {
        print("update m3_local_map\n");
        if (m3_local_map == NULL)
            m3_local_map = new_map();
        cur_type->is_global = 0;
        map_put(m3_local_map, var->name, cur_type);
    }
    return var;
}

Variable *handle_init_var(Variable *var, Type *rt) {
    print("handle_init_var\n");
    if (var == NULL || cur_type == NULL)
        return NULL;
    update_type_map(var);
    Type *lt = m3_is_global ? map_get(m3_global_map, var->name) : 
    map_get(m3_local_map, var->name);
    lt = deep_copy_type_ast(lt);
    if (rt != NULL && handle_assign_exp(1, lt, "=", rt)) {
        var->is_init = 1;
        if (m3_is_global) {
            m4handle_global_var_init(var->name);
        }
    }
    return var;
}

Variable *handle_var_ident(char *id, char is_array) {
    print("handle_var_ident\n");
    if (m3_is_global) {
        /* declaring a global variable with the 
            same name as another global variable */
        Type *t = find_global_type(id);
        if (t) {
            m3err();
            fprintf(stderr, "\tglobal variable %s already declared as:\n", id);
            char *t_str = type_to_str(t);
            fprintf(stderr, "\t%s %s (near line %d in file %s)\n", t_str, id, t->lineno, m3_cur_file_name);
            free(t_str);
            return NULL;
        }
    } else {
        /* declaring a local variable with the same name 
            as another local variable or parameter of the 
            same function */
        Type *t = find_local_type(id);
        if (t) {
            m3err();
            fprintf(stderr, "\tlocal variable %s already declared as:\n", id);
            char *t_str = type_to_str(t);
            fprintf(stderr, "\t%s %s (near line %d in file %s)\n", t_str, id, t->lineno, m3_cur_file_name);
            free(t_str);
            return NULL;
        }
    }
    return new_variable_ast(id, is_array, 0, m3lineno);
}