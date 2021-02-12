
%{

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

using namespace std;

int yylval;

%}

%option noyywrap
%option c++

%%

[0-9]+      { yylval = atoi(yytext);  return NUMBER; }
[ \t\r\n]*  { /* ignore */ }
"+"         { return PLUS; }
"*"         { return STAR; }
.           { fprintf(stderr, "Error: bad character '%c'\n", yytext[0]);  exit(1);  }

%%

/*
  No other code needed
  because it's in other source files.
*/

