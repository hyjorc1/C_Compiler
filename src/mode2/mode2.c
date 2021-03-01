#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

#include "m2global.h"


void gll_print(void *x) 
{ 
    printf("Value of a is %s\n", *(char **)x);
}

void mode2(int argc, char *argv[], int fileIdx) {
    for (int i = fileIdx; i < argc; i++) {
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

    // gll_t *list = gll_init();
    // char *a = "1";
    // char *b = "2";
    // char *c = "3";

    // void *p = &a;


    // gll_pushBack(list, &a);
    // gll_pushBack(list, &b);
    // gll_pushBack(list, &c);
    // assert(list->size == 3);

    // gll_each(list, &gll_print);

    // assert(gll_popBack(list) == &c);
    // assert(list->first->data == &a);
    // assert(list->first->next->data == &b);
    // assert(list->last->data == &b);
    // assert(list->last->prev->data == &a);
    // assert(list->last->next == NULL);
    // assert(list->size == 2);

    // assert(gll_popBack(list) == &b);
    // assert(list->size == 1);

    // assert(gll_popBack(list) == &a);
    // assert(list->first == NULL);
    // assert(list->last == NULL);
    // assert(list->size == 0);

    

    // gll_destroy(list);
}





