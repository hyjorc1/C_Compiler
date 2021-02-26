
%{

#include <stdio.h>
#include "parse.h"

int yylex();      // flex builds this for us

extern int yylineno;
extern char* yytext;

void yyerror(const char* mesg)
{
  fprintf(stderr, "Dude, there was a problem on line %d at text '%s':\n\t%s\n", 
    yylineno, yytext, mesg);
}

%}

%union {
  long number;
  struct expr* tree;
}

%token <number> NUMBER
%token PLUS MINUS STAR SLASH SEMI

%type <tree> expr

%left PLUS MINUS
%left STAR SLASH
%nonassoc UMINUS

%%

oneexpr
     : expr                             { saveRoot($1); }
     ;

expr : expr PLUS expr                   { $$ = makeBinary($1, '+', $3); }
     | expr MINUS expr                  { $$ = makeBinary($1, '-', $3); }
     | expr STAR expr                   { $$ = makeBinary($1, '*', $3); }
     | expr SLASH expr                  { $$ = makeBinary($1, '/', $3); }
     | MINUS expr   %prec UMINUS        { $$ = makeBinary(NULL, 'u', $2); }
     | NUMBER                           { $$ = makeNumber($1); }
     ;

%%

