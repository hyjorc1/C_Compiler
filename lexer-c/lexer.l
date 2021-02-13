
%{

#include <stdio.h>
#include <string.h>
#include "tokens.h"
#define ECHO fwrite(yytext, yyleng, 1, yyout)
#define END return terminate();

struct listnode
{
    struct listnode *prev;
    struct listnode *next;
    YY_BUFFER_STATE bs;     /* saved buffer */
    int lineno;             /* saved line number */
    char *filename;         /* name of this file */
    FILE *f;                /* current file */
} *list = NULL;

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
        if (list) {
            fprintf(stderr, "Error near %s line %d text '%s'\n", curfilename, yylineno, yytext);
            fprintf(stderr, "\tCouldn't open included file %s\n", yytext);
        } else {
            perror(fn);
        }
        return 0; 
    }
    /* detect cycle */
    /* struct listnode *cur = list;
    while (cur) {
        if (strcmp(cur->filename, fn) == 0) {
            fprintf(stderr, "Error near %s line %d text '%s'\n", curfilename, yylineno, yytext);
            fprintf(stderr, "\t#include cycle:\n");
            return 0;
        }
        cur = cur->prev;
    } */

    struct listnode *node = malloc(sizeof(struct listnode));
    if (!node) { perror("malloc"); exit(1); }

    /* remember state */ 
    if (list) {
        printf("newfile() has previous file %s\n", curfilename);
        list->lineno = yylineno;
    } else {
        printf("newfile() no previous file\n");
    }
    
    /* set up current entry */
    node->bs = yy_create_buffer(f, YY_BUF_SIZE);
    node->f = f;
    node->filename = fn;
    yy_switch_to_buffer(node->bs);

    /* list <- node */
    node->prev = list;
    if (list) {
        list->next = node;
    }
    list = node;
    
    yylineno = 1;
    curfilename = fn;
    printf("newfile() lineno: %d\n", yylineno);
    return 1;
}

int popfile(void)
{
    printf("popfile() lineno: %d\n", yylineno);
    struct listnode *node = list;
    if (!node) {
        printf("popfile() current list is empty");
        return 0;
    }
    
    /* get rid of current entry */
    if (fclose(node->f) == 0) {
        printf("popfile() closed file %s\n", curfilename);
    }  else {
        printf("popfile() cannot closed file");
    }
    yy_delete_buffer(node->bs);

    /* switch back to previous */
    list = node->prev;
    if (list) {
        list->next = NULL;
    }

    free(node);
    if (!list) {
        printf("popfile() no previous file and current lineno: %d\n", yylineno);
        return 0;
    }

    yy_switch_to_buffer(list->bs);
    yylineno = list->lineno;
    curfilename = list->filename;
    printf("popfile() current lineno: %d\n", yylineno);
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