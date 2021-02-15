#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "tokens.h"
#include "global.h"

int debug = 1;

int main(int argc, char *argv[])
{

    print("current debug mode %d\n", debug);
    for (int i = 1; i < argc; i++)
    {
        printf("\n");
        print("start file %s\n", argv[i]);
        if (newfile(argv[i]))
        {
            int token;
            while ((token = yylex()))
            {
                fprintf(stdout, "%s line %d text '%s' token %s\n", curfilename, yylineno, yytext, token_str);
            }
        }
    }

    return 0;
}