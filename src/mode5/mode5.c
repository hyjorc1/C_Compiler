#include "m5global.h"

void m5print_bytecode_java_main() {
    printf("; Java main function\n\n");
    printf(".method public static main : ([Ljava/lang/String;)V\n");
    printf("    .code stack 1 locals 1\n");
    printf("        invokestatic Method %s main ()I\n", m4_class_name);
    printf("        pop\n");
    printf("        return\n");
    printf("    .end code\n");
    printf(".end method\n");
}

void mode5(int argc, char *argv[], int fileIdx) {
    for (int i = fileIdx; i < argc; i++) {
        m5preprocess();
        m5process(argv, i);
        
        if (!m3_error) {
            print_bytecode_class();
            print_bytecode_global_vars();
            print_bytecode_default_constructor();
            print_bytecode_methods();
            m5print_bytecode_java_main();
        }

        m5postprocess();
    }

    // List *l = list_new(sizeof(List), list_destroy_void);

    // List *e1 = list_new(sizeof(int), free);
    // list_add_last(e1, new_int(1));
    // list_add_last(e1, new_int(2));
    // list_print(e1, print_int);

    // while (e1->size > 0) {
    //     int *data = (int *)(list_remove_last(e1));
    //     printf("%d\n", *data);
    // }

    // List *e2 = list_new(sizeof(int), free);
    // list_add_last(e2, new_int(3));
    // list_add_last(e2, new_int(4));
    // list_print(e2, print_int);

    // list_add_last(l, e1);
    // list_add_last(l, e2);

    // ListNode *cur = l->first;
    // while (cur != NULL) {
    //     List *e = (List *)cur->data;
    //     list_print(e, print_int);
    //     cur = cur->next;
    // }
    // list_destroy(l);
}
