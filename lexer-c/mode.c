
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "tokens.h"
#include "token_map.h"

int main(int argc, char *argv[])
{

    for (int i = 1; i < argc; i++)
    {
        if (newfile(argv[i]))
        {
            int token;
            while ((token = yylex()))
            {
                if (token == ERR)
                {
                    fprintf(stderr, "Error near %s line %d\n", curfilename, err_lineno);
                    printf("\t%s\n", err_msg);
                    exit(0);
                }
                else
                {
                    fprintf(stdout, "%s line %d text '%s' token %s\n", curfilename, lineno(), yytext, map(token));
                }
            }
        }
    }

    return 0;
}