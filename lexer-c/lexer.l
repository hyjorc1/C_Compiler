
%{

#include <stdio.h>
#include <string.h>
#include "tokens.h"
// #define ECHO fwrite( yytext, yyleng, 1, yyout )

struct bufstack
{
    struct bufstack *prev;  /* previous entry */
    YY_BUFFER_STATE bs;     /* saved buffer */
    int lineno;             /* saved line number */
    char *filename;         /* name of this file */
    FILE *f;                /* current file */
} *stack = NULL;

char *curfilename;
int yylval;

int err_lineno;
char *err_msg;

%}

%option yylineno noyywrap
%x COMMENT

%%

"#include".*\n          { /* ignore */ }

"/*"                    { BEGIN(COMMENT); err_lineno = yylineno; }
<COMMENT>"*/"           { BEGIN(INITIAL); }
<COMMENT>.|\n           { /* ignore */ }
<COMMENT><<EOF>>        { fprintf(stderr, "Error near %s line %d\n\t%s\n", curfilename, err_lineno, "Unclosed comment"); return terminate(); }

<<EOF>>                 { printf("end of file\n"); return terminate(); }

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


\0          { printf("reach to end of string\n"); return terminate(); }
.	        { printf("bad input character '%s' at line %d\n", yytext, yylineno); }

%%

int newfile(char *fn)
{
    printf("newfile() %s\n", fn);
    FILE *f = fopen(fn, "r");
    struct bufstack *bs = malloc(sizeof(struct bufstack));

    /* die if no file or no room */
    if (!f) { perror(fn); return 0; }
    if (!bs) { perror("malloc"); exit(1); }

    /* remember state */ 
    if (stack) {
        printf("newfile() has previous file %s\n", curfilename);
        stack->lineno = yylineno;
    } else {
        printf("newfile() no previous file\n");
    }
    bs->prev = stack;

    /* set up current entry */
    bs->bs = yy_create_buffer(f, YY_BUF_SIZE);
    bs->f = f;
    bs->filename = fn;
    yy_switch_to_buffer(bs->bs);

    stack = bs;
    yylineno = 1;
    curfilename = fn;
    printf("newfile() lineno: %d\n", yylineno);
    return 1;
}

int popfile(void)
{
    printf("popfile() lineno: %d\n", yylineno);
    struct bufstack *bs = stack;
    if (!bs) {
        printf("popfile() current stack is empty");
        return 0;
    }
    
    /* get rid of current entry */
    if (fclose(bs->f) == 0) {
        printf("popfile() closed file %s\n", curfilename);
    }  else {
        printf("popfile() cannot closed file");
    }
    yy_delete_buffer(bs->bs);

    /* switch back to previous */
    stack = bs->prev;
    free(bs);
    if (!stack) {
        printf("popfile() no previous file and current lineno: %d\n", yylineno);
        return 0;
    }
    yy_switch_to_buffer(stack->bs);
    yylineno = stack->lineno;
    printf("popfile() current lineno: %d\n", yylineno);
    curfilename = stack->filename;
    printf("popfile() current file: %s\n", curfilename);
    return 1;
}

int terminate() {
    BEGIN(INITIAL);
    popfile();
    yyterminate();
};