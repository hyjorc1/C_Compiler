#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "tokens.h"
#include "m1global.h"

void mode1(int argc, char *argv[], int fileIdx) {
    for (int i = fileIdx; i < argc; i++) {
        print("\nstart file %s\n", argv[i]);
        if (newfile(argv[i])) {
            int token;
            while ((token = yylex())) {
                fprintf(stdout, "%s line %d text '%s' token %s\n", curfilename, yylineno, yytext, token_str);
            }
        } else {
            fprintf(stderr, "THe input file %s doesn't exist\n", argv[i]);
        }
    }
}