#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

#include "m3global.h"

void print_m3_global_vars() {
    if (m3_global_vars == NULL)
        return;
    printf("Global variables\n\t");
    struct node *cur = m3_global_vars->first;
    while (cur != NULL) {
        struct node *next = cur->next;
        printf("%s", cur->data);
        if (next != NULL)
            printf(", ");
        cur = next;
    }
    printf("\n\n");
}

void print_m3_list_member(char *label, struct list *l) {
    if (l == NULL || l->size == 0) {
        return;
    }
    struct node *cur = l->first;
    printf("\t%s", label);
    while (cur != NULL) {
        struct node *next = cur->next;
        printf("%s", cur->data);
        if (next != NULL)
            printf(", ");
        cur = next;
    }
    printf("\n");
}

void print_m3_global_structs() {
    if (m3_global_structs == NULL)
        return;
    struct struct_node *cur = m3_global_structs->first;
    while (cur != NULL) {
        struct struct_node *next = cur->next;
        printf("Global struct %s\n", cur->name);
        if (cur->members == NULL || cur->members->size == 0) {
            printf("\n");
        } else {
            print_m3_list_member("", cur->members);
        }
        cur = next;
        printf("\n");
    }
}

void print_m3_funcs() {
    if (m3_global_funcs == NULL)
        return;
    struct func_node *cur = m3_global_funcs->first;
    while (cur != NULL) {
        struct func_node *next = cur->next;
        if (cur->is_proto) {
            printf("Prototype %s\n", cur->name);
            print_m3_list_member("Parameters: ", cur->paras);   
        } else {
            printf("Function %s\n", cur->name);
            print_m3_list_member("Parameters: ", cur->paras);
            print_m3_list_member("Local structs: ", cur->local_structs);
            print_m3_list_member("Local variables: ", cur->local_vars);
        }
        cur = next;
        printf("\n");
    }
}

void mode3(int argc, char *argv[], int fileIdx) {
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

        print_m3_global_structs();
        destroy_struct_list(m3_global_structs);
        m3_global_structs = NULL;

        print_m3_global_vars();
        destroy_list(m3_global_vars);
        m3_global_vars = NULL;

        print_m3_funcs();
        destroy_func_list(m3_global_funcs);
        m3_global_funcs = NULL;

        fclose(f);
    }
}





