
%{

#include <stdio.h>
#include <string.h>
#include "tokens.h"
#define ECHO fwrite(yytext, yyleng, 1, yyout)
#define END return terminate();

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

%option yylineno noyywrap nodefault
%x COMMENT
%x IFILE

%%

^"#"[ \t]*"include"[ \t]*[\"<]      {   /* match #include statement up through the quote or < */
                                        BEGIN(IFILE); 
                                    }
<IFILE>[^ \t\n\">]+                 {   /* handle filename up to the closing quote, >, or end of line */
                                        int c; 
                                        while((c = input()) && c != '\n');
                                        newfile(yytext);
                                        BEGIN(INITIAL);
                                    }
<IFILE>.|\n                         {   /* handle bad input in IFILE state */
                                        fprintf(stderr, "%4d bad include line\n", yylineno);
                                        END;
                                    }


"/*"                                {   /* handle c comment */
                                        BEGIN(COMMENT); 
                                        err_lineno = yylineno; 
                                    }
<COMMENT>.|\n                       {   /* ignore */  }
<COMMENT>"*/"                       {   BEGIN(INITIAL); }
<COMMENT><<EOF>>                    {   /* handle bad input in COMMENT state */
                                        fprintf(stderr, "Error near %s line %d\n\t%s\n", curfilename, err_lineno, "Unclosed comment"); 
                                        END; 
                                    }
"//".*\n                            { /* handle c++ comment */ }


[ \t\r\n]*  { /* ignore */ }


"void"      { return TYPE; ECHO; }
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

<<EOF>>     {   
                printf("end of file\n"); 
                BEGIN(INITIAL);
                if (!popfile())
                    yyterminate(); 
            }
\0          { printf("reach to end of string\n"); END; }
.	        { printf("bad input character '%s' at line %d\n", yytext, yylineno); }

%%

int newfile(char *fn)
{
    printf("newfile() %s\n", fn);

    /* check the existance of the file */
    FILE *f = fopen(fn, "r");
    if (!f) {
        if (stack) {
            fprintf(stderr, "Error near %s line %d text '%s'\n", curfilename, yylineno, yytext);
            fprintf(stderr, "\tCouldn't open included file %s\n", yytext);
        } else {
            perror(fn);
        }
        return 0; 
    }
    /* detect cycle */
    struct bufstack *cur = stack;
    while (cur) {
        if (strcmp(cur->filename, fn) == 0) {
            fprintf(stderr, "Error near %s line %d text '%s'\n", curfilename, yylineno, yytext);
            fprintf(stderr, "\t#include cycle:\n");
            return 0;
        }
        cur = cur->prev;
    }

    struct bufstack *bs = malloc(sizeof(struct bufstack));
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

/* void fwrite(char *text, int len, int val, ) {

} */