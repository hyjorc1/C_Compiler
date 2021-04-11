#include "m4global.h"

void print_bytecode_class() {
    printf("\n");
    printf("; Java assembly code\n");
    printf("\n");
    printf(".class public %s\n", m4_class_name);
    printf(".super java/lang/Object\n");
    printf("\n");
}

void print_file_content(const char *file_name) {
    if (file_exists(file_name)) {
        FILE *f = fopen(file_name, "r");
        char c;
        c = fgetc(f);
        while (c != EOF) {
            printf ("%c", c);
            c = fgetc(f);
        }
        fclose(f);
        remove(file_name);
    }
}

void print_bytecode_global_vars() {
    printf("; Global vars\n\n");
    if (file_exists(m4_gvar_tmp_file)) {
        print_file_content(m4_gvar_tmp_file);
        printf("\n");
    }
    if (file_exists(m4_gvar_clinit_tmp_file)) {
        printf (".method static <clinit> : ()V\n");
        printf ("    .code stack 1 locals 0\n");
        print_file_content(m4_gvar_clinit_tmp_file);
        printf ("        return\n");
        printf ("    .end code\n");
        printf (".end method\n");
        printf("\n");
    }
}

void print_bytecode_default_constructor() {
    printf("; Default constructor\n\n");
    printf(".method <init> : ()V\n");
    printf("    .code stack 1 locals 1\n");
    printf("        aload_0\n");
    printf("        invokespecial Method java/lang/Object <init> ()V\n");
    printf("        return\n");
    printf("    .end code\n");
    printf(".end method\n");
    printf("\n");
}

void print_bytecode_methods() {
    printf("; Methods\n\n");
    if (file_exists(m4_method_tmp_file)) {
        print_file_content(m4_method_tmp_file);
    }
}

void print_bytecode_java_main() {
    printf("; Java main function\n\n");
    printf(".method public static main : ([Ljava/lang/String;)V\n");
    printf("    .code stack 2 locals 2\n");
    printf("        invokestatic Method %s main ()I\n", m4_class_name);
    printf("        istore_1\n");
    printf("        getstatic Field java/lang/System out Ljava/io/PrintStream;\n");
    printf("        ldc 'Return code: '\n");
    printf("        invokevirtual Method java/io/PrintStream print (Ljava/lang/String;)V\n");
    printf("        getstatic Field java/lang/System out Ljava/io/PrintStream;\n");
    printf("        iload_1\n");
    printf("        invokevirtual Method java/io/PrintStream println (I)V\n");
    printf("        return\n");
    printf("    .end code\n");
    printf(".end method\n");
}

void mode4(int argc, char *argv[], int fileIdx) {

    for (int i = fileIdx; i < argc; i++) {

        m4preprocess();

        print("\nstart file %s\n", argv[i]);
        FILE *f = fopen(argv[i], "r");
        if (!f) {
            perror(argv[i]);
            return;
        }

        m3_cur_file_name = argv[i];
        m4_class_name = substr(m3_cur_file_name, 0, strlen(m3_cur_file_name) - 2);
        m3lineno = 1;
        m3_error = 0;
        m3_return_error = 0;

        m3restart(f);
        print("Parse return %d\n", m3parse());
        
        if (!m3_error) {
            print_bytecode_class();
            print_bytecode_global_vars();
            print_bytecode_default_constructor();
            print_bytecode_methods();
            print_bytecode_java_main();
        }

        fclose(f);
        m4postprocess();
    }

}




