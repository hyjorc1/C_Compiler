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
        if (find_global_struct(id)) {
            m3err();
            printf("\tGlobal struct '%s' is already defined\n", id);
            return;
        }
    } else {
        if (find_local_struct(id)) {
            m3err();
            printf("\tLocal struct '%s' is already defined\n", id);
            return;
        }
    }
    cur_struct = new_struct_ast(id, list_new(sizeof(Variable), free_variable_ast), new_map());
}

void update_struct_var(Variable *v) {
    if (cur_struct == NULL)
        return;
    list_add_last(cur_struct->vars, v);
    map_put(cur_struct->local_var_map, v->name, cur_type);
}

void handle_struct_decl(char *id) {
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
}   