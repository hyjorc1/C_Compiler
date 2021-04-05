#include "m4global.h"

const char *m4_class_name = NULL;
const char *global_var_tmp_file = "mode4_gvar_tmp";
const char *global_var_clinit_tmp_file = "mode4_gvc_tmp";
const char *global_method_tmp_file = "mode4_gm_tmp";
const char *global_exp_tmp_file = "mode4_ge_tmp";
const char *ident4 = "    ";
const char *ident8 = "        ";

void m4handle_global_var(char *id) {
    if (mode != 4)
        return;
    print("m4_update_global_vars\n");
    FILE *f = get_file(global_var_tmp_file);
    char *type_str = ensemble_type_str(cur_type);
    fprintf(f, ".field static %s %s\n", id, type_str);
    free(type_str);
    fclose(f);
}

void m4handle_global_var_init(char *id) {
    if (mode != 4)
        return;
    print("m4handle_global_var_init\n");
    FILE *dest = get_file(global_var_clinit_tmp_file);
    // copy exp instructions
    if (file_exists(global_exp_tmp_file)) {
        FILE *src = fopen(global_exp_tmp_file, "r");
        char c;
        c = fgetc(src);
        while (c != EOF) {
            fprintf(dest, "%c", c);
            c = fgetc(src);
        }
        fclose(src);
        remove(global_exp_tmp_file);
    }
    // update static field instruction
    char *type_str = ensemble_type_str(cur_type);
    fprintf(dest, "%sputstatic Field %s %s %s\n", ident8, m4_class_name, id, type_str);
    free(type_str);

    fclose(dest);
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

char *ensemble_type_str(Type *t) {
    print("ensemble_type_str\n");
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

void m4preprocess() {
    preprocess();
}

void m4postprocess() {
    postprocess();
    
}