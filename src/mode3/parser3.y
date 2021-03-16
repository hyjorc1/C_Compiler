
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

/* part 2 - 3. A type name is one of the simple types: void, char, int, float. */
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

/* part 3 - exp returns type */
%type <str> exp

%%

/* part 2 - 1. A C program is a sequence of zero or more (global) variable declarations, 
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
    | root struct_decl                  { m3dprint("root struct_decl", ""); }
    ;

/* part 2 - 2. A variable declaration is a type name, followed by a comma-separated list of 
    one or more identifiers, each identifier optionally followed by a left bracket, 
    an integer constant, and a right bracket. The list is terminated with a semicolon. 
    Note that this restricts arrays to a single dimension. */
var_decl : type init_var_list SEMI      { m3dprint("type init var list SEMI", ""); $$ = $2; }
    ;

/* part 2 - 2.3 and part 3 - 2.6 Extra credit: constants */
type : all_type                         { m3dprint("all_type", ""); }
    | CONST all_type                    { m3dprint("CONST all_type", ""); }
    | all_type CONST                    { m3dprint("all_type CONST", ""); }
    ;

all_type : PRIMTYPE                     { m3dprint("PRIMTYPE", $1); }
    | STRUCT IDENT                      { m3dprint("STRUCT IDENT", $2); }
    ;

init_var_list : init_var                { m3dprint("single init var init var list", ""); $$ = new_init_list($1); }
    | init_var_list COMMA init_var      { m3dprint("init var list COMMA init_var", ","); add_last($1, $3); $$ = $1; }
    ;

/* part 2 - 2.2 and part 3 - 2.5 Extra credit: variable initialization */
init_var : var                          { m3dprint("init_var var", ""); $$ = $1; }
    | var ASSIGN exp                    { m3dprint("var = exp", "="); $$ = $1; }
    ;

var : IDENT                             { m3dprint("IDENT", $1); $$ = $1; }
    | IDENT LBRACKET INTCONST RBRACKET  { m3dprint("IDENT [int]", $1); $$ = concat($1, "[]"); }
    ;

/* part 2 - 2.4 Extra credit: user-defined structs 
    A user-defined type declaration is† the keyword struct, followed by an 
    identifier, a left brace, zero or more variable declarations (without 
    initializations), a right brace, and a semicolon. */
/* part 3 - 2.7 Extra credit: user-defined structs */
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
                                                add_last(m3_local_structs, strdup($2));
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

/* part 2 - 4. A function prototype is a function declaration followed by a semicolon. */
func_proto : func_decl SEMI             { m3dprint("func_proto SEMI", ""); $1->is_proto = 1; $$ = $1; m3_is_global = 1; }
    ;

/* part 2 - 5. A function declaration is a type name (the return type of the function), 
    followed by an identifier (the name of the function), a left parenthesis, 
    an optional comma-separated list of formal parameters, and a right parenthesis. */
func_decl : type IDENT LPAR para_list RPAR  { m3dprint("func_decl", $2); $$ = new_func($2, $4, NULL, NULL, 0); m3_is_global = 0; }
    | type IDENT LPAR RPAR                  { m3dprint("sempty para list", ""); $$ = new_func($2, NULL, NULL, NULL, 0); m3_is_global = 0; }
    ;

para_list : para_list COMMA para        { m3dprint("multiple para list", ","); add_last($1, $3); $$ = $1; }
    | para                              { m3dprint("single para list", ""); $$ = new_init_list($1); }
    ;

/* part 2 - 6. A formal parameter is† a type name, followed by an identifier, and optionally 
    followed by a left and right bracket. */
para : type IDENT                       { m3dprint("type IDENT", $2); $$ = $2; }
    | type IDENT LBRACKET RBRACKET      { m3dprint("type IDENT []", $2); $$ = concat($2, "[]"); }
    ;

/* part 2 - 7. A function definition is a function declaration followed by a left brace, 
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
    | struct_decl                       { m3dprint("local_decl struct_decl", ""); }
    ;

/* part 2 - 8. A statement block is a left brace, a sequence of zero or more statements, and a right brace. */
block_stmt : LBRACE stmt_list RBRACE    { m3dprint("{ stmt list }", ""); };

stmt_list : %empty                      { m3dprint("empty stmt list", ""); }
    | stmt_list stmt                    { m3dprint("stmt_list stmt", ""); }
    | stmt                              { m3dprint("stmt", ""); }
    ;

/* part 2 - 9. statement */
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

if_stmt : IF LPAR cond_exp RPAR block_stmt %prec WITHOUT_ELSE   { m3dprint("IF block_stmt", ""); };
    | IF LPAR cond_exp RPAR block_stmt ELSE block_stmt          { m3dprint("IF block_stmt ELSE block_stmt", ""); };
    | IF LPAR cond_exp RPAR block_stmt ELSE stmt                { m3dprint("IF block_stmt ELSE stmt", ""); };
    
    | IF LPAR cond_exp RPAR stmt %prec WITHOUT_ELSE             { m3dprint("IF stmt", ""); };
    | IF LPAR cond_exp RPAR stmt ELSE block_stmt                { m3dprint("IF stmt ELSE block_stmt", ""); };
    | IF LPAR cond_exp RPAR stmt ELSE stmt                      { m3dprint("IF stmt ELSE stmt", ""); };
    ;

for_stmt : FOR LPAR bool_exp SEMI cond_bool_exp SEMI bool_exp RPAR block_stmt { m3dprint("FOR block_stmt", ""); }
    | FOR LPAR bool_exp SEMI cond_bool_exp SEMI bool_exp RPAR stmt            { m3dprint("FOR stmt", ""); }
    ;

bool_exp : %empty                       { m3dprint("false bool_exp", ""); }
    | exp                               { m3dprint("true bool_exp", ""); }
    ;

cond_bool_exp : %empty                  { m3dprint("false cond_bool_exp", ""); }
    | cond_exp                          { m3dprint("true cond_bool_exp", ""); }
    ;

while_stmt : WHILE LPAR cond_exp RPAR block_stmt                { m3dprint("WHILE block_stmt", ""); }
    | WHILE LPAR cond_exp RPAR stmt                             { m3dprint("WHILE stmt", ""); }
    ;

do_stmt : DO block_stmt WHILE LPAR cond_exp RPAR SEMI           { m3dprint("DO block_stmt WIHILE", ""); }
    | DO stmt WHILE LPAR cond_exp RPAR SEMI                     { m3dprint("DO stmt WIHILE", ""); }
    ;

/* part 3 - 2.3 The expression given for the condition 
    is a numerical type (one of char, int, or float). */
cond_exp : exp                          { m3dprint("cond exp", ""); }
    ;

/* part 2 - 10. expression */
exp : INTCONST                          { m3dprint("INTCONST", $1); }
    | REALCONST                         { m3dprint("REALCONST", $1); }
    | STRCONST                          { m3dprint("STRCONST", $1); }
    | CHARCONST                         { m3dprint("CHARCONST", $1); }
    | IDENT LPAR exp_list RPAR          { m3dprint("IDENT(exp_list)", $1); }
    | IDENT LPAR RPAR                   { m3dprint("IDENT()", $1); }

    /* part 2 - 11. An l-value is an identifier, optionally followed by a left bracket, 
        an expression, and a right bracket. Note that this restricts array 
        access to a single dimension. */
    /* part 3 - 2.4 Extra credit: widening for R8, R9, R10, R13, return stmt, call func */
    | l_val                             { m3dprint("l_val", ""); }
    | l_val ASSIGN exp                  { /* part 3 - R13 */ m3dprint("l_val = exp", "="); }
    | l_val PLUSASSIGN exp              { /* part 3 - R13 */ m3dprint("l_val += exp", "+="); }
    | l_val MINUSASSIGN exp             { /* part 3 - R13 */ m3dprint("l_val -= exp", "-="); }
    | l_val STARASSIGN exp              { /* part 3 - R13 */ m3dprint("l_val *= exp", "*="); }
    | l_val SLASHASSIGN exp             { /* part 3 - R13 */ m3dprint("l_val /= exp", "/="); }
    | INCR l_val %prec UINCR            { /* part 3 - R11 */ m3dprint("INCR l_val", "++"); }
    | DECR l_val %prec UDECR            { /* part 3 - R11 */ m3dprint("DECR l_val", "--"); }
    | l_val INCR %prec UINCR            { /* part 3 - R12 */ m3dprint("l_val INCR", "++"); }
    | l_val DECR %prec UDECR            { /* part 3 - R12 */ m3dprint("l_val DECR", "--"); }

    /* part 2 - 12. Unary operators (for any expression) are: -, !, ~ */
    | BANG exp %prec UBANG              { /* part 3 - R4 */ m3dprint("UBANG", "!"); }
    | TILDE exp %prec UTILDE            { /* part 3 - R2 */ m3dprint("UTILDE", "~"); }
    | MINUS exp %prec UMINUS            { /* part 3 - R3 */ m3dprint("UMINUS", "-"); }

    /* part 2 - 13. Binary operators are: ==, !=, >, >=, <, <=, +, -, *, /, %, |, &, ||, && */
    | exp MOD exp                       { /* part 3 - R8 */ m3dprint("MOD", "%"); }
    | exp PIPE exp                      { /* part 3 - R8 */ m3dprint("PIPE", "|"); }
    | exp AMP exp                       { /* part 3 - R8 */ m3dprint("AMP", "&"); }
    | exp PLUS exp                      { /* part 3 - R9 */ m3dprint("PLUS", "+"); }
    | exp MINUS exp                     { /* part 3 - R9 */ m3dprint("MINUS", "-"); }
    | exp STAR exp                      { /* part 3 - R9 */ m3dprint("STAR", "*"); }
    | exp SLASH exp                     { /* part 3 - R9 */ m3dprint("SLASH", "/"); }
    | exp EQUALS exp                    { /* part 3 - R10 */ m3dprint("EQUALS", "=="); }
    | exp NEQUAL exp                    { /* part 3 - R10 */ m3dprint("NEQUAL", "!="); }
    | exp GT exp                        { /* part 3 - R10 */ m3dprint("GT", ">"); }
    | exp GE exp                        { /* part 3 - R10 */ m3dprint("GE", ">="); }
    | exp LT exp                        { /* part 3 - R10 */ m3dprint("LT", "<"); }
    | exp LE exp                        { /* part 3 - R10 */ m3dprint("LE", "<="); }
    | exp DPIPE exp                     { /* part 3 - R10 */ m3dprint("DPIPE", "||"); }
    | exp DAMP exp                      { /* part 3 - R10 */ m3dprint("DAMP", "&&"); }

    /* part 2 - 14. Assignment operators are: =, +=, -=, *=, /= */
    | exp QUEST exp COLON exp           { /* part 3 - R1 */ m3dprint("exp QUEST exp COLON exp", ""); }
    | LPAR type RPAR exp                { /* part 3 - R5, R6, R7 */ m3dprint("LPAR type RPAR exp", ""); }
    | LPAR exp RPAR                     { m3dprint("( exp )", ""); }
    ;

exp_list : exp                          { m3dprint("single exp exp_list", ""); }
    | exp_list COMMA exp                { m3dprint("multiple exps exp_list", ""); }
    ; 

/* part 2 - 2.5 and part 3 - 2.8 Extra credit: struct member selection */
l_val : l_member                        { m3dprint("single l_member", ""); }
    | l_val DOT l_member                { /* part 3 - R15 */ m3dprint("l_val DOT l_member", "."); }
    ;

l_member : IDENT                        { m3dprint("IDENT", $1); }
    | IDENT dimen                       { /* part 3 - R14 */ m3dprint("IDENT dimen", $1); }
    ;

dimen : LBRACKET exp RBRACKET           { /* part 3 - R14 */ m3dprint("[ exp ]", ""); }
    | dimen LBRACKET exp RBRACKET       { /* part 3 - R14 */ m3dprint("dimen [ exp ]", ""); }
    ;

%%


