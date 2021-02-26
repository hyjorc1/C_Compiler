
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
     | NUMBER                           { printf("%s ", yytext); }
     ;

%%

int main()
{
  int code = yyparse();
  printf("yyparse returned %d\n", code);
  return 0;
}
