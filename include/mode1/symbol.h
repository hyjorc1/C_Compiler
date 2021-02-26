#ifndef SYMBOL_H
#define SYMBOL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "m1global.h"

struct symbol {
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
            sp->name = 0;
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
    print("removeref() '%s'\n", sym);
    struct symbol *sp = lookup(sym);
    /* symbol doesn't exist in the table */
    if (!sp->reflist || !sp->reflist->filename || sp->reflist->filename != curfilename) {
        print("removeref() key:'%s' doesn't exist\n", sym);
        return;
    }

    /* first remmove the refs not in the same file */
    while (sp->reflist && sp->reflist->filename && sp->reflist->filename == curfilename) {
        struct ref *next = sp->reflist->next;
        free(sp->reflist->value); /* free ref->value @ symbol.h#2 */
        sp->reflist->next = 0;
        sp->reflist->filename = 0;
        sp->reflist->lineno = 0;
        sp->reflist->flags = 0;
        free(sp->reflist); /* free ref @ symbol.h#3 */
        sp->reflist = next;
    }

    /* if the symbol has no reflist, reset it */
    if (!sp->reflist) {
        free(sp->name); /* free sp->name @ symbol.h#1 */
        sp->name = 0;
        sp->reflist = 0;
    }
}

int addref(char *sym, char *val, int flags) {
    print("addref() key:'%s' val:'%s'\n", sym, val);
    struct ref *r;
    struct symbol *sp = lookup(sym);
    
    int status = 1; /* indicate the new symbol in the current file */
    if (sp->reflist && sp->reflist->filename == curfilename) {
        fprintf(stderr, "Error near %s line %d\n", curfilename, err_lineno);
        fprintf(stderr, "\tre-defining preprocessor symbol %s\n", sp->name);
        print("addref() has prevref with val:'%s'-\n", sp->reflist->value);
        status = 0;
    }

    r = (struct ref*)malloc(sizeof(struct ref)); /* allocate ref @ symbol.h#3 */
    if (!r) {
        fputs("out of space\n", stderr);
        abort();
    }
    r->value = strdup(val);  /* allocate ref->value @ symbol.h#2 */
    r->next = sp->reflist;
    r->filename = curfilename; /* point to the same address, no need to free */
    r->lineno = err_lineno;
    r->flags = flags;
    sp->reflist = r;
    if (!sp->name)
        sp->name = strdup(sym); /* allocate sp->name @ symbol.h#1 */
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
        print("\n'%s' symbol table is empty!!\n\n", curfilename);
        return;
    }
    print("\nprint '%s' symbol table\n", curfilename);
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
        print("'%s'", sp->name);
        for (rp = rpp; rp; rp = rp->next) {
            if (rp->filename == prevfn) {
                print(" line:%d", rp->lineno);
                print(" val:'%s',", rp->value);
            } else {
                print(" '%s' line:%d", rp->filename, rp->lineno);
                print(" val:'%s',", rp->value);
                prevfn = rp->filename;
            }
        }
        print("\n");
    }
    print("\n");
}

#endif