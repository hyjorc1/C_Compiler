#include "m4global.h"

// JVM instructions - https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html

void m4handle_arr_init(char *id, char *num) {
    if (mode != 4 || m3_error)
        return;
    print("m4handle_arr_init\n");

    // handle integer first
    m4handle_int(num);

    // handle arr init
    FILE *f = get_file(m4_exp_tmp_file);
    fprintf(f, "%snewarray %s\n", ident8, cur_type->name);
    if (m3_is_global) {
        char *type_str = to_ensembly_type_str(cur_type);
        fprintf(f, "%sputstatic Field %s %s [%s ; depth %d\n", 
            ident8, m4_class_name, id, type_str, update_depth(-1));
        free(type_str);
    } else {
        int addr = m3_local_map == NULL ? 0 : m3_local_map->size;
        fprintf(f, "%sastore %d ; store to %s and depth %d\n", 
            ident8, addr, id, update_depth(-1));
    }
    fclose(f);

    if (m3_is_global)
        m4handle_global_var_init(id);
}

void m4handle_global_var(char *id) {
    if (mode != 4 || m3_error)
        return;
    print("m4_update_global_vars\n");

    FILE *f = get_file(m4_gvar_tmp_file);
    char *type_str = to_ensembly_type_str(cur_type);
    fprintf(f, ".field static %s %s\n", id, type_str);
    free(type_str);
    fclose(f);
}

void m4handle_global_var_init(char *id) {
    if (mode != 4 || m3_error)
        return;
    print("m4handle_global_var_init\n");

    FILE *dest = get_file(m4_gvar_clinit_tmp_file);
    fprintf(dest, "%s; Initializing %s\n", ident8, id);
    copy_files(dest, m4_exp_tmp_file);
    fclose(dest);
}

void m4handle_func_def() {
    if (mode != 4 || m3_error)
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
    fprintf(dest, "    .code stack %d locals %d\n", cur_fn->stack_max, var_num);

    // copy exp instructions
    copy_files(dest, m4_exp_tmp_file);

    // end lines
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
    if (mode != 4 || m3_error)
        return;
    print("m4handle_return_stmt\n");

    FILE *f = get_file(m4_exp_tmp_file);
    fprintf(f, "%s%sreturn ; depth %d\n", 
        ident8, to_ensembly_T_str1(t), update_depth(-1));
    fclose(f);
}

void m4handle_exp_stmt() {
    if (mode != 4 || m3_error)
        return;
    print("m4hanlde_exp_stmt\n");
    FILE *f = get_file(m4_exp_tmp_file);
    while (cur_fn->stack_size > 0) {
        fprintf(f, "%spop ; depth %d\n", ident8, update_depth(-1));
    }
    fclose(f);
}

/* ---------------- mode 4 exp functions --------------------- */

void m4handle_int(char *val) {
    print("m4handle_int\n");
    if (mode != 4 || m3_error)
        return;
    FILE *f = get_file(m4_exp_tmp_file);
    fprintf(f, "%sldc %s ; depth %d\n", ident8, val, update_depth(1));
    fclose(f);
}
void m4handle_real(char *val) {
    if (mode != 4 || m3_error)
        return;
    FILE *f = get_file(m4_exp_tmp_file);
    fprintf(f, "%sldc +%sf ; depth %d\n", ident8, val, update_depth(1));
    fclose(f);
}

void m4handle_str(char *val) {
    if (mode != 4 || m3_error)
        return;
    FILE *f = get_file(m4_exp_tmp_file);
    int char_cnt = strlen(val) - 2;
    val++;
    fprintf(f, "%sldc '%.*s' ; depth %d\n", ident8, char_cnt, val, update_depth(1));
    fprintf(f, "%sinvokevirtual Method java/lang/String toCharArray ()[C\n", ident8);
    fclose(f);
}

void m4handle_char(char *val) {
    if (mode != 4 || m3_error)
        return;
    FILE *f = get_file(m4_exp_tmp_file);
    fprintf(f, "%sbipush %d ; depth %d\n", ident8, val[1], update_depth(1));
    fclose(f);
}

void m4store(FILE *f, Type *lt) {
    if (lt->array_access) {
        fprintf(f, "%s%sastore ; depth %d\n",
            ident8, to_ensembly_T_str1(lt), update_depth(-3));
    } else if (lt->is_global) {
        char *type_str = to_ensembly_type_str(lt);
        fprintf(f, "%sputstatic Field %s %s %s ; depth %d\n",
            ident8, m4_class_name, lt->id, type_str, update_depth(-1));
        free(type_str);
    } else {
        fprintf(f, "%s%sstore %d ; store to %s and depth %d\n",
            ident8, to_ensembly_T_str1(lt), lt->addr, lt->id, update_depth(-1));
    }
}

void m4handle_assign_exp(Type *lt, char *op, Type *res) {
    if (mode != 4 || m3_error)
        return;
    print("m4handle_assign_exp\n");

    FILE *f = get_file(m4_exp_tmp_file);

    if (strcmp(op, "=") != 0) {
        char2int(res);
        char *type_str = to_ensembly_T_str1(res);
        char *op_str = to_ensembly_binary_op_str(op);
        fprintf(f, "%s%s%s ; depth %d\n", ident8, type_str, op_str, update_depth(-1));
    }

    if (return_count > 1) {
        char *dup_str = lt->array_access ? "dup_x2" : "dup";
        fprintf(f, "%s%s ; depth %d\n", ident8, dup_str, update_depth(1));
    }

    m4store(f, lt);
    fclose(f);
}

void m4handle_func_call_exp(Function *fn) {
    if (mode != 4 || m3_error)
        return;
    print("m4handle_func_call_exp\n");
    FILE *f = get_file(m4_exp_tmp_file);
    const char *class_name = fn->class_name ? fn->class_name : m4_class_name;
    fprintf(f, "%sinvokestatic Method %s %s (", ident8, class_name, fn->name);
    // add parameter types
    if (fn->parameters) {
        ListNode *cur = fn->parameters->first;
        while (cur != NULL) {
            Variable *v = (Variable *)cur->data;
            Type *t = map_get(fn->local_var_map, v->name);
            char *type_str = to_ensembly_type_str(t);
            fprintf(f, "%s", type_str);
            free(type_str);
            cur = cur->next;
        }
        
    }
    int para_num = fn->parameters ? fn->parameters->size : 0;
    int change = update_depth(-para_num) + update_depth(1);
    char *return_type_str = to_ensembly_type_str(fn->return_type);
    fprintf(f, ")%s ; depth %d\n", return_type_str, change);
    free(return_type_str);
    fclose(f);
}

void m4handle_root_exp_before() {
    if (mode != 4 || m3_error)
        return;
    print("m4handle_root_exp_before\n");
    FILE *dest = get_file(m4_exp_tmp_file);
    fprintf(dest, "%s;; %s %d expression\n", ident8, m4_class_name, m3lineno);
    fclose(dest);
}

Type *m4handle_lval(Type *t) {
    if (mode != 4 || m3_error)
        return t;
    print("m4handle_lval\n");
    FILE *f = get_file(m4_exp_tmp_file);
    if (t->array_access) {
        if (binary_assign)
            fprintf(f, "%sdup2 ; depth %d\n", ident8, update_depth(2));
        fprintf(f, "%s%saload ; depth %d\n",
            ident8, to_ensembly_T_str2(t), update_depth(-1));
    } else if (t->is_global) {
        char *type_str = to_ensembly_type_str(t);
        fprintf(f, "%sgetstatic Field %s %s %s ; depth %d\n",
            ident8, m4_class_name, t->id, type_str, update_depth(1));
        free(type_str);
    } else {
        fprintf(f, "%s%sload %d ; load from %s and depth %d\n",
            ident8, to_ensembly_T_str1(t), t->addr, t->id, update_depth(1));
    }
    fclose(f);
    return t;
}

void m4handle_r11_exp(char *op, Type *t2) {
    if (mode != 4 || m3_error)
        return;
    print("m4handle_r12_exp\n");
    binary_assign = 1;
    m4handle_lval(t2);
    FILE *f = get_file(m4_exp_tmp_file);
    fprintf(f, "%siconst_1 ; depth %d\n", ident8, update_depth(1));

    char *inst = strcmp(op, "++") == 0 ? "iadd" : "isub";
    fprintf(f, "%s%s ; depth %d\n", ident8, inst, update_depth(-1));

    if (return_count > 0) {
        char *dup_str = t2->array_access ? "dup_x2" : "dup";
        fprintf(f, "%s%s ; depth %d\n", ident8, dup_str, update_depth(1));
    }
    

    m4store(f, t2);
    fclose(f);
    binary_assign = 0;
}

void m4handle_r12_exp(Type *t1, char *op) {
    if (mode != 4 || m3_error)
        return;
    print("m4handle_r12_exp\n");
    binary_assign = 1;
    m4handle_lval(t1);
    FILE *f = get_file(m4_exp_tmp_file);
    if (return_count > 0) {
        char *dup_str = t1->array_access ? "dup_x2" : "dup";
        fprintf(f, "%s%s ; depth %d\n", ident8, dup_str, update_depth(1));
    }

    fprintf(f, "%siconst_1 ; depth %d\n", ident8, update_depth(1));

    char *inst = strcmp(op, "++") == 0 ? "iadd" : "isub";
    fprintf(f, "%s%s ; depth %d\n", ident8, inst, update_depth(-1));
    m4store(f, t1);
    fclose(f);
    binary_assign = 0;
}

void m4handle_utilde() {
    if (mode != 4 || m3_error)
        return;
    print("m4handle_utilde\n");
    FILE *f = get_file(m4_exp_tmp_file);
    fprintf(f, "%siconst_m1 ; depth %d\n", ident8, update_depth(1));
    fprintf(f, "%sixor ; depth %d\n", ident8, update_depth(-1));
    fclose(f);
}

void m4hanlde_uminus(Type *t) {
    if (mode != 4 || m3_error)
        return;
    print("m4handle_utilde\n");
    FILE *f = get_file(m4_exp_tmp_file);
    fprintf(f, "%s%sneg\n", ident8, to_ensembly_T_str1(t));
    fclose(f);
}

char m4cast_cond(Type *from, Type *to) {
    if (strcmp(from->name, float_str) == 0 && strcmp(to->name, int_str) == 0)
        return 1;
    if (strcmp(from->name, int_str) == 0) {
        if (strcmp(to->name, char_str) == 0 || strcmp(to->name, float_str) == 0)
            return 1;
    }
    return 0;
}

void m4handle_cast_exp(Type *t1, Type *t2) {
    if (mode != 4 || m3_error)
        return;
    print("m4handle_cast_exp\n");
    if (m4cast_cond(t2, t1)) {
        FILE *f = get_file(m4_exp_tmp_file);
        fprintf(f, "%s%s2%s\n", ident8, to_ensembly_T_str2(t2), to_ensembly_T_str2(t1));
        fclose(f);
    }
}

void m4handle_r8_exp(Type *t, char *op) {
    if (mode != 4 || m3_error)
        return;
    print("m4handle_r8_exp\n");
    char2int(t);
    FILE *f = get_file(m4_exp_tmp_file);
    char *type_str = to_ensembly_T_str1(t);
    char *op_str = to_ensembly_binary_op_str(op);
    fprintf(f, "%s%s%s ; depth %d\n", ident8, type_str, op_str, update_depth(-1));
    fclose(f);
}

void m4handle_r9_exp(Type *t, char *op) {
    if (mode != 4 || m3_error)
        return;
    print("m4handle_r9_exp\n");
    FILE *f = get_file(m4_exp_tmp_file);
    char2int(t);
    char *type_str = to_ensembly_T_str1(t);
    char *op_str = to_ensembly_binary_op_str(op);
    fprintf(f, "%s%s%s ; depth %d\n", ident8, type_str, op_str, update_depth(-1));
    fclose(f);
}

