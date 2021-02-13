
%{

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
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
} *buflist = NULL;

char *curfilename;
int debug = 0;

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
                                        if (!newfile(yytext)) {
                                            fprintf(stderr, "Error near %s line %d text '%s'\n", curfilename, yylineno, yytext);
                                            fprintf(stderr, "\tCouldn't open included file %s\n", yytext);
                                        }
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

<<EOF>>     {   
                print("end of file\n"); 
                BEGIN(INITIAL);
                if (!popfile())
                    yyterminate(); 
            }
\0          { print("reach to end of string\n"); END; }
.	        { print("bad input character '%s' at line %d\n", yytext, yylineno); }

%%

int newfile(char *fn)
{
    print("newfile() %s\n", fn);

    /* detect cycle */
    struct listnode *cur = buflist;
    while (cur) {
        /* printf("cycle file %s %d\n", cur->filename, strcmp(cur->filename, fn)); */
        if (strcmp(cur->filename, fn) == 0) {
            fprintf(stderr, "Error near %s line %d text '%s'\n", curfilename, yylineno, yytext);
            fprintf(stderr, "\t#include cycle:\n");
            while (cur != buflist) {
                fprintf(stderr, "\tFile %s includes %s\n", cur->filename, cur->next->filename);
                cur = cur->next;
            }
            fprintf(stderr, "\tFile %s includes %s\n", cur->filename, fn);
            return 0;
        }
        cur = cur->prev;
    }

    /* check the existance of the file */
    FILE *f = fopen(fn, "r");
    if (!f) { perror(fn); return 0; }

    struct listnode *node = malloc(sizeof(struct listnode));
    if (!node) { perror("malloc"); exit(1); }

    /* remember state */ 
    if (buflist) {
        print("newfile() has previous file %s\n", curfilename);
        buflist->lineno = yylineno;
    } else {
        print("newfile() no previous file\n");
    }
    
    /* set up current entry */
    node->bs = yy_create_buffer(f, YY_BUF_SIZE);
    node->f = f;
    node->filename = fn;
    yy_switch_to_buffer(node->bs);

    /* list <- node */
    node->prev = buflist;
    if (buflist) {
        buflist->next = node;
    }
    buflist = node;
    
    yylineno = 1;
    curfilename = fn;
    print("newfile() lineno: %d\n", yylineno);
    return 1;
}

int popfile(void)
{
    print("popfile() lineno: %d\n", yylineno);
    struct listnode *node = buflist;
    if (!node) {
        print("popfile() current list is empty");
        return 0;
    }
    
    /* get rid of current entry */
    if (fclose(node->f) == 0) {
        print("popfile() closed file %s\n", node->filename);
    }  else {
        print("popfile() cannot closed file");
    }
    yy_delete_buffer(node->bs);

    /* switch back to previous */
    buflist = node->prev;
    if (buflist) {
        buflist->next = NULL;
    }

    free(node);
    if (!buflist) {
        print("popfile() no previous file and current lineno: %d\n", yylineno);
        return 0;
    }

    yy_switch_to_buffer(buflist->bs);
    yylineno = buflist->lineno;
    curfilename = buflist->filename;
    print("popfile() current lineno: %d\n", yylineno);
    print("popfile() current file: %s\n", curfilename);
    return 1;
}

int terminate() {
    BEGIN(INITIAL);
    popfile();
    yyterminate();
};

void print(const char *format, ...) {
    if (debug) {
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    }
}

/* void fwrite(char *text, int len, int val, ) {

} */