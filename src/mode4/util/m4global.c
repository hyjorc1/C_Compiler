#include "m4global.h"

const char *m4_class_name = NULL;
const char *m4_gvar_tmp_file        = "m4_gvar_tmp_tmp";
const char *m4_gvar_clinit_tmp_file = "m4_gvar_clinit_tmp";
const char *m4_method_tmp_file      = "m4_method_tmp_tmp";
const char *m4_exp_tmp_file         = "m4_exp_tmp";
const char *m4_stmt_tmp_file        = "m4_stmt_tmp";
const char *ident4 = "    ";
const char *ident8 = "        ";

char *last_exp_inst = NULL; // track last exp instruction in methods

int update_depth(int num) {
    if (cur_fn) {
        cur_fn->stack_size += num;
        if (cur_fn->stack_size > cur_fn->stack_max)
            cur_fn->stack_max = cur_fn->stack_size;
    }
    return num;
}

void copy_files(FILE *dest, const char *src_file) {
    if (file_exists(src_file)) {
        FILE *src = fopen(src_file, "r");
        // copy file line by line
        char *line = NULL;
        size_t len = 0;
        while(getline(&line, &len, src) != -1) {
            fprintf(dest, "%s", line);
            free(last_exp_inst);
            last_exp_inst = strdup(line);
        }
        free(line);
        fclose(src);
        remove(src_file);
    }
}

void char2int(Type *t) {
    if (strcmp(t->name, char_str) == 0) {
        free(t->name);
        t->name = strdup(int_str);
    }
}

char *to_ensembly_binary_op_str(char *op) {
    print("to_ensembly_binary_op_str\n");
    if (strcmp(op, "+") == 0 || strcmp(op, "+=") == 0) {
        return "add";
    } else if (strcmp(op, "-") == 0 || strcmp(op, "-=") == 0) {
        return "sub";
    } else if (strcmp(op, "*") == 0 || strcmp(op, "*=") == 0) {
        return "mul";
    } else if (strcmp(op, "/") == 0 || strcmp(op, "/=") == 0) {
        return "div";
    } else if (strcmp(op, "%") == 0) {
        return "rem";
    } else {
        return "-error-";
    }
}

// caller is responsible for the free
char *to_ensembly_type_str(Type *t) {
    print("to_ensembly_type_str\n");
    char *s1 = t->is_array ? "[" : "";
    char *s2 = "";
    if (strcmp(t->name, "void") == 0) {
        s2 = "V";
    } else if (strcmp(t->name, "char") == 0) {
        s2 = "C";
    } else if (strcmp(t->name, "int") == 0) {
        s2 = "I";
    } else if (strcmp(t->name, "float") == 0) {
        s2 = "F";
    }
    return concat(s1, s2);
}

char *to_ensembly_T_str2(Type *t) {
    print("to_ensembly_T_str1\n");
    if (t->is_array) {
        return "a";
    } else if (strcmp(t->name, void_str) == 0) {
        return "";
    } else if (strcmp(t->name, char_str) == 0) {
        return "c";
    } else if (strcmp(t->name, int_str) == 0) {
        return "i";
    } else if (strcmp(t->name, float_str) == 0) {
        return "f";
    } else {
        return "-error-";
    }
}

char *to_ensembly_T_str1(Type *t) {
    print("to_ensembly_T_str1\n");
    if (t->is_array) {
        return "a";
    } else if (strcmp(t->name, void_str) == 0) {
        return "";
    } else if (strcmp(t->name, char_str) == 0
        || strcmp(t->name, int_str) == 0) {
        return "i";
    } else if (strcmp(t->name, float_str) == 0) {
        return "f";
    } else {
        return "-error-";
    }
}

void clear_tmp_files() {
    if (file_exists(m4_gvar_tmp_file)) {
        remove(m4_gvar_tmp_file);
    }
    if (file_exists(m4_gvar_clinit_tmp_file)) {
        remove(m4_gvar_clinit_tmp_file);
    }
    if (file_exists(m4_exp_tmp_file)) {
        remove(m4_exp_tmp_file);
    }
    if (file_exists(m4_stmt_tmp_file)) {
        remove(m4_stmt_tmp_file);
    }
    if (file_exists(m4_method_tmp_file)) {
        remove(m4_method_tmp_file);
    }
}

void m4preprocess() {
    preprocess();
    clear_tmp_files();

    free(last_exp_inst);
    last_exp_inst = NULL;

    // add function int getchar()
    m3_global_funcs = list_new(sizeof(Function), free_function_ast);
    Function *getchar_fn = new_function_ast(new_type_ast(strdup(int_str), 0, 0, 0), strdup("getchar"), -1);
    getchar_fn->is_proto = 1;
    getchar_fn->class_name = strdup("libc");
    list_add_last(m3_global_funcs, getchar_fn);


    // add function int putchar(int c)
    Function *putchar_fn = new_function_ast(new_type_ast(strdup(int_str), 0, 0, 0), strdup("putchar"), -1);
    Variable *v = new_variable_ast(strdup("c"), 0, 0, -1);
    Type *t = new_type_ast(strdup(int_str), 0, 0, 0);
    putchar_fn->parameters = list_add_last(list_new(sizeof(Variable), free_variable_ast), v);
    putchar_fn->local_var_map = new_map();
    map_put(putchar_fn->local_var_map, v->name, t);
    free_type_ast(t);
    putchar_fn->is_proto = 1;
    putchar_fn->class_name = strdup("libc");
    list_add_last(m3_global_funcs, putchar_fn);
}

void m4postprocess() {
    postprocess();
    clear_tmp_files();

    free(last_exp_inst);
    last_exp_inst = NULL;

    list_destroy(m3_global_vars);
    m3_global_vars = NULL;
    list_destroy(m3_global_structs);
    m3_global_structs = NULL;
    list_destroy(m3_global_funcs);
    m3_global_funcs = NULL;
}