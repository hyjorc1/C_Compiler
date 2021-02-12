#include <iostream>
#include <fstream>
#include "scanner.h"

int Scanner::newfile(istream *in, const char *fn, filebuf *fb)
{
    struct bufstack *bs = (struct bufstack *)malloc(sizeof(struct bufstack));
    if (!bs) { perror("malloc"); exit(1); }

    /* remember state */
    if (curbs)
        curbs->lineno = yylineno;
    
    /* set up current entry */
    bs->prev = curbs;
    bs->bs = yy_create_buffer(in, 16384);
    bs->fb = fb;
    bs->filename = fn;

    yy_switch_to_buffer(bs->bs);

    curbs = bs;
    yylineno = 1;
    curfilename = fn;
    return 1;
}

int Scanner::newfile(const char *fn)
{
    filebuf fb;
    if (fb.open(fn, ios::in)) {
        return newfile(new istream(&fb), fn, &fb);
    } else {
        perror(fn);
        exit(0);
    }
    return 1;
}

int Scanner::popfile(void)
{

    // printf("pop file\n");
    struct bufstack *bs = curbs;
    struct bufstack *prevbs;
    if (!bs)
        return 0;
    /* get rid of current entry */
    if (bs->fb)
    {
        // printf("bufstack pop and close file\n");
        bs->fb->close();
    }
    yy_delete_buffer(bs->bs);
    /* switch back to previous */
    prevbs = bs->prev;
    free(bs);
    if (!prevbs)
        return 0;
    yy_switch_to_buffer(prevbs->bs);
    curbs = prevbs;
    yylineno = curbs->lineno;
    curfilename = curbs->filename;
    return 1;
}