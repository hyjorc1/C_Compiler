#ifndef MACRO_H
#define MACRO_H

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "global.h"

struct node {
    char *data;
    struct node *next;
};

void printmacros(struct node *macros) {
   struct node *ptr = macros;
   printf("\n'%s' macro buf [ ", curfilename);
   while(ptr) {
      printf("'%s', ",  ptr->data);
      ptr = ptr->next;
   }
   printf(" ]\n");
}

#endif