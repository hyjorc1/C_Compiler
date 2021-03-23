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

void preprocess() {

}

void postprocess() {
    if (cur_type) {
        print("cur_type is not NULL\n");
        free(cur_type);
        cur_type = NULL;
    }
    if (m3_local_vars) {
        print("m3_local_vars is not NULL\n");
        list_destroy(m3_local_vars);
        m3_local_vars = NULL;
    }
    if (m3_local_map) {
        print("m3_local_map is not NULL\n");
        map_free(m3_local_map);
        m3_local_map = NULL;
    }
    if (cur_fn) {
        print("cur_fn is not NULL\n");
        free_function_ast(cur_fn);
        cur_fn = NULL;
    }
    if (m3_local_stmts) {
        print("m3_local_stmts is not NULL\n");
        list_destroy(m3_local_stmts);
        m3_local_stmts = NULL;
    }
}

char is_type_N(Type *t) { // N ∈ {char, int, float}
    if (t == NULL || t->is_array || t->is_struct)
        return 0;
    char *type = t->name;
    if (!strcmp(type, char_str) || !strcmp(type, int_str) || !strcmp(type, float_str))
        return 1;
    return 0;
}

char is_type_I(Type *t) { //  I ∈ {char, int}
    if (t == NULL || t->is_array || t->is_struct)
        return 0;
    char *type = t->name;
    if (!strcmp(type, char_str) || !strcmp(type, int_str))
        return 1;
    return 0;
}

int widen_rank(Type *t) {
    if (!strcmp(t->name, float_str))
        return 0;
    if (!strcmp(t->name, int_str))
        return 1;
    if (!strcmp(t->name, char_str))
        return 2;
    return -1;
}

char widen_match_type(Type *from, Type *to) {
    if (exact_match_type(from, to))
        return 1;
    if (is_type_N(from) && is_type_N(to) && widen_rank(from) > widen_rank(to))
        return 1;
    return 0;
}
