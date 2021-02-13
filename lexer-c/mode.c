
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "tokens.h"
#include "token_map.h"

int main(int argc, char *argv[])
{

    fprintf(stdout, "current debug mode %d\n", debug);
    for (int i = 1; i < argc; i++)
    {

        fprintf(stdout, "\nstart file %s\n", argv[i]);
        if (newfile(argv[i]))
        {
            int token;
            while ((token = yylex()))
            {
                fprintf(stdout, "%s line %d text '%s' token %s\n", curfilename, yylineno, yytext, map(token));
            }
        }
    }

    return 0;
}