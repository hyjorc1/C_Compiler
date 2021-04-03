#include "m3global.h"

void print_head(char *file_name) {
    printf("\n");
    printf("; Java assembly code\n");
    printf("\n");
    printf(".class public ");
    printf("%.*s\n", (int)strlen(file_name) - 2, file_name);
    printf(".super java/lang/Object\n");
    printf("\n");
    printf("; Global vars\n");
    printf("\n");
    printf(".method <init> : ()V\n");
    printf("    .code stack 1 locals 1\n");
    printf("        aload_0\n");
    printf("        invokespecial Method java/lang/Object <init> ()V\n");
    printf("        return\n");
    printf("    .end code\n");
    printf(".end method\n");
    printf("\n");
}

void print_main() {
    printf(".method public static main : ([Ljava/lang/String;)V\n");
    printf("    .code stack 2 locals 2\n");
    printf("        invokestatic Method exprs main ()I\n");
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
    
    preprocess();

    for (int i = fileIdx; i < argc; i++) {
        print("\nstart file %s\n", argv[i]);
        FILE *f = fopen(argv[i], "r");
        if (!f) {
            perror(argv[i]);
            return;
        }
        m3_cur_file_name = argv[i];
        m3lineno = 1;
        m3restart(f);
        print("Parse return %d\n", m3parse());
        
        print_head(m3_cur_file_name);
        print_main();

        fclose(f);
    }

    postprocess();
}




