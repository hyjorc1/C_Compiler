#include "m5global.h"

// JVM instructions - https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html

void backpatch(List *list, int label) {
    if (mode != 5 || list == NULL || m3_error)
        return;
    print("backpath\n");
    // list_print(list, print_int);
    // printf("%d\n", label);

    if (gotomap == NULL)
        gotomap = new_gotomap();
    ListNode *cur = list->first;
    while (cur != NULL) {
        int *line = (int *)cur->data;
        gotomap_put(gotomap, *line, label);
        cur = cur->next;
    }
    list_destroy(list);
    // gotomap_print(gotomap);
}

void m5handle_loop() {
    if (mode != 5 || !cur_fn || m3_error)
        return;
    print("m5handle_loop\n");

    if (!(cur_fn->breaks))
        cur_fn->breaks = list_new(sizeof(List), list_destroy_void);
    if (!(cur_fn->continues))
        cur_fn->continues = list_new(sizeof(List), list_destroy_void);

    list_add_last(cur_fn->breaks, list_new(sizeof(int), free));
    list_add_last(cur_fn->continues, list_new(sizeof(int), free));
}

List *m5handle_if(Type *b, int true_label, List *s_list) {
    if (mode != 5 || m3_error)
        return NULL;
    print("m5handle_if\n");

    backpatch(b->truelist, true_label);
    b->truelist = NULL;
    List *false_list = b->falselist;
    b->falselist = NULL;
    list_merge(false_list, s_list);
    free_type_ast(b);
    return false_list;
}

List *m5handle_ifelse(Type *b, int true_label, List *true_list, List *next_list, int false_label, List *false_list) {
    if (mode != 5 || m3_error)
        return NULL;
    print("m5handle_ifelse\n");

    backpatch(b->truelist, true_label);
    b->truelist = NULL;
    backpatch(b->falselist, false_label);
    b->falselist = NULL;
    List *l = list_merge(list_merge(true_list, false_list), next_list);
    free_type_ast(b);
    return l;
}

List *m5handle_while(int cond_label, Type *b, int do_label, List *s_list) {
    if (mode != 5 || m3_error)
        return NULL;
    print("m5handle_while\n");

    backpatch(b->truelist, do_label);
    b->truelist = NULL;
    List *l = b->falselist;
    b->falselist = NULL;
    free_type_ast(b);

    backpatch(s_list, cond_label);

    FILE *f = get_file(m4_exp_tmp_file);
    fprintf(f, "%sgoto L%d ; instr_line %d depth 0\n", ident8, cond_label, instr_line++);
    fclose(f);

    l = list_merge(l, (List *)list_remove_last(cur_fn->breaks)); // update breaks
    backpatch((List *)list_remove_last(cur_fn->continues), cond_label); // update continues
        
    return l;
}

List *m5handle_do(int do_label, List *s_list, int cond_label, Type *b) {
    if (mode != 5 || m3_error)
        return NULL;
    print("m5handle_do\n");

    backpatch(s_list, cond_label);

    backpatch(b->truelist, do_label);
    b->truelist = NULL;
    List *l = b->falselist;
    b->falselist = NULL;
    free_type_ast(b);

    l = list_merge(l, (List *)list_remove_last(cur_fn->breaks)); // update breaks
    backpatch((List *)list_remove_last(cur_fn->continues), cond_label); // update continues
    
    return l;
}

List *m5handle_for(int cond_label, Type *b, int post_label, List *next_list, int stmt_label, List *s_list) {
    if (mode != 5 || m3_error)
        return NULL;
    print("m5handle_for\n");

    backpatch(s_list, post_label);

    FILE *f = get_file(m4_exp_tmp_file);
    fprintf(f, "%sgoto L%d ; instr_line %d depth 0\n", ident8, post_label, instr_line++);
    fclose(f);

    backpatch(next_list, cond_label);

    backpatch(b->truelist, stmt_label);
    b->truelist = NULL;
    List *l = b->falselist;
    b->falselist = NULL;
    free_type_ast(b);

    l = list_merge(l, (List *)list_remove_last(cur_fn->breaks)); // update breaks
    backpatch((List *)list_remove_last(cur_fn->continues), post_label); // update continues

    return l;
}

void m5handle_break() {
    if (mode != 5 || !cur_fn || m3_error)
        return;
    print("m5handle_break\n");

    if (cur_fn->breaks == NULL || cur_fn->breaks->size == 0) {
        m3err();
        fprintf(stderr, "\tNo enclosing loop found for the break statement at %d\n", m3lineno);
        return;
    }

    List *break_list = (List *)cur_fn->breaks->last->data;
    list_add_last(break_list, new_int(instr_line));

    FILE *f = get_file(m4_exp_tmp_file);
    fprintf(f, "%sgoto # ; instr_line %d depth 0\n", ident8, instr_line++);
    fclose(f);
}

void m5handle_continue() {
    if (mode != 5 || !cur_fn || m3_error)
        return;
    print("m5handle_continue\n");

    if (cur_fn->continues == NULL || cur_fn->continues->size == 0) {
        m3err();
        fprintf(stderr, "\tNo enclosing loop found for the continue statement at %d\n", m3lineno);
        return;
    }

    List *cont_list = (List *)cur_fn->continues->last->data;
    list_add_last(cont_list, new_int(instr_line));

    FILE *f = get_file(m4_exp_tmp_file);
    fprintf(f, "%sgoto # ; instr_line %d depth 0\n", ident8, instr_line++);
    fclose(f);
}

int m5handle_label() {
    if (mode != 5 || m3_error)
        return -1;
    print("m5handle_label\n");
    FILE *f = get_file(m4_exp_tmp_file);
    fprintf(f, "L%d:\n", instr_label++);
    fclose(f);
    return instr_label - 1;
}

List *m5handle_next_line() {
    if (mode != 5 || m3_error)
        return NULL;
    print("m5handle_next_line\n");

    List *l = list_new(sizeof(int), free);
    list_add_last(l, new_int(instr_line));

    FILE *f = get_file(m4_exp_tmp_file);
    fprintf(f, "%sgoto # ; instr_line %d depth 0\n", ident8, instr_line++);
    fclose(f);
    return l;
}

Type *m5handle_cond_exp(Type *t) {
    if (mode != 5 || m3_error)
        return t;
    print("m5handle_cond_exp\n");

    FILE *f = get_file(m4_exp_tmp_file);

    t->truelist = list_new(sizeof(int), free);
    list_add_last(t->truelist, new_int(instr_line));
    fprintf(f, "%sifne # ; instr_line %d depth %d\n", ident8, instr_line++, update_depth(-1));

    t->falselist = list_new(sizeof(int), free);
    list_add_last(t->falselist, new_int(instr_line));
    fprintf(f, "%sgoto # ; instr_line %d depth 0\n", ident8, instr_line++);

    fclose(f);
    return t;
}

void m5handle_ubang(Type *res, Type *t) {
    if (mode != 5 || m3_error)
        return;
    print("m5handle_ubang\n");


}

void m5hanlde_r10_exp(Type *res, Type *t1, char *op, Type *t2) {
    if (mode != 5 || m3_error)
        return;
    print("m5handle_ubang\n");

}

void m5handle_ternary_exp(Type *b, int true_label, List *true_next, int false_label, int end_label) {
    if (mode != 5 || m3_error)
        return;
    print("m5handle_ternary_exp\n");

    backpatch(b->truelist, true_label);
    b->truelist = NULL;
    backpatch(b->falselist, false_label);
    b->falselist = NULL;
    backpatch(true_next, end_label);

    update_depth(-1);
}