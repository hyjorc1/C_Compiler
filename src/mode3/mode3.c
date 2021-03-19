#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

#include "m3global.h"

// void print_m3_global_vars() {
//     if (m3_global_vars == NULL)
//         return;
//     printf("Global variables\n\t");
//     struct node *cur = m3_global_vars->first;
//     while (cur != NULL) {
//         struct node *next = cur->next;
//         printf("%s", cur->data);
//         if (next != NULL)
//             printf(", ");
//         cur = next;
//     }
//     printf("\n\n");
// }

// void print_m3_list_member(char *label, struct list *l) {
//     if (l == NULL || l->size == 0) {
//         return;
//     }
//     struct node *cur = l->first;
//     printf("\t%s", label);
//     while (cur != NULL) {
//         struct node *next = cur->next;
//         printf("%s", cur->data);
//         if (next != NULL)
//             printf(", ");
//         cur = next;
//     }
//     printf("\n");
// }

// void print_m3_global_structs() {
//     if (m3_global_structs == NULL)
//         return;
//     struct struct_node *cur = m3_global_structs->first;
//     while (cur != NULL) {
//         struct struct_node *next = cur->next;
//         printf("Global struct %s\n", cur->name);
//         if (cur->members == NULL || cur->members->size == 0) {
//             printf("\n");
//         } else {
//             print_m3_list_member("", cur->members);
//         }
//         cur = next;
//         printf("\n");
//     }
// }

// void print_m3_funcs() {
//     if (m3_global_funcs == NULL)
//         return;
//     struct func_node *cur = m3_global_funcs->first;
//     while (cur != NULL) {
//         struct func_node *next = cur->next;
//         if (cur->is_proto) {
//             printf("Prototype %s\n", cur->name);
//             print_m3_list_member("Parameters: ", cur->paras);   
//         } else {
//             printf("Function %s\n", cur->name);
//             print_m3_list_member("Parameters: ", cur->paras);
//             print_m3_list_member("Local structs: ", cur->local_structs);
//             print_m3_list_member("Local variables: ", cur->local_vars);
//         }
//         cur = next;
//         printf("\n");
//     }
// }

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

        ListNode *cur = m3_global_vars->first;
        while (cur != NULL) {
            ListNode *next = cur->next;
            Variable *v = (Variable *)cur->data;
            printf("var: '%s'\n", v->name);
            printf("arr: '%d'\n", v->is_array);
            printf("t: '%s'\n", v->type->name);
            cur = next;
        }

        // list_destroy(m3_global_vars);
        // m3_global_vars = NULL;

        cur = m3_global_structs->first;
        while (cur != NULL) {
            ListNode *next = cur->next;
            Struct *s = (Struct *)cur->data;
            printf("struct: '%s'\n", s->name);
            printf("vars size: %zu\n", s->vars->size);
            cur = next;
        }

        // list_destroy(m3_global_structs);
        // m3_global_structs = NULL;

        cur = m3_global_funcs->first;
        while (cur != NULL) {
            ListNode *next = cur->next;
            Function *f = (Function *)cur->data;
            printf("function: '%s'\n", f->name);
            printf("parameters: %lu\n", (f->parameters) ? f->parameters->size : 0);
            printf("isProto: %d\n", f->is_proto);
            cur = next;
        }

        fclose(f);
    }
}




