#include "m5global.h"

// JVM instructions - https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html

void backpatch(List *list, int label) {
    if (mode != 5 || list == NULL)
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

List *m5handle_if(Type *b, int true_label, List *s_list) {
    if (mode != 5)
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
    if (mode != 5)
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

int m5handle_label() {
    if (mode != 5)
        return -1;
    print("m5handle_label\n");
    FILE *f = get_file(m4_exp_tmp_file);
    fprintf(f, "L%d:\n", instr_label++);
    fclose(f);
    return instr_label - 1;
}

List *m5handle_next_line() {
    if (mode != 5)
        return NULL;
    print("m5handle_next_line\n");

    FILE *f = get_file(m4_exp_tmp_file);
    List *l = list_new(sizeof(int), free);
    list_add_last(l, new_int(instr_line));
    fprintf(f, "%sgoto # ; instr_line %d depth 0\n", ident8, instr_line++);
    fclose(f);
    return l;
}

Type *m5handle_cond_exp(Type *t) {
    if (mode != 5)
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
    if (mode != 5)
        return;
    print("m5handle_ubang\n");


}

void m5hanlde_r10_exp(Type *res, Type *t1, char *op, Type *t2) {
    if (mode != 5)
        return;
    print("m5handle_ubang\n");

}