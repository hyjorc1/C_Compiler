#ifndef IFDEF_H
#define IFDEF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "global.h"

struct ifdef {
    struct ifdef *next;
    int lineno;
    char satisfy;
    char isifdef;
    char skip;
    char else_lineno;
} *iflist = 0;

int iflistsize = 0;

int newifdef(char isifdef, char skip) {
    if (iflistsize >= BUFFER_LIST_SIZE_LIMIT) {
        fprintf(stderr, "Error reaching iflist list size limit %d\n", BUFFER_LIST_SIZE_LIMIT);
    } else {
        struct ifdef *ifd = (struct ifdef*)malloc(sizeof(struct ifdef)); /* allocate ifdef @ ifdef.h#1 */
        ifd->isifdef = isifdef;
        ifd->skip = skip;
        ifd->else_lineno = 0;
        ifd->lineno = yylineno;
        ifd->next = iflist;
        iflist = ifd;
        iflistsize++;
    }
    return 1;
}

void popifdef() {
    struct ifdef *next = iflist->next;
    print("pop last ifdef node at line %d\n", iflist->lineno);
    free(iflist); /* free ifdef @ ifdef.h#1 */
    iflist = next;
    iflistsize--;
}

#endif