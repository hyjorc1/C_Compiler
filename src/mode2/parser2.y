
%{

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "m2global.h" 

void m2error(const char* mesg) {
    fprintf(stderr, "Dude, there was a problem on line %d at text '%s':\n\t%s\n", m2lineno, m2text, mesg);
}

void dprint(const char* s1, const char* s2) {
    if (debug) {
        fprintf(stdout, "line %d at text '%s' as '%s' => '%s'\n", m2lineno, m2text, s1, s2);
    }
}

%}

%define api.prefix {m2}


%union {
  char *str;
}

%token TYPE
%token CONST
%token STRUCT
%token FOR WHILE DO IF ELSE BREAK CONTINUE RETURN
%token <str> IDENT

%token INTCONST REALCONST STRCONST CHARCONST
%token LPAR RPAR LBRACKET RBRACKET LBRACE RBRACE
%token DOT COMMA SEMI QUEST COLON
%token PLUS MINUS STAR SLASH MOD TILDE
%token PIPE AMP BANG DPIPE DAMP
%token ASSIGN PLUSASSIGN MINUSASSIGN STARASSIGN SLASHASSIGN INCR DECR
%token EQUALS NEQUAL GT GE LT LE

%nonassoc WITHOUT_ELSE 
%nonassoc ELSE

%left   COMMA
%right  ASSIGN PLUSASSIGN MINUSASSIGN STARASSIGN SLASHASSIGN
%right  QUEST COLON
%left   DPIPE
%left   DAMP
%left   PIPE
%left   AMP
%left   EQUALS NEQUAL
%left   LT LE GT GE
%left   PLUS MINUS
%left   STAR SLASH MOD
%left   LPAR RPAR LBRACKET RBRACKET DOT

%nonassoc UMINUS UBANG UTILDE UINCR UDECR

%%

block_stmt : LBRACE stmt_list RBRACE    { dprint("LBRACE stmt_list RBRACE", ""); };

stmt_list : %empty                      { dprint("empty stmt_list", ""); }
    | stmt_list stmt                    { dprint("stmt_list stmt", ""); }
    | stmt                              { dprint("stmt", ""); }
    ;

stmt : SEMI                             { dprint("SEMI", ""); }
    | exp SEMI                          { dprint("exp SEMI", ""); }
    | BREAK SEMI                        { dprint("BREAK SEMI", ""); }
    | CONTINUE SEMI                     { dprint("CONTINUE SEMI", ""); }
    | return_stmt                       { dprint("return_stmt", ""); }
    | if_stmt                           { dprint("if_stmt", ""); }
    | for_stmt                          { dprint("for_stmt", ""); }
    | while_stmt                        { dprint("while_stmt", ""); }
    | do_stmt                           { dprint("do_stmt", ""); }
    ;

return_stmt : RETURN SEMI               { dprint("RETURN SEMI", ""); }
    | RETURN exp SEMI                   { dprint("RETURN exp SEMI", ""); }
    ;

if_stmt : IF LPAR exp RPAR block_stmt %prec WITHOUT_ELSE    { dprint("IF block_stmt", ""); };
    | IF LPAR exp RPAR block_stmt ELSE block_stmt           { dprint("IF block_stmt ELSE block_stmt", ""); };
    | IF LPAR exp RPAR block_stmt ELSE stmt                 { dprint("IF block_stmt ELSE stmt", ""); };
    
    | IF LPAR exp RPAR stmt %prec WITHOUT_ELSE              { dprint("IF stmt", ""); };
    | IF LPAR exp RPAR stmt ELSE block_stmt                 { dprint("IF stmt ELSE block_stmt", ""); };
    | IF LPAR exp RPAR stmt ELSE stmt                       { dprint("IF stmt ELSE stmt", ""); };
    ;

for_stmt : FOR LPAR exp_b SEMI exp_b SEMI exp_b SEMI RPAR block_stmt   { dprint("FOR block_stmt", ""); }
    | FOR LPAR exp_b SEMI exp_b SEMI exp_b SEMI RPAR stmt              { dprint("FOR stmt", ""); }
    ;

while_stmt : WHILE LPAR exp RPAR block_stmt   { dprint("WHILE block_stmt", ""); }
    | WHILE LPAR exp RPAR stmt                { dprint("WHILE stmt", ""); }
    ;

do_stmt : DO block_stmt WHILE LPAR exp RPAR SEMI    { dprint("DO block_stmt WIHILE", ""); }
    | DO stmt WHILE LPAR exp RPAR SEMI        { dprint("DO stmt WIHILE", ""); }
    ;

exp_b : %empty                          { dprint("false exp_b", ""); }
    | exp                               { dprint("true exp_b", ""); }
    ;

exp_list : %empty                       { dprint("empty exp_list", ""); }
    | exp_list COMMA exp                { dprint("multiple exps exp_list", ""); }
    | exp                               { dprint("single exp exp_list", ""); }
    ; 

exp : INTCONST                          { dprint("INTCONST", ""); }
    | REALCONST                         { dprint("REALCONST", ""); }
    | STRCONST                          { dprint("STRCONST", ""); }
    | CHARCONST                         { dprint("CHARCONST", ""); }
    | IDENT LPAR exp_list RPAR          { dprint("IDENT LPAR exp_list RPAR", $1); }

    | l_val                             { dprint("l_val", ""); }
    | l_val ASSIGN exp                  { dprint("l_val ASSIGN exp", "="); }
    | l_val PLUSASSIGN exp              { dprint("l_val PLUSASSIGN exp", "+="); }
    | l_val MINUSASSIGN exp             { dprint("l_val MINUSASSIGN exp", "-="); }
    | l_val STARASSIGN exp              { dprint("l_val STARASSIGN exp", "*="); }
    | l_val SLASHASSIGN exp             { dprint("l_val SLASHASSIGN exp", "/="); }
    | l_val INCR %prec UINCR            { dprint("l_val INCR", "++"); }
    | INCR l_val %prec UINCR            { dprint("INCR l_val", "++"); }
    | l_val DECR %prec UDECR            { dprint("l_val DECR", "--"); }
    | DECR l_val %prec UDECR            { dprint("DECR l_val", "--"); }

    | BANG exp %prec UBANG              { dprint("UBANG", "!"); }
    | TILDE exp %prec UTILDE            { dprint("UTILDE", "~"); }
    | MINUS exp %prec UMINUS            { dprint("UMINUS", "-"); }

    | exp EQUALS exp                    { dprint("EQUALS", "=="); }
    | exp NEQUAL exp                    { dprint("NEQUAL", "!="); }
    | exp GT exp                        { dprint("GT", ""); }
    | exp GE exp                        { dprint("GE", ""); }
    | exp LT exp                        { dprint("LT", ""); }
    | exp LE exp                        { dprint("LE", ""); }
    | exp PLUS exp                      { dprint("PLUS", "+"); }
    | exp MINUS exp                     { dprint("MINUS", "-"); }
    | exp STAR exp                      { dprint("STAR", "*"); }
    | exp SLASH exp                     { dprint("SLASH", "/"); }
    | exp MOD exp                       { dprint("MOD", ""); }
    | exp PIPE exp                      { dprint("PIPE", ""); }
    | exp AMP exp                       { dprint("AMP", ""); }
    | exp DPIPE exp                     { dprint("DPIPE", ""); }
    | exp DAMP exp                      { dprint("DAMP", ""); }

    | exp QUEST exp COLON exp           { dprint("exp QUEST exp COLON exp", ""); }
    | LPAR TYPE RPAR exp                { dprint("LPAR TYPE RPAR exp", ""); }
    | LPAR exp RPAR                     { dprint("LPAR exp RPAR", ""); }
    ;


l_val : IDENT                           { dprint("IDENT", $1); }
    | IDENT LBRACKET exp RBRACKET       { dprint("IDENT LBRACKET exp RBRACKET", $1); }
    ;

%%


