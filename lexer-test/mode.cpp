
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "tokens.h"
#include "token_map.h"
#include "scanner.h"

using namespace std;

void process(const char *fn)
{
    filebuf fb;
    if (fb.open(fn, ios::in))
    {
        Scanner *scan = new Scanner();
        scan->newfile(new istream(&fb), fn, &fb);
        int token;
        while ((token = scan->yylex()))
        {
            if (token == ERR)
            {
                fprintf(stderr, "Error near %s line %d\n", fn, err_lineno);
                printf("\t%s\n", err_msg);
                exit(0);
            }
            else
            {
                fprintf(stdout, "%s line %d text '%s' token %s\n", fn, scan->lineno(), scan->YYText(), enum_map.at(token).c_str());
            }
        }
        delete (scan);
        scan = nullptr;

        if (fb.is_open()) {
            printf("file still open\n");
            fb.close();
        } else {
            printf("file already closed\n");
        }
        
    }
    else
    {
        perror(fn);
        exit(0);
    }
}

int main(int argc, char const *argv[])
{

    for (int i = 1; i < argc; i++)
    {
        cout << endl;
        // process(argv[i]);
        Scanner *scan = new Scanner();

        filebuf fb;
        // if (fb.open(argv[i], ios::in)) {
        //     scan->newfile(new istream(&fb), argv[i], &fb);
        // }
        
        scan->newfile(argv[i]);

        scan->yylex();

        // if (scan->newfile(argv[i]))
        // {
        //     int token;
        //     while ((token = scan->yylex()))
        //     {
        //         if (token == ERR)
        //         {
        //             fprintf(stderr, "Error near %s line %d\n", scan->curfilename, err_lineno);
        //             printf("\t%s\n", err_msg);
        //             exit(0);
        //         }
        //         else
        //         {
        //             fprintf(stdout, "%s line %d text '%s' token %s\n", scan->curfilename, scan->lineno(), scan->YYText(), enum_map.at(token).c_str());
        //         }
        //     }
        // }
        // delete (scan);
        // scan = nullptr;
    }

    return 0;
}