#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "m3global.h"

Type *find_global_type(char *id) {
    if (m3_global_var_map != NULL)
        return map_get(m3_global_var_map, id);
    return NULL;
}

Type *find_local_type(char *id) {
    if (m3_local_var_map != NULL)
        return map_get(m3_local_var_map, id);
    return NULL;
}

void update_var_list(Variable *var) {
    print("update_var_list\n");
    if (var == NULL)
        return;
    if (m3_is_global) {
        if (m3_global_vars == NULL)
            m3_global_vars = list_new(sizeof(Variable), free_variable_ast);
        list_add_last(m3_global_vars, var);
    } else {
        if (m3_local_vars == NULL)
            m3_local_vars = list_new(sizeof(Variable), free_variable_ast);
        list_add_last(m3_local_vars, var);;
    }
}

Variable *update_type_map(Variable *var) {
    print("update_type_map\n");
    if (var == NULL)
        return NULL;
    
    cur_type->is_array = var->is_array;
    if (m3_is_global) {
        if (m3_global_var_map == NULL)
            m3_global_var_map = new_map();
        map_put(m3_global_var_map, var->name, cur_type);
    } else {
        if (m3_local_var_map == NULL)
            m3_local_var_map = new_map();
        map_put(m3_local_var_map, var->name, cur_type);
    }
    return var;
}

Variable *handle_init_var(Variable *var, Type *r_type) {
    print("handle_init_var\n");
    if (var == NULL)
        return NULL;
    var->is_init = 1;
    if (!handle_ASSIGN(1, cur_type, "+", r_type)) {
        return NULL;
    }
    return var;
}

Variable *handle_var_ident(char *id, char is_array) {
    print("handle_var_ident\n");
    if (m3_is_global) {
        /* declaring a global variable with the 
            same name as another global variable */
        if (find_global_type(id)) {
            m3err();
            printf("\tGlobal variable '%s' is already defined\n", id);
            return NULL;
        }
    } else {
        /* declaring a local variable with the same name 
            as another local variable or parameter of the 
            same function */
        if (find_global_type(id)) {
            m3err();
            printf("\tLocal variable '%s' is already defined\n", id);
            return NULL;
        }
    }
    return new_variable_ast(id, is_array, 0);
}