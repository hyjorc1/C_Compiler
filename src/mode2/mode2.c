#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

#include "m2global.h"

void print_strs(gll_t *list) {
    gll_node_t *currNode = list->first;
    while (currNode != NULL) {
        gll_node_t *nextNode = currNode->next;
        char *data = *(char **)currNode->data;
        printf("%s", data);
        free(data);
        if (nextNode != NULL)
            printf(", ");
        currNode = nextNode;
    }
}

void print_global_struct(void *x) { 
    struct struct_node *data = *(struct struct_node **)x;
    printf("Global struct %s\n\t", data->name);
    free(data->name);
    if (data->members) {
        print_strs(data->members);
        gll_destroy(data->members);
    }
    free(data);
    printf("\n\n");
}

void print_global_structs() {
    if (!global_structs)
        return;
    gll_each(global_structs, print_global_struct);
    gll_clear(global_structs);
}

void print_global_vars() {
    if (!global_vars)
        return;
    printf("Global variables\n\t");
    print_strs(global_vars);
    printf("\n\n");
    gll_clear(global_vars);
}

void print_func(void *x) {
    struct func_node *data = *(struct func_node **)x;
    if (data->ast_type) {
        printf("Function %s\n\t", data->name);
    } else {
        printf("Prototype %s\n\t", data->name);
    }
    if (data->paras) {
        printf("Parameters: ");
        print_strs(data->paras);
        gll_destroy(data->paras);
        printf("\n\t");
    }
    if (data->local_structs) {
        printf("Local structs: ");
        print_strs(data->local_structs);
        gll_destroy(data->local_structs);
        printf("\n\t");
    }
    if (data->local_vars) {
        printf("Local variables: ");
        print_strs(data->local_vars);
        gll_destroy(data->local_vars);
    }
    free(data);
    printf("\n\n");
}

void print_funcs() {
    if (!funcs)
        return;
    gll_each(funcs, print_func);
    gll_clear(funcs);
};



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
        print_funcs();

        fclose(f);
    }
}





