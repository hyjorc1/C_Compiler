
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

%token UN_OP BIN_OP ASSN_OP

%token INCREMENT DECREMENT

%nonassoc WITHOUT_ELSE 
%nonassoc ELSE

%left PLUS MINUS
%left STAR SLASH
%nonassoc UMINUS

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
    ;

if_stmt : IF LPAR exp RPAR block_stmt %prec WITHOUT_ELSE    { dprint("IF block_stmt", ""); };
    | IF LPAR exp RPAR block_stmt ELSE block_stmt           { dprint("IF block_stmt ELSE block_stmt", ""); };
    | IF LPAR exp RPAR block_stmt ELSE stmt                 { dprint("IF block_stmt ELSE stmt", ""); };
    
    | IF LPAR exp RPAR stmt %prec WITHOUT_ELSE              { dprint("IF stmt", ""); };
    | IF LPAR exp RPAR stmt ELSE block_stmt                 { dprint("IF stmt ELSE block_stmt", ""); };
    | IF LPAR exp RPAR stmt ELSE stmt                       { dprint("IF stmt ELSE stmt", ""); };
    ;

return_stmt : RETURN SEMI               { dprint("RETURN SEMI", ""); }
    | RETURN exp SEMI                   { dprint("RETURN exp SEMI", ""); }
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
    | l_val_exp                         { dprint("l_val_exp", ""); }
    | UN_OP exp                         { dprint("UN_OP", ""); }
    | exp BIN_OP exp                    { dprint("exp BIN_OP exp", ""); }
    | exp QUEST exp COLON exp           { dprint("exp QUEST exp COLON exp", ""); }
    | LPAR TYPE RPAR exp                { dprint("LPAR TYPE RPAR exp", ""); }
    | LPAR exp RPAR                     { dprint("LPAR exp RPAR", ""); }
    ;

l_val_exp : l_val                       { dprint("l_val", ""); }
    | l_val ASSN_OP exp                 { dprint("l_val ASSN_OP exp", ""); }
    | l_val INCREMENT                   { dprint("l_val INCREMENT", ""); }
    | INCREMENT l_val                   { dprint("INCREMENT l_val", ""); }
    | l_val DECREMENT                   { dprint("l_val DECREMENT", ""); }
    | DECREMENT l_val                   { dprint("DECREMENT l_val", ""); }
    ;

l_val : IDENT                           { dprint("IDENT", $1); }
    | IDENT LBRACKET exp RBRACKET       { dprint("IDENT LBRACKET exp RBRACKET", $1); }
    ;

%%


