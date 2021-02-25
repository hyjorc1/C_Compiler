
%{

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "global.h"
#include "tokens.h"
#include "symbol.h"
#include "ifdef.h"
#define END return terminate();

/*  ----------------- file buffer list ----------------- */

struct filebuf {
    struct filebuf *prev;
    struct filebuf *next;
    YY_BUFFER_STATE bs;     /* saved buffer */
    int lineno;             /* saved line number */
    char *filename;         /* name of this file */
    FILE *f;                /* current file */
    struct ifdef *iflist;   /* saved iflist */
    int iflistsize;
} *filebuflist = 0;

int filebuflistsize = 0;
int err_lineno = 0;

char *token_str = 0;
char *curfilename = 0;

/*  ----------------- macro buffer list ----------------- */

struct macrobuf {
    struct macrobuf *prev;
    struct macrobuf *next;
    YY_BUFFER_STATE bs;
    char *name; 
} *macrobuflist = 0;

int macrobuflistsize = 0;
char *symbolname = 0;

/*  --------------------------------------------------- */

%}

%option yylineno noyywrap nodefault
%x COMMENT CXXCOMMENT
%x IFILE
%x DEFINE_KEY DEFINE_VAL UNDEFINE
%x IFDEF SKIP

%%

"#"[ \t]*"ifdef"[ \t]*              {   /* handle #ifdef  */
                                        BEGIN(IFDEF);
                                        print("find '%s' enter IFDEF state at line %d\n", yytext, yylineno);
                                        newifdef(1, 0);
                                    }
"#"[ \t]*"ifndef"[ \t]*             {   /* handle #ifndef  */
                                        BEGIN(IFDEF);
                                        print("find '%s' enter IFDEF state at line %d\n", yytext, yylineno);
                                        newifdef(0, 0);
                                    }
<IFDEF>[^ \t\n]+                    {
                                        struct symbol *sp = lookup(yytext);
                                        if (!sp || !sp->name || !sp->reflist || sp->reflist->filename != curfilename) {
                                            if (iflist->isifdef == 1) {
                                                print("ifdef not found '%s' enter SKIP state at line %d\n", yytext, yylineno);
                                                BEGIN(SKIP);
                                            } else {
                                                print("ifndef not found '%s' enter INITIAL state at line %d\n", yytext, yylineno);
                                                iflist->satisfy = 1;
                                                BEGIN(INITIAL);
                                            }
                                        } else {
                                            if (iflist->isifdef == 1) {
                                                print("ifdef found '%s' enter INITIAL state at line %d\n", yytext, yylineno);
                                                iflist->satisfy = 1;
                                                BEGIN(INITIAL);
                                            } else {
                                                print("ifdef found '%s' enter SKIP state at line %d\n", yytext, yylineno);
                                                BEGIN(SKIP);
                                            }
                                        }
                                    }
"#"[ \t]*"else"[ \t]*               {   /* handle #else  */
                                        print("find #else\n");
                                        if (!iflist) {
                                            fprintf(stderr, "Error near %s line %d text '%s'\n", curfilename, yylineno, yytext);
                                            fprintf(stderr, "\t#endif with no matching #ifdef/#ifndef, ignoring\n");
                                            BEGIN(INITIAL);
                                        }
                                        if (iflist->else_lineno > 0) {
                                            fprintf(stderr, "Error near %s line %d\n", curfilename, yylineno);
                                            fprintf(stderr, "\tsecond #else (first on line %d), ignoring\n", iflist->else_lineno);
                                        } else {
                                            if (iflist->satisfy == 1) {
                                                print("enter SKIP state at line %d\n", yylineno);
                                                BEGIN(SKIP);
                                            } else {
                                                print("enter INITIAL state at line %d\n", yylineno);
                                                BEGIN(INITIAL);
                                            }
                                            iflist->else_lineno = yylineno;
                                        }
                                    }
"#"[ \t]*"endif"[ \t]*              {   /* handle #endif  */
                                        print("find #endif\n");
                                        if (!iflist) {
                                            fprintf(stderr, "Error near %s line %d text '%s'\n", curfilename, yylineno, yytext);
                                            fprintf(stderr, "\t#endif with no matching #ifdef/#ifndef, ignoring\n");
                                            BEGIN(INITIAL);
                                        } else {
                                            popifdef();
                                        }
                                    }
<SKIP>"#"[ \t]*"ifdef"[ \t]*        {   /* handle <SKIP>#ifdef  */
                                        print("find <SKIP>#ifdef at line %d\n", yylineno);
                                        newifdef(1, 1);
                                    }
<SKIP>"#"[ \t]*"ifndef"[ \t]*       {   /* handle <SKIP>#ifndef  */
                                        print("find <SKIP>#ifndef at line %d\n", yylineno);
                                        newifdef(0, 1);
                                    }
<SKIP>"#"[ \t]*"else"[ \t]*         {   /* handle <SKIP>#else  */
                                        print("find <SKIP>#else enter INITIAL state at line %d\n", yylineno);
                                        if (!iflist) {
                                            fprintf(stderr, "Error near %s line %d text '%s'\n", curfilename, yylineno, yytext);
                                            fprintf(stderr, "\t#endif with no matching #ifdef/#ifndef, ignoring\n");
                                            BEGIN(INITIAL);
                                        }
                                        if (iflist->else_lineno > 0) {
                                            fprintf(stderr, "Error near %s line %d\n", curfilename, yylineno);
                                            fprintf(stderr, "\tsecond #else (first on line %d), ignoring\n", iflist->else_lineno);
                                        } else {
                                            if (iflist->skip == 0)
                                                BEGIN(INITIAL);
                                            iflist->else_lineno = yylineno;
                                        }
                                    }
<SKIP>"#"[ \t]*"endif"[ \t]*        {   /* handle <SKIP>#endif */
                                        print("find #endif enter INITIAL state at line %d\n", yylineno);
                                        if (!iflist) {
                                            fprintf(stderr, "Error near %s line %d text '%s'\n", curfilename, yylineno, yytext);
                                            fprintf(stderr, "\t#endif with no matching #ifdef/#ifndef, ignoring\n");
                                            BEGIN(INITIAL);
                                        } else {
                                            if (iflist->skip == 0)
                                                BEGIN(INITIAL);
                                            popifdef();
                                        }
                                    }
<SKIP>\".*\"|.|\n                   {   /* ignore string and anything else */  }


"#"[ \t]*"include"[ \t]*[\"]        {   /* handle #include statement up through the quote */
                                        BEGIN(IFILE);
                                        print("enter IFILE state\n");
                                        err_lineno = yylineno;
                                    }
<IFILE>[^ \t\n\">]+                 {   /* handle filename up to the closing quote, >, or end of line */
                                        int c = input(); 
                                        if (c == '"') {
                                            while((c = input()) && c != '\n');
                                            if (!newfile(yytext)) {
                                                fprintf(stderr, "Error near %s line %d\n", curfilename, err_lineno);
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


"#"[ \t]*"define"[ \t]*             {   /* handle #define  */
                                        BEGIN(DEFINE_KEY);
                                        print("enter DEFINE_KEY state\n");
                                        err_lineno = yylineno;
                                    }
<DEFINE_KEY>[^ \t\n]+               {   /*  */
                                        free(symbolname); /* free symbolname @ lexer.l#2 */
                                        symbolname = strdup(yytext); /* allocate symbolname @ lexer.l#2 */
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
                                        if (text_size >= REPRESENTATION_SIZE_LIMIT) {
                                            fprintf(stderr, "Error near %s line %d the length of the replacement text is larger the limit %d\n", curfilename, err_lineno, REPRESENTATION_SIZE_LIMIT);
                                        } else if (addref(symbolname, yytext, 0)) {
                                            // addmacro(symbolname);
                                        }
                                        BEGIN(INITIAL);
                                        print("leave DEFINE_VAL state\n");
                                    }
<DEFINE_VAL>.|\n                    {   /* handle #define wiht empty input */
                                        if (addref(symbolname, "", 0)) {
                                            // addmacro(symbolname);
                                        }
                                        BEGIN(INITIAL);
                                        print("leave DEFINE_VAL state\n");
                                    }
<DEFINE_VAL><<EOF>>                 {
                                        BEGIN(INITIAL);
                                        if (!popfile())
                                            yyterminate();
                                    }


"#"[ \t]*"undef"[ \t]*              {   /* handle #undef  */
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
                                        fprintf(stderr, "Error, comment started in %s line %d is unclosed\n", curfilename, err_lineno); 
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
                                        print("end of buffer and beign INITIAL state\n"); 
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

\0          { fprintf(stderr, "Reach to end of string\n"); END; }
.	        { fprintf(stderr, "Error near %s line %d text '%s'\n\tunexpected characters; ignoring.\n", curfilename, yylineno, yytext); }

%%

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
        /* printf("cycle macro buf '%s' %d\n", cur->filename, strcmp(cur->filename, fn)); */
        if (strcmp(cur->name, ident) == 0) {
            fprintf(stderr, "Error near %s line %d\n", curfilename, yylineno);
            fprintf(stderr, "\t#define substitution cycle:\n");
            while (cur != macrobuflist) {
                fprintf(stderr, "\t%s macro contains %s\n", cur->name, cur->prev->name);
                cur = cur->prev;
            }
            fprintf(stderr, "\t%s macro contains %s\n", cur->name, ident);
            return 1;
        }
        cur = cur->next;
    }

    struct symbol *sp = lookup(ident);
    if (!sp || !sp->name || !sp->reflist || sp->reflist->filename != curfilename) {
        return 0;
    }

    print("newmacro() find symbol '%s' wiht val:'%s'\n", ident, sp->reflist->value);

    struct macrobuf *mb = (struct macrobuf*)malloc(sizeof(struct macrobuf)); /* allocate mb @ lexer.l#4 */
    if (!mb) { perror("malloc"); exit(1); }

    mb->name = sp->name; /* point to the same address, no need to free */
    mb->bs = yy_scan_string(sp->reflist->value);
    yy_switch_to_buffer(mb->bs);

    /* mb -> list */
    mb->next = macrobuflist;
    if (macrobuflist)
        macrobuflist->prev = mb;
    macrobuflist = mb;

    macrobuflistsize++;
    print("newmacro() buffer list size: %d\n", macrobuflistsize);
    return 1;
}

int popmacro() {
    struct macrobuf *mb = macrobuflist;
    if (!mb) {
        print("popmacro() current macro buf doesn't exist %s\n");
        yy_switch_to_buffer(filebuflist->bs);
        return 0;
    }
    print("popmacro() current macro name: %s\n", mb->name);

    /* clear current macro buffer */
    yy_delete_buffer(mb->bs);
    
    /* move to the next macro buffer */
    macrobuflist = mb->next;
    if (macrobuflist)
        macrobuflist->prev = 0;
    macrobuflistsize--;
    print("popmacro() buffer list size: %d\n", macrobuflistsize);

    free(mb);  /* free mb @ lexer.l#4 */

    if (!macrobuflist) {
        print("popmacro() no previous macro buf and current lineno: %d\n", yylineno);
        yy_switch_to_buffer(filebuflist->bs);
        return 0;
    }

    /* update current macro buffer */
    yy_switch_to_buffer(macrobuflist->bs);
    print("popmacro() macro buf '%s' with lineno %d\n", macrobuflist->name, yylineno);
    return 1;
};

int newfile(char *fn)
{
    print("newfile() %s\n", fn);

    /* limit buffer list size <= 256 */
    if (filebuflistsize >= BUFFER_LIST_SIZE_LIMIT) {
        fprintf(stderr, "Error reaching to file buffer list size limit %d\n", BUFFER_LIST_SIZE_LIMIT);
        return 0;
    }

    /* detect cycle */
    struct filebuf *cur = filebuflist;
    while (cur) {
        if (strcmp(cur->filename, fn) == 0) {
            fprintf(stderr, "Error near %s line %d\n", curfilename, err_lineno);
            fprintf(stderr, "\t#include cycle:\n");
            while (cur != filebuflist) {
                fprintf(stderr, "\tFile %s includes %s\n", cur->filename, cur->prev->filename);
                cur = cur->prev;
            }
            fprintf(stderr, "\tFile %s includes %s\n", cur->filename, fn);
            return 0;
        }
        cur = cur->next;
    }

    /* check the existance of the file */
    FILE *f = fopen(fn, "r");
    if (!f) { /* perror(fn); */ return 0; }

    struct filebuf *fb = (struct filebuf*)malloc(sizeof(struct filebuf));
    if (!fb) { perror("malloc"); exit(1); }

    /* remember state */ 
    if (filebuflist) {
        print("newfile() has previous file %s\n", curfilename);
        filebuflist->lineno = yylineno;
        filebuflist->iflist = iflist;
        filebuflist->iflistsize = iflistsize;
    } else {
        print("newfile() no previous file\n");
    }
    
    /* set up current entry */
    fb->bs = yy_create_buffer(f, YY_BUF_SIZE);
    fb->f = f;
    fb->filename = fn;
    yy_switch_to_buffer(fb->bs);

    /* fb -> list  */
    fb->next = filebuflist;
    if (filebuflist)
        filebuflist->prev = fb;
    filebuflist = fb;
    
    /* set up enviroment for the new file */
    yylineno = 1;
    err_lineno = 0;
    curfilename = fn;
    iflist = 0;
    iflistsize = 0;
    filebuflistsize++;
    print("newfile() buffer list size: %d\n", filebuflistsize);
    return 1;
}

int popfile(void)
{
    if (iflist) {
        fprintf(stderr, "Error near %s line %d unclosed %s\n", curfilename, iflist->lineno, iflist->isifdef ? "ifdef" : "ifndef");
        return 0;
    }

    if (macrobuflist) {
        popmacro();
        return 1;
    }

    struct filebuf *fb = filebuflist;
    if (!fb) {
        print("popfile() current file doesn't exist %s\n");
        return 0;
    }
    print("popfile() %s\n", curfilename);

    /* clear current file buffer */
    if (fclose(fb->f)) {
        fprintf(stderr, "Error cannot close file %s\n", curfilename);
    }
    yy_delete_buffer(fb->bs);

    /* move to next file buffer */
    filebuflist = fb->next;
    if (filebuflist)
        filebuflist->prev = 0;
    filebuflistsize--;
    print("popfile() filebuflistsize: %d, macrobuflistsize: %d, iflistsize: %d\n", filebuflistsize, macrobuflistsize, iflistsize);

    if (filebuflist) {
        print("filebuflist exists");
    }
    if (macrobuflist) {
        print("macrobuflist exists");
    }
    if (iflist) {
        print("iflist exists");
    }

    free(fb); /* free memory */
    fb = 0;
    
    if (!filebuflist) {
        print("popfile() no next file\n");
        return 0;
    }

    /* update the environment for the last file buffer */
    yy_switch_to_buffer(filebuflist->bs);
    yylineno = filebuflist->lineno;
    curfilename = filebuflist->filename;
    iflist  = filebuflist->iflist;
    iflistsize = filebuflist->iflistsize;
    print("popfile() current file '%s' with lineno %d\n", curfilename, yylineno);
    return 1;
}