
%{

#include "parser2.tab.h"      // Bison-generated header file with token names
#include "m2global.h"

%}

%option prefix = "m2"
%option noyywrap yylineno

type void|char|short|int|long|float|double
whitespace  [ \t\r\n]+
identifier  [a-zA-Z_][a-zA-Z_0-9]*
int         [0-9]+ 
real        [0-9]*\.[0-9]+([eE][-+]?[0-9]+)?
str         \".*\"
char        \'([^\\\']|\\[abnrt\\\'])\'
unary_op    [-!~]
bianry_op   "=="|"!="|">"|">="|"<"|"<="|"+"|"-"|"*"|"/"|"%"|"|"|"&"|"||"|"&&"
assign_op   "="|"+="|"-="|"*="|"/="
increment   "++"
decrement   "--"
%%

{type}          { return TYPE; }
const           { return CONST; }
struct          { return STRUCT; }
for             { return FOR; }
while           { return WHILE; }
do              { return DO; }
if              { return IF; }
else            { return ELSE; }
break           { return BREAK; }
continue        { return CONTINUE; }
return          { return RETURN; }
{identifier}    { m2lval.str = strdup(m2text); return IDENT; }

{int}           { return INTCONST; }
{real}          { return REALCONST; }
{str}           { return STRCONST; }
{char}          { return CHARCONST; }

"("             { return LPAR; }
")"             { return RPAR; }
"["             { return LBRACKET; }
"]"             { return RBRACKET; }
"{"             { return LBRACE; }
"}"             { return RBRACE; }

"."             { return DOT; }
","             { return COMMA; }
";"             { return SEMI; }
"?"             { return QUEST; }
":"             { return COLON; }

{unary_op}      { return UN_OP; }
{bianry_op}     { return BIN_OP; }
{assign_op}     { return ASSN_OP; }

{increment}     { return INCREMENT; }
{decrement}     { return DECREMENT; }

{whitespace}    { /* whitespace ingnore */ }

.               { fprintf(stderr, "Unexpected text: %s\n", m2text); }




%%

