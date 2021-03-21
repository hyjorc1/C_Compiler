#include "m3global.h"

Struct *find_struct(List* l, char *id) {
    ListNode *cur = l->first;
    while (cur != NULL) {
        ListNode *next = cur->next;
        Struct *s = (Struct *)cur->data;
        if (!strcmp(id, s->name))
            return s;
        cur = next;
    }
    return NULL;
}

Struct *find_global_struct(char *id) {
    if (m3_global_structs != NULL)
        return find_struct(m3_global_structs, id);
    return NULL;
}

Struct *find_local_struct(char *id) {
    if (m3_local_structs != NULL)
        return find_struct(m3_local_structs, id);
    return NULL;
}

void handle_struct_name_decl(char *id) {
    if (m3_is_global) {
        /* It is an error to define two global structs with the same name. */
        Struct *s = find_global_struct(id);
        if (s) {
            m3err();
            printf("\tstruct %s is already defined near %s line %d\n", id, m3_cur_file_name, s->lineno);
            return;
        }
    } else {
        /* It is an error to define two local structs with the same name. */
        Struct *s = find_local_struct(id);
        if (s) {
            m3err();
            printf("\tstruct %s is already defined near %s line %d\n", id, m3_cur_file_name, s->lineno);
            return;
        }
    }
    cur_struct = new_struct_ast(id, list_new(sizeof(Variable), free_variable_ast), new_map(), m3lineno);
}

void update_struct_vars(Variable *v) {
    if (cur_struct == NULL || v == NULL || cur_type == NULL)
        return;
    cur_type->is_array = v->is_array;
    list_add_last(cur_struct->vars, v);
    map_put(cur_struct->local_var_map, v->name, cur_type);
}

void update_structs() {
    if (cur_struct == NULL)
        return;
    if (m3_is_global) {
        if (m3_global_structs == NULL)
            m3_global_structs = list_new(sizeof(Struct), free_struct_ast);
        list_add_last(m3_global_structs, cur_struct);
    } else {
        if (m3_global_structs == NULL)
            m3_global_structs = list_new(sizeof(Struct), free_struct_ast);
        list_add_last(m3_global_structs, cur_struct);
    }
    cur_struct = NULL;
}

Variable *handle_noinit_var_ident(char *id, char is_array) {
    if (cur_struct == NULL)
        return NULL;
    if (map_get(cur_struct->local_var_map, id)) {
        m3err();
        printf("\tLocal variable '%s' is already defined\n", id);
        return NULL;
    }
    return new_variable_ast(id, is_array, 0);
}

Type *handle_struct_type_var(char *id) {
    if (!find_local_struct(id) && !find_global_struct(id)) {
        m3err();
        printf("\tNo definition for 'struct %s'\n", id);
        return NULL;
    }
    return new_type_ast(id, 0, 1, 0);
}