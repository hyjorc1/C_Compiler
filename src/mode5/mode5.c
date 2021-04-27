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
}
