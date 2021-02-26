
%{

#include <stdio.h>

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
}

%token <number> NUMBER
%token PLUS MINUS STAR SLASH SEMI

%type <number> expr

%left PLUS MINUS
%left STAR SLASH
%nonassoc UMINUS

%%

stmt :                                  { /* empty */ }
     | stmt expr SEMI                   { printf("evaluated to %ld\n", $2); }
     ;

expr : expr PLUS expr                   { $$ = $1 + $3; }
     | expr MINUS expr                  { $$ = $1 - $3; }
     | expr STAR expr                   { $$ = $1 * $3; }
     | expr SLASH expr                  { $$ = $1 / $3; }
     | MINUS expr   %prec UMINUS        { $$ = -$2;  }
     | NUMBER                           { $$ = $1; }
     ;

%%

int main()
{
  int code = yyparse();
  printf("yyparse returned %d\n", code);
  return 0;
}
