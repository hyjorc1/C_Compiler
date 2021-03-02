
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

struct list *global_vars = NULL;
struct struct_list *global_structs = NULL;
struct func_list *global_funcs = NULL;
struct list *local_structs = NULL;
struct list *local_vars = NULL;

%}

%define api.prefix {m2}

%union {
    char *str;
    struct list *l;
    struct struct_node *sn;
    struct func_node *fn;
}

/* 3. A type name is‡ one of the simple types: void, char, int, float. */
%token <str> PRIMTYPE
%token CONST
%token STRUCT
%token FOR WHILE DO IF ELSE BREAK CONTINUE RETURN
%token <str> IDENT

%token <str> INTCONST REALCONST STRCONST CHARCONST
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

%type <str> var init_var para
%type <l> init_var_list var_decl noinit_var_decls noinit_var_decl var_ni_list para_list
%type <sn> struct_decl
%type <fn> func_proto func_def func_decl

%%

/* 1. A C program is‡ a sequence of zero or more (global) variable declarations, 
    function prototypes, and function definitions, appearing in any order. */
root : %empty                           {   dprint("empty root", "");   }
    | root var_decl                     { 
                                            dprint("global var_decl", "============== global var_decl  =============");
                                            global_vars = global_vars == NULL ? $2 : merge(global_vars, $2);
                                        }
    | root func_proto                   { 
                                            dprint("global func_proto", "============== global func_proto =============");
                                            if (global_funcs == NULL)
                                                global_funcs = new_func_list();
                                            add_last_func(global_funcs, $2);
                                        }
    | root func_def                     {   
                                            dprint("global func_def ", "============== global func_def =============");
                                            if (global_funcs == NULL)
                                                global_funcs = new_func_list();
                                            add_last_func(global_funcs, $2);
                                        }
    | root struct_decl                  { 
                                            dprint("global struct_decl ", "============== global struct_decl ============="); 
                                            if (global_structs == NULL)
                                                global_structs = new_struct_list();
                                            add_last_struct(global_structs, $2);
                                        }
    ;

/* 2. A variable declaration is‡ a type name, followed by a comma-separated list of 
    one or more identifiers, each identifier optionally followed by a left bracket, 
    an integer constant, and a right bracket. The list is terminated with a semicolon. 
    Note that this restricts arrays to a single dimension. */
var_decl : type init_var_list SEMI      { dprint("type init_var_list SEMI", ""); $$ = $2; }
    ;

/* 2.3 Extra credit: constants */
type : all_type                         { dprint("all_type", ""); }
    | CONST all_type                    { dprint("CONST all_type", ""); }
    | all_type CONST                    { dprint("all_type CONST", ""); }
    ;

all_type : PRIMTYPE                     { dprint("PRIMTYPE", $1); }
    | STRUCT IDENT                      { dprint("STRUCT IDENT", $2); }
    ;

init_var_list : init_var                { dprint("single init_var init_var_list", ""); $$ = new_init_list($1); }
    | init_var_list COMMA init_var      { dprint("init_var_list COMMA init_var", ","); add_last($1, $3); $$ = $1; }
    ;

/* 2.2 Extra credit: variable initialization */
init_var : var                          { dprint("init_var var", ""); $$ = $1; }
    | var ASSIGN exp                    { dprint("var ASSIGN exp", "="); $$ = $1; }
    ;

var : IDENT                             { dprint("IDENT", $1); $$ = $1; }
    | IDENT LBRACKET INTCONST RBRACKET  { dprint("IDENT [int]", $1); $$ = concat($1, "[]"); }
    ;

/* 2.4 Extra credit: user-defined structs 
    A user-defined type declaration is† the keyword struct, followed by an 
    identifier, a left brace, zero or more variable declarations (without 
    initializations), a right brace, and a semicolon. */
struct_decl : STRUCT IDENT LBRACE noinit_var_decls RBRACE SEMI  { dprint("STRUCT DECL", $2); $$ = new_struct($2, $4); }
    ;

noinit_var_decls : noinit_var_decl      { dprint("single noinit_var_decl", ""); $$ = $1; }
    | noinit_var_decls noinit_var_decl  { dprint("noinit_var_decls noinit_var_decl", ""); $$ = merge($1, $2); }
    ;

noinit_var_decl : type var_ni_list SEMI { dprint("type var_ni_list SEMI", ""); $$ = $2; }
    ;

var_ni_list : var                       { dprint("var_ni_list var", ""); $$ = new_init_list($1); }
    | var_ni_list COMMA var             { dprint("var_ni_list COMMA var", ","); add_last($1, $3); $$ = $1; }
    ;

/* 4. A function prototype is a function declaration followed by a semicolon. */
func_proto : func_decl SEMI             { dprint("func_proto SEMI", ""); $1->is_proto = 1; $$ = $1; }
    ;

/* 5. A function declaration is a type name (the return type of the function), 
    followed by an identifier (the name of the function), a left parenthesis, 
    an optional comma-separated list of formal parameters, and a right parenthesis. */
func_decl : type IDENT LPAR para_list RPAR  { dprint("func_decl", $2); $$ = new_func($2, $4, NULL, NULL, 0);}
    ;

para_list : %empty                      { dprint("empty para_list", ""); $$ = NULL; }
    | para                              { dprint("single para para_list", ""); $$ = new_init_list($1); }
    | para_list COMMA para              { dprint("para_list COMMA para", ","); add_last($1, $3); $$ = $1; }
    ;

/* 6. A formal parameter is† a type name, followed by an identifier, and optionally 
    followed by a left and right bracket. */
para : type IDENT                       { dprint("type IDENT", $2); $$ = $2; }
    | type IDENT LBRACKET RBRACKET      { dprint("type IDENT []", $2); $$ = concat($2, "[]"); }
    ;

/* 7. A function definition is‡ a function declaration followed by a left brace, 
    a sequence of zero or more variable declarations, a sequence of zero or more 
    statements, and a right brace. Note that this definition requires all variable 
    declarations to appear before statements. */
func_def : func_decl LBRACE func_local_decls stmt_list RBRACE   {
                                                                    dprint("func_decl RBRACE func_body LBRACE", ""); 
                                                                    $1->is_proto = 0;
                                                                    $1->local_vars = local_vars;
                                                                    $1->local_structs = local_structs; 
                                                                    $$ = $1;
                                                                    local_vars = NULL;
                                                                    local_structs = NULL;
                                                                }
    ;

func_local_decls : func_local_decls local_decl
    | local_decl
    ;

local_decl : var_decl                   {
                                            dprint("local var_decl", "============== local var_decl =============");
                                            local_vars = local_vars == NULL ? $1 : merge(local_vars, $1);
                                        }
    | struct_decl                       { 
                                            dprint("local struct_decl", "============== local struct_decl =============");
                                            if  (local_structs == NULL)
                                                local_structs = new_list();
                                            add_last(local_structs, strdup($1->name));
                                            free($1->name);
                                            destroy_list($1->members);
                                            free($1);
                                        }
    ;


/* 8. A statement block is a left brace, a sequence of zero or more statements, and a right brace. */
block_stmt : LBRACE stmt_list RBRACE    { dprint("LBRACE stmt_list RBRACE", ""); };

stmt_list : %empty                      { dprint("empty stmt_list", ""); }
    | stmt_list stmt                    { dprint("stmt_list stmt", ""); }
    | stmt                              { dprint("stmt", ""); }
    ;

/* 9. statement */
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

for_stmt : FOR LPAR exp_b SEMI exp_b SEMI exp_b RPAR block_stmt   { dprint("FOR block_stmt", ""); }
    | FOR LPAR exp_b SEMI exp_b SEMI exp_b RPAR stmt              { dprint("FOR stmt", ""); }
    ;

exp_b : %empty                          { dprint("false exp_b", ""); }
    | exp                               { dprint("true exp_b", ""); }
    ;

while_stmt : WHILE LPAR exp RPAR block_stmt   { dprint("WHILE block_stmt", ""); }
    | WHILE LPAR exp RPAR stmt                { dprint("WHILE stmt", ""); }
    ;

do_stmt : DO block_stmt WHILE LPAR exp RPAR SEMI    { dprint("DO block_stmt WIHILE", ""); }
    | DO stmt WHILE LPAR exp RPAR SEMI              { dprint("DO stmt WIHILE", ""); }
    ;

/* 10. expression */
exp : INTCONST                          { dprint("INTCONST", $1); }
    | REALCONST                         { dprint("REALCONST", $1); }
    | STRCONST                          { dprint("STRCONST", $1); }
    | CHARCONST                         { dprint("CHARCONST", $1); }
    | IDENT LPAR exp_list RPAR          { dprint("IDENT LPAR exp_list RPAR", $1); }

    /* 11. An l-value is‡ an identifier, optionally followed by a left bracket, 
        an expression, and a right bracket. Note that this restricts array 
        access to a single dimension. */
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

    /* 12. Unary operators (for any expression) are: -, !, ~ */
    | BANG exp %prec UBANG              { dprint("UBANG", "!"); }
    | TILDE exp %prec UTILDE            { dprint("UTILDE", "~"); }
    | MINUS exp %prec UMINUS            { dprint("UMINUS", "-"); }

    /* 13. Binary operators are: ==, !=, >, >=, <, <=, +, -, *, /, %, |, &, ||, && */
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

    /* 14. Assignment operators are: =, +=, -=, *=, /= */
    | exp QUEST exp COLON exp           { dprint("exp QUEST exp COLON exp", ""); }
    | LPAR type RPAR exp                { dprint("LPAR type RPAR exp", ""); }
    | LPAR exp RPAR                     { dprint("LPAR exp RPAR", ""); }
    ;

exp_list : %empty                       { dprint("empty exp_list", ""); }
    | exp_list COMMA exp                { dprint("multiple exps exp_list", ""); }
    | exp                               { dprint("single exp exp_list", ""); }
    ; 

/* 2.5 Extra credit: struct member selection */
l_val : l_value                         { dprint("single l_value", ""); }
    | l_val DOT l_value                 { dprint("l_val DOT l_value", "."); }
    ;

l_value : IDENT                         { dprint("IDENT", $1); }
    | IDENT LBRACKET exp RBRACKET       { dprint("IDENT [exp]", $1); }
    ;

%%


