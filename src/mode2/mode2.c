#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "m2global.h" 

void mode2(int argc, char *argv[], int fileIdx) {
    // for (int i = fileIdx; i < argc; i++) {
    //     print("\nstart file %s\n", argv[i]);
    //     if (newfile(argv[i])) {
    //         int token;
    //         while ((token = yylex())) {
    //             fprintf(stdout, "%s line %d text '%s' token %s\n", curfilename, yylineno, yytext, token_str);
    //         }
    //     } else {
    //         fprintf(stderr, "THe input file %s doesn't exist\n", argv[i]);
    //     }
    // }
    int code = m2parse();
    printf("yyparse returned %d\n", code);
}
