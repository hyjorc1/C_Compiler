#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "global.h"

struct node {
    char *data;
    struct node *next;
};

void printmacros(struct node *list) {
   struct node *ptr = list;
   printf("\n[ ");
   while(ptr != NULL) {
      printf("%s, ",  ptr->data);
      ptr = ptr->next;
   }
   printf(" ]\n");
}

