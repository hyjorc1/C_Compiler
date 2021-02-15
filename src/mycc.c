#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"
#include "global.h"

int debug = 0;

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printusage();
        return 0;
    }

    int fileIdx = 2;
    /* set output file */
    if (argc >= 4 && !strcmp(argv[2], "-o")) {
        freopen(argv[3], "w", stdout);
        fileIdx = 4;
    }
    
    if (!strcmp(argv[1], "-0")) {
        printversion();
    } else {
        if (fileIdx > argc) {
            fprintf(stderr, "Modes 1 to 5 need input files\n");
        } else if (!strcmp(argv[1], "-1")) {
            for (int i = fileIdx; i < argc; i++) {
                print("\nstart file %s\n", argv[i]);
                if (newfile(argv[i])) {
                    int token;
                    while ((token = yylex())) {
                        fprintf(stdout, "%s line %d text '%s' token %s\n", curfilename, yylineno, yytext, token_str);
                    }
                }
            }
        } else if (strlen(argv[1]) >= 2 && argv[1][1] >= '1' && argv[1][1] <= '5') {
            fprintf(stderr, "The other modes are not implemented.\n");
        } else {
            printusage();
        }
    }
    return 0;
}

