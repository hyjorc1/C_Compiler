
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

%define api.prefix {m2}


%union {
  long number;
}

%token <number> NUMBER
%token PLUS MINUS STAR SLASH SEMI

%type <number> expr

%left PLUS MINUS
%left STAR SLASH
%nonassoc UMINUS

%%

stmt :                                  { /* empty */ }
     | stmt expr SEMI                   { printf(" ; "); printf("evaluated to %ld\n", $2); }
     ;

expr : expr PLUS expr                   { $$ = $1 + $3; printf("+ "); }
     | expr MINUS expr                  { $$ = $1 - $3; printf("- "); }
     | expr STAR expr                   { $$ = $1 * $3; printf("* "); }
     | expr SLASH expr                  { $$ = $1 / $3; printf("/ "); }
     | MINUS expr   %prec UMINUS        { $$ = -$2; printf("uminus "); }
     | NUMBER                           { $$ = $1; printf("%s ", m2text); }
     ;

%%


