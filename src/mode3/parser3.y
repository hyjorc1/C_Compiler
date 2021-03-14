
%{

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "m3global.h" 


void m3error(const char* mesg) {
    fprintf(stderr, "Error near %s line %d text '%s'\n\t%s\n", m3_cur_file_name, m3lineno, m3text, mesg);
}

void m3dprint(const char* s1, const char* s2) {
    if (debug) {
        fprintf(stdout, "line %d at text '%s' as '%s' => '%s'\n", m3lineno, m3text, s1, s2);
    }
}

char *m3_cur_file_name;

struct list *m3_global_vars = NULL;
struct struct_list *m3_global_structs = NULL;
struct func_list *m3_global_funcs = NULL;

int m3_is_global = 1;

struct list *m3_local_structs = NULL;
struct list *m3_local_vars = NULL;

%}

%define api.prefix {m3}

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
%type <l> init_var_list var_decl struct_body_decls struct_body_decl noinit_var_decl var_ni_list para_list
%type <sn> struct_decl
%type <fn> func_proto func_def func_decl

%%

/* 1. A C program is‡ a sequence of zero or more (global) variable declarations, 
    function prototypes, and function definitions, appearing in any order. */
root : %empty                           {   m3dprint("empty root", "");   }
    | root var_decl                     { 
                                            m3dprint("global var_decl", "============== global var_decl  =============");
                                            m3_global_vars = m3_global_vars == NULL ? $2 : merge(m3_global_vars, $2);
                                        }
    | root func_proto                   { 
                                            m3dprint("global func_proto", "============== global func_proto =============");
                                            if (m3_global_funcs == NULL)
                                                m3_global_funcs = new_func_list();
                                            add_last_func(m3_global_funcs, $2);
                                        }
    | root func_def                     {   
                                            m3dprint("global func_def ", "============== global func_def =============");
                                            if (m3_global_funcs == NULL)
                                                m3_global_funcs = new_func_list();
                                            add_last_func(m3_global_funcs, $2);
                                        }
    | root struct_decl                  { 
                                            // m3dprint("global struct decl ", "============== global struct decl ============="); 
                                            // if (m3_global_structs == NULL)
                                            //     m3_global_structs = new_struct_list();
                                            // add_last_struct(m3_global_structs, $2);
                                        }
    ;

/* 2. A variable declaration is‡ a type name, followed by a comma-separated list of 
    one or more identifiers, each identifier optionally followed by a left bracket, 
    an integer constant, and a right bracket. The list is terminated with a semicolon. 
    Note that this restricts arrays to a single dimension. */
var_decl : type init_var_list SEMI      { m3dprint("type init_var_list SEMI", ""); $$ = $2; }
    ;

/* 2.3 Extra credit: constants */
type : all_type                         { m3dprint("all_type", ""); }
    | CONST all_type                    { m3dprint("CONST all_type", ""); }
    | all_type CONST                    { m3dprint("all_type CONST", ""); }
    ;

all_type : PRIMTYPE                     { m3dprint("PRIMTYPE", $1); }
    | STRUCT IDENT                      { m3dprint("STRUCT IDENT", $2); }
    ;

init_var_list : init_var                { m3dprint("single init_var init_var_list", ""); $$ = new_init_list($1); }
    | init_var_list COMMA init_var      { m3dprint("init_var_list COMMA init_var", ","); add_last($1, $3); $$ = $1; }
    ;

/* 2.2 Extra credit: variable initialization */
init_var : var                          { m3dprint("init_var var", ""); $$ = $1; }
    | var ASSIGN exp                    { m3dprint("var ASSIGN exp", "="); $$ = $1; }
    ;

var : IDENT                             { m3dprint("IDENT", $1); $$ = $1; }
    | IDENT LBRACKET INTCONST RBRACKET  { m3dprint("IDENT [int]", $1); $$ = concat($1, "[]"); }
    ;

/* 2.4 Extra credit: user-defined structs 
    A user-defined type declaration is† the keyword struct, followed by an 
    identifier, a left brace, zero or more variable declarations (without 
    initializations), a right brace, and a semicolon. */
struct_decl : STRUCT IDENT LBRACE struct_body_decls RBRACE SEMI 
                                        {
                                            m3dprint("STRUCT { struct_body_decls }", $2);
                                            if (m3_is_global) {
                                                m3dprint("global struct decl ", "============== global struct decl =============");
                                                if (m3_global_structs == NULL)
                                                    m3_global_structs = new_struct_list();
                                                add_last_struct(m3_global_structs, new_struct($2, $4));
                                            } else {
                                                m3dprint("local struct decl", "============== local struct decl =============");
                                                if  (m3_local_structs == NULL)
                                                    m3_local_structs = new_list();
                                                add_first(m3_local_structs, strdup($2));
                                                free($2);
                                                destroy_list($4);
                                            }
                                        }
    ;

struct_body_decls : %empty              { m3dprint("empty struct body decls", ""); $$ = NULL; }
    | struct_body_decl                  { m3dprint("sinlge struct body decl", ""); $$ = $1; }
    | struct_body_decls struct_body_decl{ m3dprint("multiple struct body decl", ""); $$ = merge($1, $2); }
    ;

struct_body_decl : noinit_var_decl      { m3dprint("noinit var decl", ""); $$ = $1; }
    | struct_decl                       { m3dprint("nested struct decl", ""); $$ = NULL; }
    ;

noinit_var_decl : type var_ni_list SEMI { m3dprint("type var_ni_list SEMI", ""); $$ = $2; }
    ;

var_ni_list : var                       { m3dprint("var_ni_list var", ""); $$ = new_init_list($1); }
    | var_ni_list COMMA var             { m3dprint("var_ni_list COMMA var", ","); add_last($1, $3); $$ = $1; }
    ;

/* 4. A function prototype is a function declaration followed by a semicolon. */
func_proto : func_decl SEMI             { m3dprint("func_proto SEMI", ""); $1->is_proto = 1; $$ = $1; m3_is_global = 1; }
    ;

/* 5. A function declaration is a type name (the return type of the function), 
    followed by an identifier (the name of the function), a left parenthesis, 
    an optional comma-separated list of formal parameters, and a right parenthesis. */
func_decl : type IDENT LPAR para_list RPAR  { m3dprint("func_decl", $2); $$ = new_func($2, $4, NULL, NULL, 0); m3_is_global = 0; }
    | type IDENT LPAR RPAR                  { m3dprint("sempty para list", ""); $$ = new_func($2, NULL, NULL, NULL, 0); m3_is_global = 0; }
    ;

para_list : para_list COMMA para        { m3dprint("multiple para list", ","); add_last($1, $3); $$ = $1; }
    | para                              { m3dprint("single para list", ""); $$ = new_init_list($1); }
    ;

/* 6. A formal parameter is† a type name, followed by an identifier, and optionally 
    followed by a left and right bracket. */
para : type IDENT                       { m3dprint("type IDENT", $2); $$ = $2; }
    | type IDENT LBRACKET RBRACKET      { m3dprint("type IDENT []", $2); $$ = concat($2, "[]"); }
    ;

/* 7. A function definition is‡ a function declaration followed by a left brace, 
    a sequence of zero or more variable declarations, a sequence of zero or more 
    statements, and a right brace. Note that this definition requires all variable 
    declarations to appear before statements. */
func_def : func_decl LBRACE func_local_decls stmt_list RBRACE   {
                                                                    m3dprint("func_decl RBRACE func_body LBRACE", ""); 
                                                                    $1->is_proto = 0;
                                                                    $1->local_vars = m3_local_vars;
                                                                    $1->local_structs = m3_local_structs; 
                                                                    $$ = $1;
                                                                    m3_local_vars = NULL;
                                                                    m3_local_structs = NULL;
                                                                    m3_is_global = 1;
                                                                }
    ;

func_local_decls : %empty               { m3dprint("empty func_local_decls", ""); }
    | func_local_decls local_decl       { m3dprint("multiple local_decl", ""); }
    | local_decl                        { m3dprint("single local_decl", ""); }
    ;

local_decl : var_decl                   {
                                            m3dprint("local var decl", "============== local var decl =============");
                                            m3_local_vars = m3_local_vars == NULL ? $1 : merge(m3_local_vars, $1);
                                        }
    | struct_decl                       { 
                                            // m3dprint("local struct decl", "============== local struct decl =============");
                                            // if  (m3_local_structs == NULL)
                                            //     m3_local_structs = new_list();
                                            // add_last(m3_local_structs, strdup($1->name));
                                            // free($1->name);
                                            // destroy_list($1->members);
                                            // free($1);
                                        }
    ;

/* 8. A statement block is a left brace, a sequence of zero or more statements, and a right brace. */
block_stmt : LBRACE stmt_list RBRACE    { m3dprint("{ stmt list }", ""); };

stmt_list : %empty                      { m3dprint("empty stmt list", ""); }
    | stmt_list stmt                    { m3dprint("stmt_list stmt", ""); }
    | stmt                              { m3dprint("stmt", ""); }
    ;

/* 9. statement */
stmt : SEMI                             { m3dprint("SEMI", ""); }
    | exp SEMI                          { m3dprint("exp SEMI", ""); }
    | BREAK SEMI                        { m3dprint("BREAK SEMI", ""); }
    | CONTINUE SEMI                     { m3dprint("CONTINUE SEMI", ""); }
    | return_stmt                       { m3dprint("return_stmt", ""); }
    | if_stmt                           { m3dprint("if_stmt", ""); }
    | for_stmt                          { m3dprint("for_stmt", ""); }
    | while_stmt                        { m3dprint("while_stmt", ""); }
    | do_stmt                           { m3dprint("do_stmt", ""); }
    ;

return_stmt : RETURN SEMI               { m3dprint("RETURN SEMI", ""); }
    | RETURN exp SEMI                   { m3dprint("RETURN exp SEMI", ""); }
    ;

if_stmt : IF LPAR exp RPAR block_stmt %prec WITHOUT_ELSE    { m3dprint("IF block_stmt", ""); };
    | IF LPAR exp RPAR block_stmt ELSE block_stmt           { m3dprint("IF block_stmt ELSE block_stmt", ""); };
    | IF LPAR exp RPAR block_stmt ELSE stmt                 { m3dprint("IF block_stmt ELSE stmt", ""); };
    
    | IF LPAR exp RPAR stmt %prec WITHOUT_ELSE              { m3dprint("IF stmt", ""); };
    | IF LPAR exp RPAR stmt ELSE block_stmt                 { m3dprint("IF stmt ELSE block_stmt", ""); };
    | IF LPAR exp RPAR stmt ELSE stmt                       { m3dprint("IF stmt ELSE stmt", ""); };
    ;

for_stmt : FOR LPAR exp_b SEMI exp_b SEMI exp_b RPAR block_stmt   { m3dprint("FOR block_stmt", ""); }
    | FOR LPAR exp_b SEMI exp_b SEMI exp_b RPAR stmt              { m3dprint("FOR stmt", ""); }
    ;

exp_b : %empty                          { m3dprint("false exp_b", ""); }
    | exp                               { m3dprint("true exp_b", ""); }
    ;

while_stmt : WHILE LPAR exp RPAR block_stmt   { m3dprint("WHILE block_stmt", ""); }
    | WHILE LPAR exp RPAR stmt                { m3dprint("WHILE stmt", ""); }
    ;

do_stmt : DO block_stmt WHILE LPAR exp RPAR SEMI    { m3dprint("DO block_stmt WIHILE", ""); }
    | DO stmt WHILE LPAR exp RPAR SEMI              { m3dprint("DO stmt WIHILE", ""); }
    ;

/* 10. expression */
exp : INTCONST                          { m3dprint("INTCONST", $1); }
    | REALCONST                         { m3dprint("REALCONST", $1); }
    | STRCONST                          { m3dprint("STRCONST", $1); }
    | CHARCONST                         { m3dprint("CHARCONST", $1); }
    | IDENT LPAR exp_list RPAR          { m3dprint("IDENT(exp_list)", $1); }
    | IDENT LPAR RPAR                   { m3dprint("IDENT()", $1); }

    /* 11. An l-value is‡ an identifier, optionally followed by a left bracket, 
        an expression, and a right bracket. Note that this restricts array 
        access to a single dimension. */
    | l_val                             { m3dprint("l_val", ""); }
    | l_val ASSIGN exp                  { m3dprint("l_val ASSIGN exp", "="); }
    | l_val PLUSASSIGN exp              { m3dprint("l_val PLUSASSIGN exp", "+="); }
    | l_val MINUSASSIGN exp             { m3dprint("l_val MINUSASSIGN exp", "-="); }
    | l_val STARASSIGN exp              { m3dprint("l_val STARASSIGN exp", "*="); }
    | l_val SLASHASSIGN exp             { m3dprint("l_val SLASHASSIGN exp", "/="); }
    | l_val INCR %prec UINCR            { m3dprint("l_val INCR", "++"); }
    | INCR l_val %prec UINCR            { m3dprint("INCR l_val", "++"); }
    | l_val DECR %prec UDECR            { m3dprint("l_val DECR", "--"); }
    | DECR l_val %prec UDECR            { m3dprint("DECR l_val", "--"); }

    /* 12. Unary operators (for any expression) are: -, !, ~ */
    | BANG exp %prec UBANG              { m3dprint("UBANG", "!"); }
    | TILDE exp %prec UTILDE            { m3dprint("UTILDE", "~"); }
    | MINUS exp %prec UMINUS            { m3dprint("UMINUS", "-"); }

    /* 13. Binary operators are: ==, !=, >, >=, <, <=, +, -, *, /, %, |, &, ||, && */
    | exp EQUALS exp                    { m3dprint("EQUALS", "=="); }
    | exp NEQUAL exp                    { m3dprint("NEQUAL", "!="); }
    | exp GT exp                        { m3dprint("GT", ""); }
    | exp GE exp                        { m3dprint("GE", ""); }
    | exp LT exp                        { m3dprint("LT", ""); }
    | exp LE exp                        { m3dprint("LE", ""); }
    | exp PLUS exp                      { m3dprint("PLUS", "+"); }
    | exp MINUS exp                     { m3dprint("MINUS", "-"); }
    | exp STAR exp                      { m3dprint("STAR", "*"); }
    | exp SLASH exp                     { m3dprint("SLASH", "/"); }
    | exp MOD exp                       { m3dprint("MOD", ""); }
    | exp PIPE exp                      { m3dprint("PIPE", ""); }
    | exp AMP exp                       { m3dprint("AMP", ""); }
    | exp DPIPE exp                     { m3dprint("DPIPE", ""); }
    | exp DAMP exp                      { m3dprint("DAMP", ""); }

    /* 14. Assignment operators are: =, +=, -=, *=, /= */
    | exp QUEST exp COLON exp           { m3dprint("exp QUEST exp COLON exp", ""); }
    | LPAR type RPAR exp                { m3dprint("LPAR type RPAR exp", ""); }
    | LPAR exp RPAR                     { m3dprint("LPAR exp RPAR", ""); }
    ;

exp_list : exp                          { m3dprint("single exp exp_list", ""); }
    | exp_list COMMA exp                { m3dprint("multiple exps exp_list", ""); }
    ; 

/* 2.5 Extra credit: struct member selection */
l_val : l_member                         { m3dprint("single l_member", ""); }
    | l_val DOT l_member                 { m3dprint("l_val DOT l_member", "."); }
    ;

l_member : IDENT                         { m3dprint("IDENT", $1); }
    | IDENT dimen                       { m3dprint("IDENT dimen", $1); }
    ;

dimen : LBRACKET exp RBRACKET            { m3dprint("[ exp ]", ""); }
    | dimen LBRACKET exp RBRACKET        { m3dprint("dimen [ exp ]", ""); }
    ;

%%


