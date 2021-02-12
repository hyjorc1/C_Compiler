
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "tokens.h"
#include "token_map.h"

int main(int argc, char *argv[])
{

    for (int i = 1; i < argc; i++)
    {

        printf("start file %s\n", argv[i]);
        if (newfile(argv[i]))
        {
            int token;
            while ((token = yylex()))
            {
                if (token == END)
                {
                    break;
                }
                else
                {
                    fprintf(stdout, "%s line %d text '%s' token %s\n", curfilename, yylineno, yytext, map(token));
                }
            }
        }
    }

    // for (int i = 1; i < argc; i++)
    // {
    //     FILE *f = fopen(argv[i], "r");
    //     if (!f)
    //     {
    //         perror(argv[i]);
    //         return (1);
    //     }
    //     yyrestart(f);
    //     int token;
    //     while ((token = yylex()))
    //     {
    //         if (token == ERR)
    //         {
    //             fprintf(stderr, "Error near %s line %d\n", argv[i], err_lineno);
    //             printf("\t%s\n", err_msg);
    //             exit(0);
    //         }
    //         else
    //         {
    //             fprintf(stdout, "%s line %d text '%s' token %s\n", argv[i], yylineno, yytext, map(token));
    //         }
    //     }
    //     fclose(f);
    // }

    return 0;
}