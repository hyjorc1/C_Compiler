#include "m4global.h"

const char *m4_class_name = NULL;
const char *m4_gvar_tmp_file = "mode4_gvar_tmp_tmp";
const char *m4_gvar_clinit_tmp_file = "mode4_gvar_clinit_tmp";
const char *m4_method_tmp_file = "mode4_method_tmp_tmp";
const char *m4_exp_tmp_file = "mode4_exp_tmp";
const char *m4_stmt_tmp_file = "mode4_stmt_tmp";
const char *ident4 = "    ";
const char *ident8 = "        ";

char *last_exp_inst = NULL; // track last exp instruction in methods

void m4increment(Function *f) {
    if (f) {
        f->depth++;
        if (f->depth > f->max)
            f->max = f->depth;
        stmt_stack_depth++;
        FILE *f = get_file(m4_exp_tmp_file);
        fprintf(f, "%s;; depth++\n", ident8);
        fclose(f);
    }
}

void m4decrement(Function *f) {
    if (f) {
        f->depth--;
        stmt_stack_depth--;
        FILE *f = get_file(m4_exp_tmp_file);
        fprintf(f, "%s;; depth--\n", ident8);
        fclose(f);
    }
}

void m4hanlde_exp_stmt() {
    if (mode != 4)
        return;
    print("m4hanlde_exp_stmt\n");
    FILE *f = get_file(m4_exp_tmp_file);
    while (stmt_stack_depth > 0) {
        fprintf(f, "%spop\n", ident8);
        stmt_stack_depth--;
    }
    fclose(f);
}

void m4handle_arr_init(char *id, char *num) {
    if (mode != 4)
        return;
    print("m4handle_arr_init\n");
    m4handle_int(num);
    FILE *f = get_file(m4_exp_tmp_file);
    fprintf(f, "%snewarray %s\n", ident8, cur_type->name);
    if (m3_is_global) {
        char *type_str = to_ensembly_type_str(cur_type);
        fprintf(f, "%sputstatic Field %s %s [%s\n", ident8, m4_class_name, id, type_str);
        free(type_str);
    } else {
        int addr = m3_local_map == NULL ? 0 : m3_local_map->size;
        fprintf(f, "%sastore %d ; store to %s\n", ident8, addr, id);
    }
    m4decrement(cur_fn);
    m4decrement(cur_fn);
    m4decrement(cur_fn);
    fclose(f);
    if (m3_is_global)
        m4handle_global_var_init(id);
}

void m4handle_global_var(char *id) {
    if (mode != 4)
        return;
    print("m4_update_global_vars\n");
    FILE *f = get_file(m4_gvar_tmp_file);
    char *type_str = to_ensembly_type_str(cur_type);
    fprintf(f, ".field static %s %s\n", id, type_str);
    free(type_str);
    fclose(f);
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

void m4handle_global_var_init(char *id) {
    if (mode != 4)
        return;
    print("m4handle_global_var_init\n");
    FILE *dest = get_file(m4_gvar_clinit_tmp_file);
    fprintf(dest, "%s; Initializing %s\n", ident8, id);
    // copy exp instructions
    copy_files(dest, m4_exp_tmp_file);
    fclose(dest);
}

void m4handle_func_def() {
    if (mode != 4)
        return;
    print("m4handle_func_def\n");
    FILE *dest = get_file(m4_method_tmp_file);
    // first line
    fprintf(dest, ".method public static %s : (", cur_fn->name);
    // add parameter types
    if (cur_fn->parameters) {
        ListNode *cur = cur_fn->parameters->first;
        while (cur != NULL) {
            Variable *v = (Variable *)cur->data;
            Type *t = map_get(cur_fn->local_var_map, v->name);
            char *type_str = to_ensembly_type_str(t);
            fprintf(dest, "%s", type_str);
            free(type_str);
            cur = cur->next;
        }
    }
    char *return_type_str = to_ensembly_type_str(cur_fn->return_type);
    fprintf(dest, ")%s\n", return_type_str);
    free(return_type_str);

    // second line
    int var_num = (cur_fn->parameters ? cur_fn->parameters->size : 0)
        + (cur_fn->local_vars ? cur_fn->local_vars->size : 0);
    fprintf(dest, "    .code stack %d locals %d\n", cur_fn->max, var_num);

    // copy exp instructions
    copy_files(dest, m4_exp_tmp_file);

    // end
    if (last_exp_inst == NULL
        || (strcmp(cur_fn->return_type->name, void_str) == 0
            && strcmp(last_exp_inst, "        return\n") != 0))
        fprintf(dest, "        return\n");
    free(last_exp_inst);
    last_exp_inst = NULL;

    fprintf(dest, "    .end code\n");
    fprintf(dest, ".end method\n\n");

    fclose(dest);
}

void m4handle_return_stmt(Type *t) {
    if (mode != 4)
        return;
    print("m4handle_return_stmt\n");
    FILE *f = get_file(m4_exp_tmp_file);
    fprintf(f, "%s%sreturn\n", ident8, to_ensembly_T_str1(t));
    fclose(f);
    m4decrement(cur_fn);
}

void m4handle_int(char *val) {
    print("m4handle_int\n");
    if (mode != 4)
        return;
    FILE *f = get_file(m4_exp_tmp_file);
    fprintf(f, "%sldc %s\n", ident8, val);
    fclose(f);
    m4increment(cur_fn);
}
void m4handle_real(char *val) {
    if (mode != 4)
        return;
    FILE *f = get_file(m4_exp_tmp_file);
    fprintf(f, "%sldc +%sf\n", ident8, val);
    fclose(f);
    m4increment(cur_fn);
}

void m4handle_str(char *val) {
    if (mode != 4)
        return;
    FILE *f = get_file(m4_exp_tmp_file);
    int char_cnt = strlen(val) - 2;
    val++;
    fprintf(f, "%sldc '%.*s'\n", ident8, char_cnt, val);
    fprintf(f, "%sinvokevirtual Method java/lang/String toCharArray ()[C\n", ident8);
    fclose(f);
    m4increment(cur_fn);
}

void m4handle_char(char *val) {
    if (mode != 4)
        return;
    FILE *f = get_file(m4_exp_tmp_file);
    fprintf(f, "%sbipush %d\n", ident8, val[1]);
    fclose(f);
    m4increment(cur_fn);
}

void m4handle_assign_exp(Type *lt, char *op, Type *res) {
    if (mode != 4)
        return;
    print("m4handle_assign_exp\n");

    FILE *f = get_file(m4_exp_tmp_file);

    if (strcmp(op, "=") != 0) {
        char2int(res);
        char *type_str = to_ensembly_T_str1(res);
        char *op_str = to_ensembly_binary_op_str(op);
        fprintf(f, "%s%s%s\n", ident8, type_str, op_str);
    }

    char *dup_str = lt->array_access ? "dup_x2" : "dup";
    fprintf(f, "%s%s\n", ident8, dup_str);
    m4increment(cur_fn);

    if (lt->array_access) {
        fprintf(f, "%s%sastore\n", ident8, to_ensembly_T_str1(lt));
        m4decrement(cur_fn);
        m4decrement(cur_fn);
        m4decrement(cur_fn);
    } else if (lt->is_global) {
        char *type_str = to_ensembly_type_str(lt);
        fprintf(f, "%sputstatic Field %s %s %s\n", ident8, m4_class_name, lt->id, type_str);
        free(type_str);
        m4decrement(cur_fn);
    } else {
        fprintf(f, "%s%sstore %d ; store to %s\n", ident8, to_ensembly_T_str1(lt), lt->addr, lt->id);
        m4decrement(cur_fn);
    }
    fclose(f);
}

void m4handle_func_call_exp(Function *fn) {
    if (mode != 4)
        return;
    print("m4handle_func_call_exp\n");
    FILE *f = get_file(m4_exp_tmp_file);
    const char *class_name = fn->class_name ? fn->class_name : m4_class_name;
    fprintf(f, "%sinvokestatic Method %s %s (", ident8, class_name, fn->name);
    print("m4handle_func_call_exp 1\n");
    // add parameter types
    if (fn->parameters) {
        ListNode *cur = fn->parameters->first;
        print("m4handle_func_call_exp 2\n");
        while (cur != NULL) {
            m4decrement(cur_fn);
            Variable *v = (Variable *)cur->data;
            Type *t = map_get(fn->local_var_map, v->name);
            char *type_str = to_ensembly_type_str(t);
            fprintf(f, "%s", type_str);
            free(type_str);
            cur = cur->next;
        }
    }
    print("m4handle_func_call_exp 3\n");
    char *return_type_str = to_ensembly_type_str(fn->return_type);
    fprintf(f, ")%s\n", return_type_str);
    free(return_type_str);
    fclose(f);
    m4increment(cur_fn);
}

void m4handle_root_exp_before() {
    if (mode != 4)
        return;
    print("m4handle_root_exp_before\n");
    stmt_stack_depth = 0;
    FILE *dest = get_file(m4_exp_tmp_file);
    fprintf(dest, "%s;; %s %d expression\n", ident8, m4_class_name, m3lineno);
    fclose(dest);
}

Type *m4handle_lval(Type *t) {
    if (mode != 4)
        return t;
    print("m4handle_lval\n");
    FILE *f = get_file(m4_exp_tmp_file);
    if (t->array_access) {
        if (cur_op)
            fprintf(f, "%sdup2\n", ident8);
        fprintf(f, "%s%saload\n", ident8, to_ensembly_T_str2(t));
    } else if (t->is_global) {
        char *type_str = to_ensembly_type_str(t);
        fprintf(f, "%sgetstatic Field %s %s %s\n", ident8, m4_class_name, t->id, type_str);
        free(type_str);
    } else {
        fprintf(f, "%s%sload %d ; load from %s\n", ident8, to_ensembly_T_str1(t), t->addr, t->id);
    }
    m4increment(cur_fn);
    fclose(f);
    return t;
}

void m4handle_ulval(Type *t, char *op) {
    if (mode != 4)
        return;
    m4handle_lval(t);
    print("m4handle_ulval\n");
    FILE *f = get_file(m4_exp_tmp_file);

    fprintf(f, "%siconst_1\n", ident8);
    m4increment(cur_fn);

    char *inst = strcmp(op, "++") == 0 ? "iadd" : "isub";
    fprintf(f, "%s%s\n", ident8, inst);
    m4decrement(cur_fn);
    fclose(f);
}

void m4handle_utilde() {
    if (mode != 4)
        return;
    print("m4handle_utilde\n");
    FILE *f = get_file(m4_exp_tmp_file);
    fprintf(f, "%siconst_m1\n", ident8);
    m4increment(cur_fn);
    fprintf(f, "%sixor\n", ident8);
    m4decrement(cur_fn);
    fclose(f);
}

void m4hanlde_uminus(Type *t) {
    if (mode != 4)
        return;
    print("m4handle_utilde\n");
    FILE *f = get_file(m4_exp_tmp_file);
    fprintf(f, "%s%sneg\n", ident8, to_ensembly_T_str1(t));
    fclose(f);
}

void m4handle_cast_exp(Type *t1, Type *t2) {
    if (mode != 4)
        return;
    print("m4handle_cast_exp\n");
    FILE *f = get_file(m4_exp_tmp_file);
    fprintf(f, "%s%s2%s\n", ident8, to_ensembly_T_str2(t2), to_ensembly_T_str2(t1));
    fclose(f);
}

void m4handle_r8_exp(Type *t, char *op) {
    if (mode != 4)
        return;
    print("m4handle_r8_exp\n");
    char2int(t);
    FILE *f = get_file(m4_exp_tmp_file);
    char *type_str = to_ensembly_T_str1(t);
    char *op_str = to_ensembly_binary_op_str(op);
    fprintf(f, "%s%s%s\n", ident8, type_str, op_str);
    fclose(f);
}

void m4handle_r9_exp(Type *t, char *op) {
    if (mode != 4)
        return;
    print("m4handle_r9_exp\n");
    FILE *f = get_file(m4_exp_tmp_file);
    char2int(t);
    char *type_str = to_ensembly_T_str1(t);
    char *op_str = to_ensembly_binary_op_str(op);
    fprintf(f, "%s%s%s\n", ident8, type_str, op_str);
    fclose(f);
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
    getchar_fn->is_proto = 0;
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
    putchar_fn->is_proto = 0;
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