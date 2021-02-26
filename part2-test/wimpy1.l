
%{

#include "wimpy1.tab.h"      // Bison-generated header file with token names

%}

%option noyywrap yylineno

%%

[0-9]+        { return NUMBER; }
"+"           { return PLUS; }
"-"           { return MINUS; }
"*"           { return STAR; }
"/"           { return SLASH; }
";"           { return SEMI; }
[ \t\n\r]     { /* */ }
.             { fprintf(stderr, "Unexpected text: %s\n", yytext); }

%%

/* No extra C code here */

