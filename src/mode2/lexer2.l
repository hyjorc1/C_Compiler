
%{

#include "parser2.tab.h"      // Bison-generated header file with token names
#include "m2global.h"

%}

%option prefix = "m2"
%option noyywrap yylineno

%%

[0-9]+        { m2lval.number = atol(m2text);  return NUMBER; }
"+"           { return PLUS; }
"-"           { return MINUS; }
"*"           { return STAR; }
"/"           { return SLASH; }
";"           { return SEMI; }
[ \t\n\r]     { /* */ }
.             { fprintf(stderr, "Unexpected text: %s\n", m2text); }

%%

