#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

#include "m2global.h"

void print_global_vars() {
    if (global_vars == NULL)
        return;
    printf("Global variables\n\t");
    struct node *cur = global_vars->first;
    while (cur != NULL) {
        struct node *next = cur->next;
        printf("%s", cur->data);
        if (next != NULL)
            printf(", ");
        cur = next;
    }
    printf("\n\n");
}

void print_list_member(char *label, struct list *l) {
    struct node *cur = l->first;
    printf("%s", label);
    while (cur != NULL) {
        struct node *next = cur->next;
        printf("%s", cur->data);
        if (next != NULL)
            printf(", ");
        cur = next;
    }
    printf("\n");
}

void print_global_structs() {
    struct struct_node *cur = global_structs->first;
    while (cur != NULL) {
        struct struct_node *next = cur->next;
        printf("Global struct %s\n\t", cur->name);
        print_list_member("Parameters: ", cur->members);
        cur = next;
        printf("\n");
    }
}

void mode2(int argc, char *argv[], int fileIdx) {

    for (int i = fileIdx; i < argc; i++) {
        print("\nstart file %s\n", argv[i]);
        FILE *f = fopen(argv[i], "r");
        if (!f)
            perror(argv[i]);
        m2restart(f);
        m2parse();

        print_global_structs();

        print_global_vars();


        // print_funcs();

        fclose(f);
    }

}





