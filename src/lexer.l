
%{

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "global.h"
#include "tokens.h"
#include "symbol.h"
#include "macro.h"
#define END return terminate();

/*  ----------------- file buffer list ----------------- */
struct filebuf
{
    struct filebuf *prev;
    struct filebuf *next;
    YY_BUFFER_STATE bs;     /* saved buffer */
    int lineno;             /* saved line number */
    char *filename;         /* name of this file */
    FILE *f;                /* current file */
    struct node *macros;    /* saved new macros */
} *filebuflist = 0;

int filebuflistsize = 0;
#define BUFFER_LIST_SIZE_LIMIT 256

char *token_str;
char *curfilename;
int err_lineno;

/*  ----------------- macro buffer list ----------------- */
struct macrobuf
{
    struct macrobuf *prev;
    struct macrobuf *next;
    YY_BUFFER_STATE bs;
    char *name; 
} *macrobuflist = 0;

int macrobuflistsize = 0;
char *symbolname;
#define REP_SIZE_LIMIT 4096

/*  ----------------- define if  ----------------- */


%}

%option yylineno noyywrap nodefault
%x COMMENT CXXCOMMENT
%x IFILE
%x DEFINE_KEY DEFINE_VAL UNDEFINE
%x DEFINE_IF DEFINE_IFN DEFINE_ELSE DEFINE_END

%%

^"#"[ \t]*"include"[ \t]*[\"]       {   /* handle #include statement up through the quote */
                                        BEGIN(IFILE);
                                        print("enter IFILE state\n");
                                        err_lineno = yylineno;
                                    }
<IFILE>[^ \t\n\">]+                 {   /* handle filename up to the closing quote, >, or end of line */
                                        int c = input(); 
                                        if (c == '"') {
                                            while((c = input()) && c != '\n');
                                            if (!newfile(yytext)) {
                                                fprintf(stderr, "Error near %s line %d text '%s'\n", curfilename, err_lineno, yytext);
                                                fprintf(stderr, "\tCouldn't open included file %s\n", yytext);
                                            }
                                            BEGIN(INITIAL);
                                            print("leave IFILE state\n");
                                        }
                                    }
<IFILE>.|\n                         {   /* handle bad input in IFILE state */
                                        fprintf(stderr, "Error near %s line %d bad #include\n", curfilename, err_lineno);
                                        END;
                                    }
<IFILE><<EOF>>                      {   /* handle bad input in IFILE state */
                                        fprintf(stderr, "Error near %s line %d bad #include\n", curfilename, err_lineno);
                                        END;
                                    }


^"#"[ \t]*"define"[ \t]*            {   /* handle #define  */
                                        BEGIN(DEFINE_KEY);
                                        print("enter DEFINE_KEY state\n");
                                        err_lineno = yylineno;
                                    }
<DEFINE_KEY>[^ \t\n]+               {   /*  */
                                        symbolname = strdup(yytext);
                                        BEGIN(DEFINE_VAL);
                                        print("leave DEFINE_KEY state\n");
                                        print("enter DEFINE_VAL state\n");
                                    }
<DEFINE_KEY>.|\n                    {   /* handle bad #define  */
                                        fprintf(stderr, "Error near %s line %d bad #define\n", curfilename, err_lineno);
                                        END;
                                    }
<DEFINE_KEY><<EOF>>                 {   /* handle bad #define  */
                                        fprintf(stderr, "Error near %s line %d bad #define\n", curfilename, err_lineno);
                                        END;
                                    }
<DEFINE_VAL>[^\n]+                  {   
                                        int text_size = strlen(yytext);
                                        if (text_size >= REP_SIZE_LIMIT) {
                                            fprintf(stderr, "Error near %s line %d the length of the replacement text is larger the limit %d\n", curfilename, err_lineno, REP_SIZE_LIMIT);
                                        } else if (addref(err_lineno, curfilename, symbolname, yytext, 0)) {
                                            addmacro(symbolname);
                                        }
                                        BEGIN(INITIAL);
                                        print("leave DEFINE_VAL state\n");
                                    }
<DEFINE_VAL><<EOF>>                 {
                                        BEGIN(INITIAL);
                                        if (!popfile())
                                            yyterminate();
                                    }


^"#"[ \t]*"undef"[ \t]*             {   /* handle #undef  */
                                        BEGIN(UNDEFINE);
                                        print("enter UNDEFINE state\n");
                                        err_lineno = yylineno;
                                    }
<UNDEFINE>[^ \t\n]+                 {   /*  */
                                        removeref(yytext);
                                        BEGIN(INITIAL);
                                        print("leave UNDEFINE state\n");
                                    }


"/*"                                {   /* handle c comment */
                                        BEGIN(COMMENT); 
                                        err_lineno = yylineno; 
                                        print("enter COMMENT state\n");
                                    }
<COMMENT>.|\n                       {   /* ignore */  }
<COMMENT>"*/"                       {   BEGIN(INITIAL); print("leave COMMENT state\n"); }
<COMMENT><<EOF>>                    {   /* handle bad input in COMMENT state */
                                        fprintf(stderr, "Error near %s line %d\n\t%s\n", curfilename, err_lineno, "Unclosed comment\n"); 
                                        END; 
                                    }


"//"                                {   /* handle c++ comment */
                                        BEGIN(CXXCOMMENT);
                                        print("enter CXXCOMMENT state\n");
                                    }
<CXXCOMMENT>"\n"                    {   BEGIN(INITIAL);    
                                        print("leave CXXCOMMENT state\n");
                                    }
<CXXCOMMENT>.                       {   /* ignore */  }                                 


[ \t\r\n]*                          {   /* whitespace ingnore */    }


<<EOF>>                             {   /* end of file */
                                        print("end of file and beign INITIAL state\n"); 
                                        BEGIN(INITIAL);
                                        if (!popfile())
                                            yyterminate();
                                    }


"void"      { token_str = "TYPE"; return TYPE; }
"char"      { token_str = "TYPE"; return TYPE; }
"int"       { token_str = "TYPE"; return TYPE; }
"float"     { token_str = "TYPE"; return TYPE; }

"const"     { token_str = "CONST"; return CONST; }
"struct"    { token_str = "STRUCT"; return STRUCT; }
"for"       { token_str = "FOR"; return FOR; }
"while"     { token_str = "WHILE"; return WHILE; }
"do"        { token_str = "DO"; return DO; }
"if"        { token_str = "IF"; return IF; }
"else"      { token_str = "ELSE"; return ELSE; }
"break"     { token_str = "BREAK"; return BREAK; }
"continue"  { token_str = "CONTINUE"; return CONTINUE; }
"return"    { token_str = "RETURN"; return RETURN; }


[a-zA-Z_][a-zA-Z_0-9]*              {
                                        token_str = "IDENT";
                                        if (!newmacro(yytext))
                                            return IDENT; 
                                    }

[0-9]+                              { token_str = "INTCONST"; return INTCONST; }

[0-9]*\.[0-9]+([eE][-+]?[0-9]+)?    { token_str = "REALCONST"; return REALCONST; }

\".*\"                              { token_str = "STRCONST"; return STRCONST; }

\'([^\\\']|\\[abnrt\\\'])\'         { token_str = "CHARCONST"; return CHARCONST; }


"("         { token_str = "LPAR"; return LPAR; }
")"         { token_str = "RPAR"; return RPAR; }
"["         { token_str = "LBRACKET"; return LBRACKET; }
"]"         { token_str = "RBRACKET"; return RBRACKET; }
"{"         { token_str = "LBRACE"; return LBRACE; }
"}"         { token_str = "RBRACE"; return RBRACE; }

"."         { token_str = "DOT"; return DOT; }
","         { token_str = "COMMA"; return COMMA; }
";"         { token_str = "SEMI"; return SEMI; }
"?"         { token_str = "QUEST"; return QUEST; }
":"         { token_str = "COLON"; return COLON; }

"+"         { token_str = "PLUS"; return PLUS; }
"-"         { token_str = "MINUS"; return MINUS; }
"*"         { token_str = "STAR"; return STAR; }
"/"         { token_str = "SLASH"; return SLASH; }
"%"         { token_str = "MOD"; return MOD; }
"~"         { token_str = "TILDE"; return TILDE; }

"|"         { token_str = "PIPE"; return PIPE; }
"&"         { token_str = "AMP"; return AMP; }
"!"         { token_str = "BANG"; return BANG; }
"||"        { token_str = "DPIPE"; return DPIPE; }
"&&"        { token_str = "DAMP"; return DAMP; }

"="         { token_str = "ASSIGN"; return ASSIGN; }
"+="        { token_str = "PLUSASSIGN"; return PLUSASSIGN; }
"-="        { token_str = "MINUSASSIGN"; return MINUSASSIGN; }
"*="        { token_str = "STARASSIGN"; return STARASSIGN; }
"/="        { token_str = "SLASHASSIGN"; return SLASHASSIGN; }
"++"        { token_str = "INCR"; return INCR; }
"--"        { token_str = "DECR"; return DECR; }

"=="        { token_str = "EQUALS"; return EQUALS; }
"!="        { token_str = "NEQUAL"; return NEQUAL; }
">"         { token_str = "GT"; return GT; }
">="        { token_str = "GE"; return GE; }
"<"         { token_str = "LT"; return LT; }
"<="        { token_str = "LE"; return LE; }

\0          { print("reach to end of string\n"); END; }
.	        { fprintf(stderr, "Error near %s bad input character '%s' at line %d\n", curfilename, yytext, yylineno); }

%%

void addmacro(char * sym) {
    print("addmacro() add new marco %s\n", sym);
    struct node *link = (struct node*) malloc(sizeof(struct node));
    link->data = sym;
    link->next = filebuflist->macros;
    filebuflist->macros = link;
}

int terminate() {
    BEGIN(INITIAL);
    popfile();
    yyterminate();
};

int newmacro(char* ident) {
    /* limit buffer list size <= 256 */
    if (macrobuflistsize >= BUFFER_LIST_SIZE_LIMIT) {
        fprintf(stderr, "Error reaching to macro buffer list size %d\n", BUFFER_LIST_SIZE_LIMIT);
        return 0;
    }

    /* detect cycle */
    struct macrobuf *cur = macrobuflist;
    while (cur) {
        /* printf("cycle macro buf %s %d\n", cur->filename, strcmp(cur->filename, fn)); */
        if (strcmp(cur->name, ident) == 0) {
            fprintf(stderr, "Error near %s line %d text '%s'\n", curfilename, yylineno, ident);
            fprintf(stderr, "\t#define substituion cycle:\n");
            while (cur != macrobuflist) {
                fprintf(stderr, "\t%s macro contains %s\n", cur->name, cur->next->name);
                cur = cur->next;
            }
            fprintf(stderr, "\t%s macro contains %s\n", cur->name, ident);
            return 0;
        }
        cur = cur->prev;
    }

    struct symbol *sp = lookup(ident);
    if (!sp || !sp->name || !sp->reflist || sp->reflist->filename != curfilename) {
        return 0;
    }

    print("newmacro() check id %s wiht val:%s-\n", ident, sp->reflist->value);

    struct macrobuf *mb = (struct macrobuf*)malloc(sizeof(struct macrobuf));
    if (!mb) { perror("malloc"); exit(1); }

    mb->name = sp->name;
    mb->bs = yy_scan_string(sp->reflist->value);
    yy_switch_to_buffer(mb->bs);

    /* list <- fb */
    mb->prev = macrobuflist;
    if (macrobuflist) {
        macrobuflist->next = mb;
    }
    macrobuflist = mb;

    macrobuflistsize++;
    print("newmacro() buffer list size: %d\n", macrobuflistsize);
    return 1;
}

int popmacro() {
    print("popmacro() lineno: %d\n", yylineno);

    struct macrobuf *mb = macrobuflist;
    if (!mb) {
        print("popmacro() current list is empty");
        yy_switch_to_buffer(filebuflist->bs);
        return 0;
    }

    yy_delete_buffer(mb->bs);

    /* switch back to previous */
    macrobuflist = mb->prev;
    if (macrobuflist) {
        macrobuflist->next = 0;
    }
    macrobuflistsize--;
    print("popmacro() buffer list size: %d\n", macrobuflistsize);
    if (!macrobuflist) {
        print("popmacro() no previous macro buf and current lineno: %d\n", yylineno);
        yy_switch_to_buffer(filebuflist->bs);
        return 0;
    }

    yy_switch_to_buffer(macrobuflist->bs);
    print("popmacro() macro buf $s with lineno %d\n", macrobuflist->name, yylineno);

    return 1;
};

int newfile(char *fn)
{
    print("newfile() %s\n", fn);

    /* limit buffer list size <= 256 */
    if (filebuflistsize >= BUFFER_LIST_SIZE_LIMIT) {
        fprintf(stderr, "Error reaching to file buffer list size %d\n", BUFFER_LIST_SIZE_LIMIT);
        return 0;
    }

    /* detect cycle */
    struct filebuf *cur = filebuflist;
    while (cur) {
        /* printf("cycle file %s %d\n", cur->filename, strcmp(cur->filename, fn)); */
        if (strcmp(cur->filename, fn) == 0) {
            fprintf(stderr, "Error near %s line %d text '%s'\n", curfilename, err_lineno, yytext);
            fprintf(stderr, "\t#include cycle:\n");
            while (cur != filebuflist) {
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

    struct filebuf *fb = (struct filebuf*)malloc(sizeof(struct filebuf));
    if (!fb) { perror("malloc"); exit(1); }

    /* remember state */ 
    if (filebuflist) {
        print("newfile() has previous file %s\n", curfilename);
        filebuflist->lineno = yylineno;
    } else {
        print("newfile() no previous file\n");
    }
    
    /* set up current entry */
    fb->bs = yy_create_buffer(f, YY_BUF_SIZE);
    fb->f = f;
    fb->filename = fn;
    yy_switch_to_buffer(fb->bs);

    /* list <- fb */
    fb->prev = filebuflist;
    if (filebuflist) {
        filebuflist->next = fb;
    }
    filebuflist = fb;
    
    yylineno = 1;
    err_lineno = 0;
    curfilename = fn;
    filebuflistsize++;
    print("newfile() buffer list size: %d\n", filebuflistsize);
    return 1;
}

int popfile(void)
{
    if (macrobuflist) {
        popmacro();
        return 1;
    }

    print("popfile() lineno: %d\n", yylineno);
    struct filebuf *fb = filebuflist;
    if (!fb) {
        print("popfile() current list is empty");
        return 0;
    }
    
    /* get rid of current entry */
    if (fclose(fb->f) == 0) {
        print("popfile() closed file %s\n", fb->filename);
    }  else {
        print("popfile() cannot closed file");
    }
    yy_delete_buffer(fb->bs);
    /* clear macro records */
    /* printmacros(fb->macros); */
    struct node *ptr = fb->macros;
    while (ptr) {
        removeref(ptr->data);
        ptr = ptr->next;
    }
    free(fb);
    /* printrefs(); */

    /* switch back to previous */
    filebuflist = fb->prev;
    if (filebuflist) {
        filebuflist->next = 0;
    }
    filebuflistsize--;
    print("popfile() buffer list size: %d\n", filebuflistsize);
    if (!filebuflist) {
        print("popfile() no previous file and current lineno: %d\n", yylineno);
        return 0;
    }

    yy_switch_to_buffer(filebuflist->bs);
    yylineno = filebuflist->lineno;
    curfilename = filebuflist->filename;
    print("popfile() current file $s with lineno %d\n", curfilename, yylineno);
    return 1;
}