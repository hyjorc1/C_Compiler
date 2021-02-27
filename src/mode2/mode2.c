#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "m2global.h"

void mode2(int argc, char *argv[], int fileIdx)
{
    for (int i = fileIdx; i < argc; i++)
    {
        print("\nstart file %s\n", argv[i]);
        FILE *f = fopen(argv[i], "r");
        if (!f)
            perror(argv[i]);
        m2restart(f);
        // yylex();
        int code = m2parse();
        printf("yyparse returned %d\n", code);
        fclose(f);
    }
    
}
