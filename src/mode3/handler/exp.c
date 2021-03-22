#include "m3global.h"

/* R13: N op N -> N */
Type *handle_ASSIGN(char is_init, Type *lt, char *op, Type *rt) {
    print("handle_ASSIGN\n");
    Type *res = NULL;
    if (!is_init) {
        if (lt->is_const) { // l_val is const then error
            m3err();
            fprintf(stderr, "\tCannot assign to item of type %s%s\n", "const ", lt->name);
            return NULL;
        }
    }
    if (lt != NULL && rt != NULL) {
        if (widen_match_type(rt, lt)) {
            res = lt; 
        } else {
            m3err();
            fprintf(stderr, "\ttype mismatch\n");
            return NULL;
        }
    } else {
        char *lt_str = lt == NULL ? strdup("error") : type_to_str(lt);
        char *rt_str = rt == NULL ? strdup("error") : type_to_str(rt);
        m3err();
        fprintf(stderr, "\tOperation not supported: %s %s %s\n", lt_str, op, rt_str);
        return NULL;
    }
    return res;
}

Type *handle_UBANG(Type *t) {
    Type *res = NULL;
    // if (t != NULL && is_type_N(t)) {
    //     res = new_type_ast(strdup("char"), t->is_const, 0, 0);
    //     free_type_ast(t);
    // } else {
    //     m3err();
    //     // fprintf(stderr, "Operation not supported: %s %s\n", "!", t == NULL ? "error" t->name);
    // }
    return res;
}

void handle_cond_exp(char *msg, Type *t) {
    print("handle_cond_exp\n");
    if (t == NULL)
        return;
    if (!is_type_N(t)) {
        char *type_str = type_to_str(t);
        m3err();
        fprintf(stderr, "\tCondition of %s has invalid type: %s\n", msg, type_str);
        free(type_str);
    }
}

void print_err_candidates(Function *f) {
    fprintf(stderr, "\tCandidates are:\n");
    fprintf(stderr, "\t\t");

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
    fprintf(stderr, " declared in %s, near line %d\n", m3_cur_file_name, f->lineno);
}

void print_err_func_call(char *fn_name) {
    fprintf(stderr, "\tNo match for function call %s(", fn_name);
    if (m3_local_types != NULL) {
        ListNode *cur = m3_local_types->first;
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

char math_types(List *types1, Function *f) {
    if (f->parameters) {
        ListNode *cur1 = types1->first;
        ListNode *cur2 = f->parameters->first;
        while (cur2 != NULL) {
            Type *t1 = (Type *)cur1->data;
            Type *t2 = map_get(f->local_var_map, ((Variable *)cur2->data)->name);
            if (!exact_match_type(t1, t2))
                return 0;
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
    }
    return 1;
}

Type *handle_func_call(char *id) {
    Type *res = NULL;
    Function *f = find_proto_func(id);
    if (!f) {
        m3err();
        print_err_func_call(id);
        fprintf(stderr, "\tNo functions with this name\n");
    } else if (f->parameters->size != m3_local_types->size) {
        m3err();
        print_err_func_call(id);
        print_err_candidates(f);
    } else if (!math_types(m3_local_types, f)) {
        m3err();
        print_err_func_call(id);
        print_err_candidates(f);
    } else {
        res = f->return_type;
    }
    free(m3_local_types);
    m3_local_types = NULL;
    return res;
}

void handle_exp_list(Type *t) {
    if (t == NULL)
        return;
    if (m3_local_types == NULL)
        m3_local_types = list_new(sizeof(Type), free_type_ast);
    list_add_last(m3_local_types, t);
}