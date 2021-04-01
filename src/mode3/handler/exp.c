#include "m3global.h"

/* R1: N ? T : T -> T */
Type *handle_ternary_exp(Type *t1, Type *t2, Type *t3) {
    Type *res = NULL;
    if (t1 == NULL || t2 == NULL || t3 == NULL) {
        // omit
    } else if (!is_type_N(t1) || (!widen_match_type(t2, t3) && !widen_match_type(t3, t2))) {
        char *t1_str = type_to_str(t1);
        char *t2_str = type_to_str(t2);
        char *t3_str = type_to_str(t3);
        m3err();
        fprintf(stderr, "\tOperation not supported: %s ? %s : %s\n", t1_str, t2_str, t3_str);
        free(t1_str);
        free(t2_str);
        free(t3_str);
    } else {
        res = widen_match_type(t2, t3) ? deep_copy_type_ast(t3) : deep_copy_type_ast(t2);
        if (t1->is_const && t2->is_const && t3->is_const)
            res->is_const = 1;
    }
    free_type_ast(t1);
    free_type_ast(t2);
    free_type_ast(t3);
    return res;
}

/* R2: ~ I -> I */
Type *handle_utilde(Type *t) {
    Type *res = NULL;
    if (t == NULL) {
        // omit
    } else if (!is_type_I(t)) {
        char *t_str = type_to_str(t);
        m3err();
        fprintf(stderr, "\tOperation not supported: ~ %s\n", t_str);
        free(t_str);
    } else {
        res = deep_copy_type_ast(t);
    }
    free_type_ast(t);
    return res;
}

/* R3: ~ N -> N */
Type *handle_uminus(Type *t) {
    Type *res = NULL;
    if (t == NULL) {
        // omit
    } else if (!is_type_N(t)) {
        char *t_str = type_to_str(t);
        m3err();
        fprintf(stderr, "\tOperation not supported: - %s\n", t_str);
        free(t_str);
    } else {
        res = deep_copy_type_ast(t);
    }
    free_type_ast(t);
    return res;
}

/* R4: ! N -> char */
Type *handle_ubang(Type *t) {
    Type *res = NULL;
    if (t == NULL) {
        // omit
    } else if (!is_type_N(t)) {
        char *t_str = type_to_str(t);
        m3err();
        fprintf(stderr, "\tOperation not supported: ! %s\n", t_str);
        free(t_str);
    } else {
        res = new_type_ast(strdup(char_str), 0, 0, 0);
        res->is_const = (t->is_const) ? 1 : 0;
    }
    free_type_ast(t);
    return res;
}

/* R5, 6, 7: (N) N -> N */
Type *handle_cast_exp(Type *t2) {
    Type *res = NULL;
    Type *t1 = cur_type;
    cur_type = NULL;
    if (t1 == NULL || t2 == NULL) {
        // omit
    } else if (!is_type_N(t1) || !is_type_N(t2)) {
        char *t1_str = type_to_str(t1);
        char *t2_str = type_to_str(t2);
        m3err();
        fprintf(stderr, "\tCannot cast expression of type %s\n", t2_str);
        free(t1_str);
        free(t2_str);
    } else {
        if (!strcmp(t1->name, char_str))
            res = new_type_ast(strdup(char_str), 0, 0, 0);
        else if (!strcmp(t1->name, int_str))
            res = new_type_ast(strdup(int_str), 0, 0, 0);
        else if (!strcmp(t1->name, float_str))
            res = new_type_ast(strdup(float_str), 0, 0, 0);
        res->is_const = (t2->is_const) ? 1 : 0;
    }
    free_type_ast(t1);
    free_type_ast(t2);
    return res;
}

/* R8: I op I -> I */
Type *handle_r8_exp(Type *t1, char *op, Type *t2) {
    Type *res = NULL;
    if (t1 == NULL || t2 == NULL) {
        // omit
    } else if (!is_type_I(t1) || !is_type_I(t2)
        || (!widen_match_type(t1, t2) && !widen_match_type(t2, t1))) {
        char *t1_str = type_to_str(t1);
        char *t2_str = type_to_str(t2);
        m3err();
        fprintf(stderr, "\tOperation not supported: %s %s %s\n", t1_str, op, t2_str);
        free(t1_str);
        free(t2_str);
    } else {
        res = widen_match_type(t1, t2) ? deep_copy_type_ast(t2) : deep_copy_type_ast(t1);
        res->is_const = (t1->is_const && t2->is_const) ? 1 : 0;
    }
    free_type_ast(t1);
    free_type_ast(t2);
    return res;
}

/* R9: N op N -> N */
Type *handle_r9_exp(Type *t1, char *op, Type *t2) {
    Type *res = NULL;
    if (t1 == NULL || t2 == NULL) {
        // omit
    } else if (!is_type_N(t1) || !is_type_N(t2)
        || (!widen_match_type(t1, t2) && !widen_match_type(t2, t1))) {
        char *t1_str = type_to_str(t1);
        char *t2_str = type_to_str(t2);
        m3err();
        fprintf(stderr, "\tOperation not supported: %s %s %s\n", t1_str, op, t2_str);
        free(t1_str);
        free(t2_str);
    } else {
        res = widen_match_type(t1, t2) ? deep_copy_type_ast(t2) : deep_copy_type_ast(t1);
        res->is_const = (t1->is_const && t2->is_const) ? 1 : 0;
    }
    free_type_ast(t1);
    free_type_ast(t2);
    return res;
}

/* R10: N op N -> char */
Type *handle_r10_exp(Type *t1, char *op, Type *t2) {
    Type *res = NULL;
    if (t1 == NULL || t2 == NULL) {
        // omit
    } else if (!is_type_N(t1) || !is_type_N(t2)
        || (!widen_match_type(t1, t2) && !widen_match_type(t2, t1))) {
        char *t1_str = type_to_str(t1);
        char *t2_str = type_to_str(t2);
        m3err();
        fprintf(stderr, "\tOperation not supported: %s %s %s\n", t1_str, op, t2_str);
        free(t1_str);
        free(t2_str);
    } else {
        res = new_type_ast(strdup(char_str), 0, 0, 0);
        res->is_const = (t1->is_const && t2->is_const) ? 1 : 0;
    }
    free_type_ast(t1);
    free_type_ast(t2);
    return res;
}

/* R11: op N -> N */
Type *handle_r11_exp(char *op, Type *t2) {
    Type *res = NULL;
    if (t2 == NULL) {
        // omit
    } else if (t2->is_const || !is_type_N(t2)) {
        char *t_str = type_to_str(t2);
        char *s1 = strcmp(op, "++") == 0 ? "increment" : "decrement";
        m3err();
        fprintf(stderr, "\tCannot %s lvalue of type %s\n", s1, t_str);
        free(t_str);
    } else {
        res = deep_copy_type_ast(t2);
    }
    free_type_ast(t2);
    return res;
}

/* R12: N op -> N */
Type *handle_r12_exp(Type *t1, char *op) {
    Type *res = NULL;
    if (t1 == NULL) {
        // omit
    } else if (t1->is_const || !is_type_N(t1)) {
        char *t_str = type_to_str(t1);
        char *s1 = strcmp(op, "++") == 0 ? "increment" : "decrement";
        m3err();
        fprintf(stderr, "\tCannot %s lvalue of type %s\n", s1, t_str);
        free(t_str);
    } else {
        res = deep_copy_type_ast(t1);
    }
    free_type_ast(t1);
    return res;
}

/* R13: N op N -> N */
Type *handle_assign_exp(char is_init, Type *lt, char *op, Type *rt) {
    print("handle_assign_exp\n");
    Type *res = NULL;
    if (lt == NULL || rt == NULL) {
        // omit
    } else if (!is_init && lt->is_const) { // l_val is const then error
        char *t_str = type_to_str(lt);
        m3err();
        fprintf(stderr, "\tCannot assign to item of type %s\n", t_str);
        free(t_str);
    } else if (is_type_N(lt) && is_type_N(rt) && widen_match_type(rt, lt)) {
        res = deep_copy_type_ast(lt);
        res->is_const = (rt->is_const && lt->is_const) ? 1 : 0;
    } else {
        char *lt_str = type_to_str(lt);
        char *rt_str = type_to_str(rt);
        m3err();
        if (!is_type_N(lt) || !is_type_N(rt)) {
            fprintf(stderr, "\tOperation not supported: %s %s %s\n", lt_str, op, rt_str);
        } else {
            fprintf(stderr, "\tType mismatch in assignment: expected %s, got %s\n", lt_str, rt_str);
        }
        free(lt_str);
        free(rt_str);
    }
    free_type_ast(lt);
    free_type_ast(rt);
    return res;
}

Type *handle_l_ident(char *id) {
    print("handle_l_ident\n");
    Type *res = NULL;
    Type *t = find_local_type(id);
    if (t == NULL)
        t = find_global_type(id);

    if (t == NULL) {
        m3err();
        fprintf(stderr, "\tUndeclared identifier: %s\n", id);
    } else {
        res = deep_copy_type_ast(t);
    }
    return res;
}

/* R14: T[int] -> N  */
Type *handle_l_array_access(char *id, Type *op) {
    Type *t = handle_l_ident(id);
    Type *res = NULL;
    if (t == NULL || op == NULL) {
        // omit
    } else if (!t->is_array) {
        m3err();
        fprintf(stderr, "\tIdentifier %s is not an array\n", id);
    } else if (!is_type_I(op)) {
        m3err();
        fprintf(stderr, "\tIndex to array %s is not an integer\n", id);
    } else {
        t->is_array = 0;
        res = t;
    }
    free(op);
    return res;
}

/* R14: S.m -> T */
Type *handle_l_member(Type *st, char *m) {
    Type *res = NULL;
    if (st == NULL) {
        // omit
    } else if (!st->is_struct) {
        char *t_str = type_to_str(st);
        m3err();
        fprintf(stderr, "\tBase type %s is not a struct\n", t_str);
        free(t_str);
    } else {
        Struct *s = find_local_struct(st->name);
        if (s == NULL)
            s = find_global_struct(st->name);
        if (s != NULL) {
            Type *mt = map_get(s->local_var_map, m);
            if (mt == NULL) {
                m3err();
                fprintf(stderr, "\tBase type struct %s has no member named %s\n", st->name, m);
            } else {
                res = deep_copy_type_ast(mt);
            }
        }
    }
    free(st);
    return res;
}

Type *handle_l_array_member(Type *st, char *m, Type *op) {
    Type *mt = handle_l_member(st, m);
    Type *res = NULL;
    if (st == NULL || mt == NULL || op == NULL) {
        // omit
    } else if (!mt->is_array) {
        m3err();
        fprintf(stderr, "\tStruct member %s is not an array\n", m);
    } else if (!is_type_I(op)) {
        m3err();
        fprintf(stderr, "\tIndex to array member %s is not an integer\n", m);
    } else {
        mt->is_array = 0;
        res = mt;
    }
    free(op);
    return res;
}

void handle_cond_exp(char *msg, Type *t) {
    print("handle_cond_exp\n");
    if (t == NULL) {
        // omit
    } else if (!is_type_N(t)) {
        char *type_str = type_to_str(t);
        m3err();
        fprintf(stderr, "\tCondition of %s has invalid type: %s\n", msg, type_str);
        free(type_str);
    }
    free(t);
}

void print_err_func_sig(Function *f) {
    char *return_type_str = type_to_str(f->return_type);
    fprintf(stderr, "%s %s(", return_type_str, f->name);
    free(return_type_str);

    if (f->parameters) {
        ListNode *cur = f->parameters->first;
        while (cur != NULL) {
            ListNode *next = cur->next;
            Variable *v = (Variable *)cur->data;
            Type *t = map_get(f->local_var_map, v->name);
            char *type_str = type_to_str(t);
            fprintf(stderr, "%s", type_str);
            free(type_str);
            if (next != NULL)
                fprintf(stderr, ", ");
            cur = next;
        }
    }
    fprintf(stderr, ")");
}

void print_err_candidates(Function *f) {
    fprintf(stderr, "\tCandidates are:\n\t");
    print_err_func_sig(f);
    fprintf(stderr, " declared in %s near line %d\n", m3_cur_file_name, f->lineno);
}

void print_err_func_call(char *fn_name, List *arg_types) {
    print("print_err_func_call\n");
    fprintf(stderr, "\tNo match for function call %s(", fn_name);
    if (arg_types != NULL) {
        ListNode *cur = arg_types->first;
        while (cur != NULL) {
            ListNode *next = cur->next;
            Type *t = (Type *)cur->data;
            char *type_str = type_to_str(t);
            fprintf(stderr, "%s", type_str);
            free(type_str);
            if (next != NULL)
                fprintf(stderr, ", ");
            cur = next;
        }
    }
    fprintf(stderr, ")\n");
}

char math_types(List *arg_types, Function *f) {
    print("math_types\n");
    if (f->parameters) {
        ListNode *cur1 = arg_types->first;
        ListNode *cur2 = f->parameters->first;
        HashMap *func_local_map = f->local_var_map ? f->local_var_map : m3_local_map;
        while (cur2 != NULL) {
            Type *arg_type = (Type *)cur1->data;
            Type *para_type = map_get(func_local_map, ((Variable *)cur2->data)->name);
            if (!widen_match_type(arg_type, para_type))
                return 0;
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
    }
    return 1;
}

int match_parameter_size(List *parameters, List *types) {
    int n1 = parameters == NULL ? 0 : parameters->size;
    int n2 = types == NULL ? 0 : types->size;
    return n1 == n2 ? 1 : 0;
}


Type *handle_func_call_exp(char *id, List *arg_types) {
    print("handle_func_call_exp\n");
    Type *res = NULL;
    Function *f = find_proto_func(id); // check proto function
    if (!f)
        f = find_declared_func(id); // check defined function
    if (!f && !strcmp(cur_fn->name, id)) // check current function
        f = cur_fn;

    if (!f) {
        m3err();
        print_err_func_call(id, arg_types);
        fprintf(stderr, "\tNo functions with this name\n");
    } else if (!match_parameter_size(f->parameters, arg_types)) {
        m3err();
        print_err_func_call(id, arg_types);
        print_err_candidates(f);
    } else if (!math_types(arg_types, f)) {
        m3err();
        print_err_func_call(id, arg_types);
        print_err_candidates(f);
    } else {
        res = deep_copy_type_ast(f->return_type);
    }
    free(arg_types);
    return res;
}

List *handle_single_type(Type *t) {
    if (t == NULL)
        return NULL;
    List *l = list_new(sizeof(Type), free_type_ast);
    return list_add_last(l, t);
}


