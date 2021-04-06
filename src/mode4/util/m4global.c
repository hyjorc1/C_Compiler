#include "m4global.h"

const char *m4_class_name = NULL;
const char *global_var_tmp_file = "mode4_gvar_tmp";
const char *global_var_clinit_tmp_file = "mode4_gvc_tmp";
const char *global_method_tmp_file = "mode4_gm_tmp";
const char *global_exp_tmp_file = "mode4_ge_tmp";
const char *ident4 = "    ";
const char *ident8 = "        ";

char *last_exp_inst = NULL; // track last exp instruction in methods

void m4handle_global_var(char *id) {
    if (mode != 4)
        return;
    print("m4_update_global_vars\n");
    FILE *f = get_file(global_var_tmp_file);
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
            print("exp file line: '%s'", line);
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
    FILE *dest = get_file(global_var_clinit_tmp_file);
    fprintf(dest, "%s; Initializing %s\n", ident8, id);
    // copy exp instructions
    copy_files(dest, global_exp_tmp_file);
    // update static field instruction
    char *type_str = to_ensembly_type_str(cur_type);
    fprintf(dest, "%sputstatic Field %s %s %s\n", ident8, m4_class_name, id, type_str);
    free(type_str);

    fclose(dest);
}

void m4handle_func_def() {
    if (mode != 4)
        return;
    print("m4handle_func_def\n");
    FILE *dest = get_file(global_method_tmp_file);
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
    fprintf(dest, "    .code stack %d locals %d\n", 2, var_num); // TODO: need to update stack depth

    // copy exp instructions
    copy_files(dest, global_exp_tmp_file);

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
    FILE *f = get_file(global_exp_tmp_file);
    fprintf(f, "%s%sreturn\n", ident8, to_ensembly_T_str(t));
    fclose(f);
}

void m4handle_int(char *val) {
    print("m4handle_int\n");
    if (mode != 4)
        return;
    FILE *f = get_file(global_exp_tmp_file);
    fprintf(f, "%siconst_%s\n", ident8, val);
    fclose(f);
}
void m4handle_real(char *val) {
    if (mode != 4)
        return;
    FILE *f = get_file(global_exp_tmp_file);
    fprintf(f, "%sldc +%sf\n", ident8, val);
    fclose(f);
}
void m4handle_char(char *val) {
    if (mode != 4)
        return;
    FILE *f = get_file(global_exp_tmp_file);
    fprintf(f, "%sbipush %d\n", ident8, val[1]);
    fclose(f);
}

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

char *to_ensembly_T_str(Type *t) {
    print("to_ensembly_T_str\n");
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

void m4preprocess() {
    preprocess();
    if (file_exists(global_var_tmp_file)) {
        remove(global_var_tmp_file);
    }
    if (file_exists(global_var_clinit_tmp_file)) {
        remove(global_var_clinit_tmp_file);
    }
    if (file_exists(global_exp_tmp_file)) {
        remove(global_exp_tmp_file);
    }
    if (file_exists(global_method_tmp_file)) {
        remove(global_method_tmp_file);
    }
    free(last_exp_inst);
    last_exp_inst = NULL;
}

void m4postprocess() {
    postprocess();
    if (file_exists(global_var_tmp_file)) {
        remove(global_var_tmp_file);
    }
    if (file_exists(global_var_clinit_tmp_file)) {
        remove(global_var_clinit_tmp_file);
    }
    if (file_exists(global_exp_tmp_file)) {
        remove(global_exp_tmp_file);
    }
    if (file_exists(global_method_tmp_file)) {
        remove(global_method_tmp_file);
    }
    free(last_exp_inst);
    last_exp_inst = NULL;
}