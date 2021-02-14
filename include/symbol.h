#ifndef SYMBOL_H
#define SYMBOL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "global.h"

struct symbol {             /* a word */
    char *name;
    struct ref *reflist; 
};

struct ref {
    struct ref *next; 
    char *value;
    char *filename;
    int flags;
    int lineno;
};

#define NHASH 9997          /* simple symtab of fixed size */ 
struct symbol symtab[NHASH];

static unsigned symhash(char *sym) {
    unsigned int hash = 0;
    unsigned c;
    while ((c = *sym++))
        hash = hash * 7 ^ c;
    return hash;
}

struct symbol *lookup(char *sym) {
    struct symbol *sp = &symtab[symhash(sym) % NHASH];
    int scount = NHASH; /* how many have we looked at */
    while ((--scount >= 0)) {
        /* found sym */
        if (sp->name && !strcmp(sp->name, sym))
            return sp;
        /* new entry */
        if (!sp->name) {
            sp->reflist = 0;
            return sp;
        }
        /* find a free entry */
        if (++sp >= symtab + NHASH)
            sp = symtab; /* start from the frist entry */
    }
    fputs("symbol table overflow\n", stderr);
    abort(); /* tried them all, table is full */
}

void removeref(char *sym) {
    print("removeref() %s\n", sym);
    struct symbol *sp = lookup(sym);
    /* symbol doesn't exist in the table */
    if (!sp->reflist || sp->reflist->filename != curfilename) {
        print("removeref() key:%s- doesn't exist\n", sym);
        return;
    }

    sp->name = 0;
    struct ref *r = sp->reflist;
    sp->reflist = 0;
    free(r);
}

int addref(int lineno, char *filename, char *sym, char *val, int flags) {
    print("addref() key:%s- val:%s-\n", sym, val);
    struct ref *r;
    struct symbol *sp = lookup(sym);
    
    int status = 1; /* indicate the new symbol in the current file */
    if (sp->reflist && sp->reflist->filename == filename) {
        fprintf(stderr, "Error near %s line %d text '%s'\n", curfilename, err_lineno, yytext);
        fprintf(stderr, "\tre-defining preprocessor symbol %s\n", sp->name);
        print("addref() has prevref with val:%s-\n", sp->reflist->value);
        status = 0;
    }

    r = (struct ref*)malloc(sizeof(struct ref));
    if (!r) {
        fputs("out of space\n", stderr);
        abort();
    }
    r->value = strdup(val);
    r->next = sp->reflist;
    r->filename = filename;
    r->lineno = lineno;
    r->flags = flags;
    sp->reflist = r;
    sp->name = strdup(sym);
    return status;
}

/* print the references sort the table alphabetically
then flip each entry's reflist to get it into forward 
order * and print it out */

/* aux function for sorting */
static int symcompare(const void *xa, const void *xb) {
    const struct symbol *a = (const struct symbol *)xa;
    const struct symbol *b = (const struct symbol *)xb;
    if (a->name && b->name) {
        return strcmp(a->name, b->name);
    } else if (a->name) {   /* a is smaller */
        return -1;
    } else if (b->name) {   /* b is smaller */
        return 1;
    } else {                /* both empty */
        return 0;
    }
}

void printrefs() {
    struct symbol *sp = 0;
    qsort(symtab, NHASH, sizeof(struct symbol), symcompare); /* sort the symbol table */

    if (!symtab[0].name) {
        print("\nsymbol table is empty!!\n\n");
        return;
    }
    print("\nprint symbol table\n");
    for (sp = symtab; sp->name && sp < symtab + NHASH; sp++) {
        char *prevfn = NULL; /* last printed filename, to skip dups */
        /* reverse the list of references */
        struct ref *rp = sp->reflist;
        struct ref *rpp = 0;            /* previous ref */
        struct ref *rpn;                /* next ref */

        do {
            rpn = rp->next;
            rp->next = rpp;
            rpp = rp;
            rp = rpn;
        } while (rp);

        /* now print the word and its references */
        print("%s", sp->name);
        for (rp = rpp; rp; rp = rp->next) {
            if (rp->filename == prevfn) {
                print(" line:%d", rp->lineno);
                print(" val:%s,", rp->value);
            } else {
                print(" %s-line:%d", rp->filename, rp->lineno);
                print(" val:%s,", rp->value);
                prevfn = rp->filename;
            }
        }
        print("\n");
    }
    print("\n");
}

#endif