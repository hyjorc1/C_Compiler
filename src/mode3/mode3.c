#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

#include "m3global.h"

void print_var(Variable *v, HashMap *map) {
    char *type = type_to_str(map_get(map, v->name));
    printf("\t%s %s%s\n", type, v->name, v->is_init ? " (initialized)" : "");
    free(type);
}

void m3_print_global_vars() {
    printf("Global variables\n");
    if (m3_global_vars != NULL) {
        ListNode* cur = m3_global_vars->first;
        while (cur != NULL) {
            ListNode *next = cur->next;
            print_var((Variable *)cur->data, m3_global_map);
            cur = next;
        }
    }
    printf("\n");
    list_destroy(m3_global_vars);
    map_free(m3_global_map);
}

void m3_print_struct(Struct *s) {
    if (s == NULL)
        return;
    printf("Global struct %s\n", s->name);
    ListNode* cur = s->vars->first;
    while (cur != NULL) {
        ListNode *next = cur->next;
        print_var((Variable *)cur->data, s->local_var_map);
        cur = next;
    }
    printf("\n");
}

void m3_print_global_structs() {
    if (m3_global_structs == NULL)
        return;
    ListNode* cur = m3_global_structs->first;
    while (cur != NULL) {
        ListNode *next = cur->next;
        m3_print_struct((Struct *)cur->data);
        cur = next;
    }
    list_destroy(m3_global_structs);
}

void m3_print_parameters(Function *f) {
    printf("\tParameters\n");
    if (f->parameters) {
        ListNode* cur = f->parameters->first;
        while (cur != NULL) {
            ListNode *next = cur->next;
            printf("\t");
            print_var((Variable *)cur->data, f->local_var_map);
            cur = next;
        }
    }
    printf("\n");
}

void m3_print_local_struct(Struct *s) {
    if (s == NULL)
        return;
    printf("\tLocal struct %s\n", s->name);
    ListNode* cur = s->vars->first;
    while (cur != NULL) {
        ListNode *next = cur->next;
        printf("\t");
        print_var((Variable *)cur->data, s->local_var_map);
        cur = next;
    }
    printf("\n");
}

void m3_print_local_structs(Function *f) {
    if (f->local_structs && f->local_structs->size > 0) {
        ListNode* cur = f->local_structs->first;
        while (cur != NULL) {
            ListNode *next = cur->next;
            m3_print_local_struct((Struct *)cur->data);
            cur = next;
        }
    }
}

void m3_print_local_vars(Function *f) {
    printf("\tLocal variables\n");
    if (f->local_vars) {
        ListNode* cur = f->local_vars->first;
        while (cur != NULL) {
            ListNode *next = cur->next;
            printf("\t");
            print_var((Variable *)cur->data, f->local_var_map);
            cur = next;
        }
    }
    printf("\n");
}

void m3_print_statements(Function *f) {
    printf("\tStatements\n");
    if (f->statements) {
        ListNode* cur = f->statements->first;
        while (cur != NULL) {
            ListNode *next = cur->next;
            Statement *s = (Statement *)cur->data;
            char *type = type_to_str(s->type);
            printf("\t\tExpression on line %d has type %s\n", s->lineno, type);
            free(type);
            cur = next;
        }
    }
    printf("\n");
}

void m3_print_func(Function *f) {
    if (f == NULL || f->is_proto)
        return;
    char *type = type_to_str(f->return_type);
    printf("Function %s, returns %s\n", f->name, type);
    free(type);
    m3_print_parameters(f);
    m3_print_local_structs(f);
    m3_print_local_vars(f);
    m3_print_statements(f);
}

void m3_print_global_funcs() {
    if (m3_global_funcs == NULL)
        return;
    ListNode* cur = m3_global_funcs->first;
    while (cur != NULL) {
        ListNode *next = cur->next;
        m3_print_func((Function *)cur->data);
        cur = next;
    }
    list_destroy(m3_global_funcs);
}

void mode3(int argc, char *argv[], int fileIdx) {
    
    preprocess();

    for (int i = fileIdx; i < argc; i++) {
        print("\nstart file %s\n", argv[i]);
        FILE *f = fopen(argv[i], "r");
        if (!f) {
            perror(argv[i]);
            return;
        }
        m3_cur_file_name = argv[i];
        m3lineno = 1;
        m3restart(f);
        print("Parse return %d\n", m3parse());

        m3_print_global_structs();
        m3_print_global_vars();
        m3_print_global_funcs();

        fclose(f);
    }

    postprocess();
}




