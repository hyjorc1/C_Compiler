#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "m3global.h"

void m3error(const char* msg) {
    fprintf(stderr, "Error near %s line %d text '%s'\n\t%s\n", m3_cur_file_name, m3lineno, m3text, msg);
}

void m3err() {
    fprintf(stderr, "Error near %s line %d\n", m3_cur_file_name, m3lineno);
}

void m3dprint(const char* s1, const char* s2) {
    if (debug) {
        fprintf(stdout, "line %d at text '%s' as '%s' => '%s'\n", m3lineno, m3text, s1, s2);
    }
}

void preprocess_const_types() {
    char_type = new_type_ast(strdup(char_str), 0, 0, 0);
    const_char_type = new_type_ast(strdup(char_str), 1, 0, 0);
    const_string_type = new_type_ast(strdup(char_str), 1, 0, 1);
    int_type = new_type_ast(strdup(int_str), 0, 0, 0);
    const_int_type = new_type_ast(strdup(int_str), 1, 0, 0);
    float_type = new_type_ast(strdup(float_str), 0, 0, 0);
    const_float_type = new_type_ast(strdup(float_str), 1, 0, 0);
}

void free_const_types() {
    free_type_ast(char_type);
    free_type_ast(const_char_type);
    free_type_ast(const_string_type);
    free_type_ast(int_type);
    free_type_ast(const_int_type);
    free_type_ast(float_type);
    free_type_ast(const_float_type);
}

char is_type_N(Type *t) { // N ∈ {char, int, float}
    char *type = t->name;
    if (!strcmp(type, char_str) || !strcmp(type, int_str) || !strcmp(type, float_str))
        return 1;
    return 0;
}

char is_type_I(Type *t) { //  I ∈ {char, int}
    char *type = t->name;
    if (!strcmp(type, char_str) || !strcmp(type, float_str))
        return 1;
    return 0;
}

