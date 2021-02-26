
%{

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "m2global.h" 

void m2error(const char* mesg) {
  fprintf(stderr, "Dude, there was a problem on line %d at text '%s':\n\t%s\n", 
    m2lineno, m2text, mesg);
}

%}

%name-prefix "m2"

%token PLUS MINUS STAR SLASH NUMBER SEMI

%left PLUS MINUS
%left STAR SLASH
%nonassoc UMINUS

%%

stmt :                                  { /* empty */ }
     | stmt expr SEMI                   { printf(" ;\n"); }
     ;

expr : expr PLUS expr                   { printf("+ "); }
     | expr MINUS expr                  { printf("- "); }
     | expr STAR expr                   { printf("* "); }
     | expr SLASH expr                  { printf("/ "); }
     | MINUS expr   %prec UMINUS        { printf("uminus ");  }
     | NUMBER                           { printf("%s ", m2text); }
     ;

%%


