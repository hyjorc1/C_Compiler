#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

#include "m2global.h"


void print_str(void *x) {
    char *data = *(char **)x;
    printf("%s, ", data);
    free(data);
}

void print_global_struct(void *x) { 
    struct struct_node *data = *(struct struct_node **)x;
    printf("Global struct %s\n\t", data->name);
    free(data->name);
    if (data->members) {
        gll_each(data->members, &print_str);
        free(data->members);
    }
    free(data);
    printf("\n\n");
}

void print_global_structs() {
    if (!global_structs)
        return;
    gll_each(global_structs, &print_global_struct);
    gll_destroy(global_structs);
}

void print_global_vars() {
    if (!global_vars)
        return;
    printf("Global variables\n\t");
    gll_each(global_vars, &print_str);
    gll_destroy(global_vars);
    printf("\n\n");
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
        gll_each(data->paras, &print_str);
        free(data->paras);
        printf("\n\t");
    }
    if (data->local_structs) {
        printf("Local structs: ");
        gll_each(data->local_structs, &print_str);
        free(data->local_structs);
        printf("\n\t");
    }
    if (data->local_vars) {
        printf("Local variables: ");
        gll_each(data->local_vars, &print_str);
        free(data->local_vars);
    }
    printf("\n\n");
}

void print_funcs() {
    if (!funcs)
        return;
    gll_each(funcs, &print_func);
    gll_destroy(funcs);
};

void mode2(int argc, char *argv[], int fileIdx) {
    for (int i = fileIdx; i < argc; i++) {
        print("\nstart file %s\n", argv[i]);
        FILE *f = fopen(argv[i], "r");
        if (!f)
            perror(argv[i]);
        m2restart(f);
        int code = m2parse();
        // global structs
        print_global_structs();
        // global vars
        print_global_vars();
        // funcs
        print_funcs();

        printf("yyparse returned %d\n", code);
        fclose(f);
    }
}





