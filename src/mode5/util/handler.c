#include "m5global.h"

// JVM instructions - https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html

int m5handle_label() {
    if (mode != 5)
        return -1;
    print("m5handle_label\n");
    FILE *f = get_file(m4_exp_tmp_file);
    fprintf(f, "L%d:\n", instr_label++);
    fclose(f);
    return instr_label - 1;
}

Type *m5handle_cond_exp(Type *t) {
    if (mode != 5)
        return t;
    print("m5handle_cond_exp\n");

    FILE *f = get_file(m4_exp_tmp_file);

    t->truelist = list_new(sizeof(int), free);
    list_add_last(t->truelist, new_int(instr_line));
    fprintf(f, "%sifne _ ; instr_line %d depth %d\n", ident8, instr_line++, update_depth(-1));

    t->falselist = list_new(sizeof(int), free);
    list_add_last(t->falselist, new_int(instr_line));
    fprintf(f, "%sgoto _ ; instr_line %d depth 0\n", ident8, instr_line++);

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