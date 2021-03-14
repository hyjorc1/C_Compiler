
%{

#include "m3global.h"
#include "parser3.tab.h"      // Bison-generated header file with token names

int m3_err_lineno = 0;

%}

%option prefix = "m3"
%option noyywrap yylineno
%x COMMENT CXXCOMMENT

primtype    void|char|short|int|long|float|double
whitespace  [ \t\r\n]+
identifier  [a-zA-Z_][a-zA-Z_0-9]*
int         [0-9]+ 
real        [0-9]*\.[0-9]+([eE][-+]?[0-9]+)?
str         \".*\"
char        \'([^\\\']|\\[abnrt\\\'])\'
%%

{primtype}      { m3lval.str = strdup(m3text); return PRIMTYPE; }
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
{identifier}    { m3lval.str = strdup(m3text); return IDENT; }

{int}           { m3lval.str = strdup(m3text); return INTCONST; }
{real}          { m3lval.str = strdup(m3text); return REALCONST; }
{str}           { m3lval.str = strdup(m3text); return STRCONST; }
{char}          { m3lval.str = strdup(m3text); return CHARCONST; }

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

"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return STAR; }
"/"             { return SLASH; }
"%"             { return MOD; }
"~"             { return TILDE; }

"|"             { return PIPE; }
"&"             { return AMP; }
"!"             { return BANG; }
"||"            { return DPIPE; }
"&&"            { return DAMP; }

"="             { return ASSIGN; }
"+="            { return PLUSASSIGN; }
"-="            { return MINUSASSIGN; }
"*="            { return STARASSIGN; }
"/="            { return SLASHASSIGN; }
"++"            { return INCR; }
"--"            { return DECR; }

"=="            { return EQUALS; }
"!="            { return NEQUAL; }
">"             { return GT; }
">="            { return GE; }
"<"             { return LT; }
"<="            { return LE; }

"/*"                                {   /* handle c comment */
                                        BEGIN(COMMENT); 
                                        m3_err_lineno = yylineno; 
                                        print("enter COMMENT state\n");
                                    }
<COMMENT>.|\n                       {   /* ignore */    }
<COMMENT>"*/"                       {   BEGIN(INITIAL); print("leave COMMENT state\n"); }
<COMMENT><<EOF>>                    {   /* handle bad input in COMMENT state */
                                        int tmp = m3lineno;
                                        m3lineno = m3_err_lineno;
                                        m3error("unclosed comment");
                                        m3lineno = tmp;
                                        BEGIN(INITIAL);
                                    }


"//"                                {   /* handle c++ comment */
                                        BEGIN(CXXCOMMENT);
                                        print("enter CXXCOMMENT state\n");
                                    }
<CXXCOMMENT>"\n"                    {   BEGIN(INITIAL);    
                                        print("leave CXXCOMMENT state\n");
                                    }
<CXXCOMMENT>.                       {   /* ignore */  }


{whitespace}    { /* whitespace ingnore */ }

.               { fprintf(stderr, "Unexpected text: %s\n", m3text); BEGIN(INITIAL); }




%%

