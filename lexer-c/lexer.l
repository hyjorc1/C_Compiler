
%{

#include <stdio.h>
#include <string.h>
#include "tokens.h"
#include "scanner.h"

struct bufstack
{
    struct bufstack *prev;
    YY_BUFFER_STATE bs;
    int lineno;
    char *filename;
    FILE *f;
} *curbs = 0;

char *curfilename;
int yylval;

int err_lineno;
char *err_msg;

%}

%option yylineno noyywrap
%x COMMENT

%%

"#include".*\n          { /* ignore */ }

"/*"                    { BEGIN(COMMENT); err_lineno = lineno(); }
<COMMENT>"*/"           { BEGIN(INITIAL); }
<COMMENT>.|\n           { /* ignore */ }
<COMMENT><<EOF>>        { err_msg = (char *) "Unclosed comment"; return ERR; }

<<EOF>>                 { printf("end of file\n"); if(!popfile()) yyterminate(); }

"//".*\n                { /* ignore */ }
[ \t\r\n]*              { /* ignore */ }

"void"      { return TYPE; }
"char"      { return TYPE; }
"int"       { return TYPE; }
"float"     { return TYPE; }

"const"     { return CONST; }
"struct"    { return STRUCT; }
"for"       { return FOR; }
"while"     { return WHILE; }
"do"        { return DO; }
"if"        { return IF; }
"else"      { return ELSE; }
"break"     { return BREAK; }
"continue"  { return CONTINUE; }
"return"    { return RETURN; }

[a-zA-Z_][a-zA-Z_0-9]*              { return IDENT; }

[0-9]+                              { return INTCONST; }

[0-9]*\.[0-9]+([eE][-+]?[0-9]+)?    { return REALCONST; }

\".*\"                              { return STRCONST; }

\'([^\\\']|\\[abnrt\\\'])\'         { return CHARCONST; }


"("         { return LPAR; }
")"         { return RPAR; }
"["         { return LBRACKET; }
"]"         { return RBRACKET; }
"{"         { return LBRACE; }
"}"         { return RBRACE; }

"."         { return DOT; }
","         { return COMMA; }
";"         { return SEMI; }
"?"         { return QUEST; }
":"         { return COLON; }

"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return STAR; }
"/"         { return SLASH; }
"%"         { return MOD; }
"~"         { return TILDE; }

"|"         { return PIPE; }
"&"         { return AMP; }
"!"         { return BANG; }
"||"        { return DPIPE; }
"&&"        { return DAMP; }

"="         { return ASSIGN; }
"+="        { return PLUSASSIGN; }
"-="        { return MINUSASSIGN; }
"*="        { return STARASSIGN; }
"/="        { return SLASHASSIGN; }
"++"        { return INCR; }
"--"        { return DECR; }

"=="        { return EQUALS; }
"!="        { return NEQUAL; }
">"         { return GT; }
">="        { return GE; }
"<"         { return LT; }
"<="        { return LE; }

.	        { printf("bad input character '%s' at line %d\n", yytext, yylineno); }

%%

int newfile(char *fn)
{
    FILE *f = fopen(fn, "r");
    struct bufstack *bs = malloc(sizeof(struct bufstack));
    /* die if no file or no room */
    if (!f) { perror(fn); return 0; }
    if (!bs) { perror("malloc"); exit(1); }
    /* remember state */ 
    if (curbs)
        curbs->lineno = yylineno;
    bs->prev = curbs;
    /* set up current entry */
    bs->bs = yy_create_buffer(f, YY_BUF_SIZE);
    bs->f = f;
    bs->filename = fn;
    yy_switch_to_buffer(bs->bs);
    curbs = bs;
    yylineno = 1;
    curfilename = fn;
    return 1;
}

int popfile(void)
{
    struct bufstack *bs = curbs;
    struct bufstack *prevbs;
    if (!bs)
        return 0;
    /* get rid of current entry */
    fclose(bs->f); 
    yy_delete_buffer(bs->bs);
    /* switch back to previous */
    prevbs = bs->prev;
    free(bs);
    if (!prevbs)
        return 0;
    yy_switch_to_buffer(prevbs->bs);
    curbs = prevbs;
    yylineno = curbs->lineno;
    curfilename = curbs->filename;
    return 1;
}