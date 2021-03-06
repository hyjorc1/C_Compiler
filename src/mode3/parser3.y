
%{

#include "m3global.h"


char *m3_cur_file_name = NULL;
char m3_is_global = 1;
char m3_error = 0;
char m3_return_error = 0;

/* Variables */ 
Type *cur_type = NULL;
Type *cast_type = NULL;
List *m3_global_vars = NULL;
HashMap *m3_global_map = NULL;

List *m3_local_vars = NULL;
HashMap *m3_local_map = NULL;

/* Structs */
Struct *cur_struct = NULL;
List *m3_global_structs = NULL;
List *m3_local_structs = NULL;

/* Functions */
Function *cur_fn = NULL;
List *m3_global_funcs = NULL;

/* Statements */
List *m3_local_stmts = NULL;

/* constant strings for types */
const char *char_str = "char";
const char *int_str = "int";
const char *float_str = "float";
const char *void_str = "void";
const char *error_str = "error";

/* mode 4 */
char binary_assign = 0;
int return_count = 0;

/* mode 5 */
int instr_line = 0;
int instr_label = 0;
char cond_trigger = 0;

%}

%define api.prefix {m3}

%union {
    char *str;
    Type *t;
    Variable *v;
    Statement *sm;
    Struct *st;
    Function *fn;
    List *l;
    int num;
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
%right  QUEST COLON TERNARY
%left   DPIPE CDPIPE
%left   DAMP CDAMP
%left   PIPE
%left   AMP
%left   EQUALS NEQUAL
%left   LT LE GT GE
%left   PLUS MINUS
%left   STAR SLASH MOD
%left   LPAR RPAR LBRACKET RBRACKET DOT

%nonassoc UMINUS UBANG UTILDE UINCR UDECR

%type <v> var init_var noinit_var para var_return
%type <l> para_list exp_list
/* part 3 - exp returns type */
%type <t> exp l_val cond_exp root_exp lval_assign lval_bassign array_ident gtype all_type
%type <fn> func_decl func_proto func_def
/* part 5 */
%type <num> MK
%type <t> if_cond cond_emp_exp emp_exp do_cond while_cond rexp for_cond_emp_exp cond_exp2
%type <l> block_stmt stmt_list stmt if_stmt for_stmt while_stmt do_stmt stmts NL

%%

/* part 2 - 1. A C program is a sequence of zero or more (global) variable declarations, 
    function prototypes, and function definitions, appearing in any order. */
root : %empty                           { m3dprint("empty root", ""); }
    | root var_decl                     { m3dprint("global var_decl", "============== global var_decl  ============="); }
    | root func_proto                   { m3dprint("global func_proto", "============== global func_proto ============="); }
    | root func_def                     { m3dprint("global func_def ", "============== global func_def ============="); }
    | root struct_decl                  { m3dprint("root struct_decl", "============== global struct_decl ============="); }
    ;

/* part 2 - 2. A variable declaration is a type name, followed by a comma-separated list of 
    one or more identifiers, each identifier optionally followed by a left bracket, 
    an integer constant, and a right bracket. The list is terminated with a semicolon. 
    Note that this restricts arrays to a single dimension. */
var_decl : type init_var_list SEMI      { m3dprint("type init var list ;", ""); free_type_ast(cur_type); cur_type = NULL; }
    ;

/* part 2 - 2.3 and part 3 - 2.6 Extra credit: constants */
type : gtype                            { cur_type = $1; }
    ;

cast_type : gtype                       { cast_type = $1; }
    ;

gtype : all_type                        { m3dprint("all_type", ""); $$ = $1; }
    | CONST all_type                    { m3dprint("CONST all_type", ""); if ($2) $2->is_const = 1; $$ = $2; }
    | all_type CONST                    { m3dprint("all_type CONST", ""); if ($1) $1->is_const = 1; $$ = $1; }
    ;

all_type : PRIMTYPE                     { m3dprint("PRIMTYPE", $1); $$ = new_type_ast($1, 0, 0, 0); }
    | STRUCT IDENT                      { m3dprint("STRUCT IDENT", $2); $$ = handle_struct_type_var($2); }
    ;

init_var_list : init_var                { m3dprint("single init var init var list", ""); update_var_list($1); }
    | init_var_list COMMA init_var      { m3dprint("init var list COMMA init_var", ","); update_var_list($3); }
    ;

/* part 2 - 2.2 and part 3 - 2.5 Extra credit: variable initialization */
init_var : var                          { m3dprint("init_var var", ""); $$ = update_type_map($1); }
    | var_return ASSIGN rexp            { m3dprint("var = exp", "="); $$ = handle_init_var($1, $3); return_count--; }
    ;

var_return : var                        { $$ = $1; return_count++; }
    ;

var : IDENT                             { m3dprint("IDENT", $1); $$ = handle_var_ident($1, 0); }
    | IDENT LBRACKET INTCONST RBRACKET  { m3dprint("IDENT [int]", $1); $$ = handle_var_ident($1, 1); m4handle_arr_init($1, $3); }
    ;

/* part 2 - 2.4 Extra credit: user-defined structs 
    A user-defined type declaration is??? the keyword struct, followed by an 
    identifier, a left brace, zero or more variable declarations (without 
    initializations), a right brace, and a semicolon. */
/* part 3 - 2.7 Extra credit: user-defined structs */
struct_decl : struct_name_decl LBRACE struct_body_decls RBRACE SEMI { update_structs(); }
    ;

struct_name_decl : STRUCT IDENT         { m3dprint("STRUCT { struct decl }", $2); handle_struct_name_decl($2); }
    ;

struct_body_decls : %empty              { m3dprint("empty struct body decls", ""); }
    | struct_body_decl                  { m3dprint("sinlge struct body decl", ""); }
    | struct_body_decls struct_body_decl{ m3dprint("multiple struct body decl", ""); }
    ;

struct_body_decl : noinit_var_decl      { m3dprint("noinit var decl", ""); }
    | struct_decl                       { m3dprint("nested struct decl", ""); }
    ;

noinit_var_decl : type noinit_var_list SEMI { m3dprint("type noinit_var_list SEMI", ""); free_type_ast(cur_type); cur_type = NULL; }
    ;

noinit_var_list : noinit_var            { m3dprint("single noinit var", ""); update_struct_vars($1); }
    | noinit_var_list COMMA noinit_var  { m3dprint("multiple noinit vars", ","); update_struct_vars($3); }
    ;

noinit_var : IDENT                      { m3dprint("noinit var", $1); $$ = handle_noinit_var_ident($1, 0); }
    | IDENT LBRACKET INTCONST RBRACKET  { m3dprint("noinit var [int]", $1); $$ = handle_noinit_var_ident($1, 1); }
    ;

/* part 2 - 4. A function prototype is a function declaration followed by a semicolon. */
func_proto : func_decl SEMI             { m3dprint("func_proto SEMI", ""); handle_func_proto(); }
    ;

/* part 2 - 5. A function declaration is a type name (the return type of the function), 
    followed by an identifier (the name of the function), a left parenthesis, 
    an optional comma-separated list of formal parameters, and a right parenthesis. */
func_decl : func_name_decl LPAR para_list RPAR  { m3dprint("func(para list)", ""); handle_func_decl(); }
    | func_name_decl LPAR RPAR                  { m3dprint("func()", ""); handle_func_decl(); }
    ;

func_name_decl : type IDENT             { m3dprint("func name decl", $2); handle_func_name($2);  }
    ;

para_list : para_list COMMA para        { m3dprint("multiple para list", ","); }
    | para                              { m3dprint("single para list", ""); }
    ;

/* part 2 - 6. A formal parameter is??? a type name, followed by an identifier, and optionally 
    followed by a left and right bracket. */
para : type IDENT                       { m3dprint("type IDENT", $2); handle_para($2, 0); cur_type = NULL; }
    | type IDENT LBRACKET RBRACKET      { m3dprint("type IDENT []", $2); handle_para($2, 1); cur_type = NULL; }
    ;

/* part 2 - 7. A function definition is a function declaration followed by a left brace, 
    a sequence of zero or more variable declarations, a sequence of zero or more 
    statements, and a right brace. Note that this definition requires all variable 
    declarations to appear before statements. */
func_def : func_decl LBRACE func_local_decls func_stmts RBRACE  { m3dprint("func(){func_body}", ""); handle_func_def(); }
    | func_decl LBRACE func_local_decls RBRACE                  { m3dprint("func(){func_local_decls}", ""); handle_func_def(); }
    ;

func_stmts : stmt_list MK               { backpatch($1, $2); }
    ;

func_local_decls : %empty               { m3dprint("empty func_local_decls", ""); }
    | func_local_decls local_decl       { m3dprint("multiple local_decl", ""); }
    | local_decl                        { m3dprint("single local_decl", ""); }
    ;

local_decl : var_decl                   { m3dprint("local var decl", ""); }
    | struct_decl                       { m3dprint("local_decl struct decl", ""); }
    ;

/* part 2 - 8. A statement block is a left brace, a sequence of zero or more statements, and a right brace. */
block_stmt : LBRACE stmt_list RBRACE    { m3dprint("{ stmt list }", ""); $$ = $2; }
    | LBRACE RBRACE                     { m3dprint("{ empty }", ""); $$ = NULL; }
    ;

stmt_list : stmt_list MK stmt           { m3dprint("stmt list stmt", ""); $$ = $3; backpatch($1, $2); }
    | stmt                              { m3dprint("stmt", ""); $$ = $1; }
    ;

/* part 2 - 9. statement */
stmt : SEMI                             { m3dprint("SEMI", ""); $$ = NULL; }
    | root_exp SEMI                     { m3dprint("exp SEMI", ""); handle_exp_stmt($1); $$ = NULL; }
    | break SEMI                        { m3dprint("BREAK SEMI", ""); m5handle_break(); $$ = NULL; }
    | continue SEMI                     { m3dprint("CONTINUE SEMI", ""); m5handle_continue(); $$ = NULL; }
    | return_stmt                       { m3dprint("return_stmt", ""); $$ = NULL; }
    | if_stmt                           { m3dprint("if_stmt", ""); $$ = $1; }
    | for_stmt                          { m3dprint("for_stmt", ""); $$ = $1; }
    | while_stmt                        { m3dprint("while_stmt", ""); $$ = $1; }
    | do_stmt                           { m3dprint("do_stmt", ""); $$ = $1; }
    ;

break : BREAK                           { m4handle_comment("break"); }
    ;

continue : CONTINUE                     { m4handle_comment("continue"); }
    ;

return_stmt : return SEMI               { m3dprint("RETURN SEMI", ""); handle_return_stmt(new_type_ast(strdup(void_str), 0, 0, 0)); }
    | return rexp SEMI                  { m3dprint("RETURN exp SEMI", ""); handle_return_stmt($2); }
    ;

return : RETURN                         { m4handle_comment("return"); }
    ;

if_stmt : if_cond MK stmts %prec WITHOUT_ELSE   { m3dprint("IF (cond){}", ""); $$ = m5handle_if($1, $2, $3); }
    | if_cond MK stmts ELSE NL MK stmts         { m3dprint("IF (cond){} ELSE {}", ""); $$ = m5handle_ifelse($1, $2, $3, $5, $6, $7); }
    ;

stmts : block_stmt                      { $$ = $1; }           
    | stmt                              { $$ = $1; }
    ;

/* The expression inside an if condition is numerical. */
if_cond : if LPAR cond_exp RPAR         { m3dprint("IF condition", ""); $$ = handle_cond_exp("if statement", $3); }
    ;

if : IF                                 { m4handle_comment("if statement"); }
    ;

for_stmt : for LPAR emp_exp SEMI MK for_cond_emp_exp SEMI MK emp_exp NL RPAR MK stmts 
                                        { m3dprint("for(){}", ""); $$ = m5handle_for($5, $6, $8, $10, $12, $13); }
    ;

for_cond_emp_exp : cond_emp_exp         { $$ = m5hanlde_for_cond($1); }
    ;

for : FOR                               { m4handle_comment("for statement"); m5handle_loop(); }
    ;

emp_exp : %empty                        { m3dprint("false emp_exp", ""); $$ = NULL; }
    | exp                              { m3dprint("true emp_exp", ""); $$ = $1; }
    ;

cond_emp_exp : %empty                   { m3dprint("false cond_emp_exp", ""); $$ = NULL; }
    | cond_exp                          { m3dprint("true cond_emp_exp", ""); $$ = handle_cond_exp("for loop", $1); }
    ;

while_stmt : while MK while_cond MK stmts      { m3dprint("WHILE block_stmt", ""); $$ = m5handle_while($2, $3, $4, $5); }
    ;

while : WHILE                           { m4handle_comment("while statement"); m5handle_loop(); }
    ;

while_cond : LPAR cond_exp RPAR         { $$ = handle_cond_exp("while loop", $2); };
    ;

do_stmt : do MK stmts WHILE MK do_cond SEMI   { m3dprint("do{}while(cond)", ""); $$ = m5handle_do($2, $3, $5, $6); }
    ;

do : DO                                 { m4handle_comment("do-while statement"); m5handle_loop(); }
    ;

do_cond : LPAR cond_exp RPAR            { m3dprint("do condition", ""); $$ = handle_cond_exp("do while loop", $2); }
    ;

/* part 2 - 10. expression */
exp : INTCONST                          { m3dprint("INTCONST", $1); $$ = new_type_ast(strdup(int_str), 1, 0, 0); m4handle_int($1); }
    | REALCONST                         { m3dprint("REALCONST", $1); $$ = new_type_ast(strdup(float_str), 1, 0, 0); m4handle_real($1); }
    | STRCONST                          { m3dprint("STRCONST", $1); $$ = new_type_ast(strdup(char_str), 1, 0, 1); m4handle_str($1); }
    | CHARCONST                         { m3dprint("CHARCONST", $1); $$ = new_type_ast(strdup(char_str), 1, 0, 0); m4handle_char($1); }
    | IDENT LPAR exp_list RPAR          { m3dprint("IDENT(exps)", $1); $$ = handle_func_call_exp($1, $3); }
    | IDENT LPAR RPAR                   { m3dprint("IDENT()", $1); $$ = handle_func_call_exp($1, NULL); }

    /* part 2 - 11. An l-value is an identifier, optionally followed by a left bracket, 
        an expression, and a right bracket. Note that this restricts array 
        access to a single dimension. */
    /* part 3 - 2.4 Extra credit: widening for R8, R9, R10, R13, return stmt, call func */
    | l_val                             { m3dprint("l_val", ""); $$ = m4handle_lval($1); }
    | lval_assign ASSIGN exp            { /* part 3 - R13 */ m3dprint("l_val = exp", "="); $$ = handle_assign_exp(0, $1, "=", $3); return_count--; }
    | lval_bassign PLUSASSIGN exp       { /* part 3 - R13 */ m3dprint("l_val += exp", "+="); $$ = handle_assign_exp(0, $1, "+=", $3); return_count--; binary_assign = 0; }
    | lval_bassign MINUSASSIGN exp      { /* part 3 - R13 */ m3dprint("l_val -= exp", "-="); $$ = handle_assign_exp(0, $1, "-=", $3); return_count--; binary_assign = 0; }
    | lval_bassign STARASSIGN exp       { /* part 3 - R13 */ m3dprint("l_val *= exp", "*="); $$ = handle_assign_exp(0, $1, "*=", $3); return_count--; binary_assign = 0; }
    | lval_bassign SLASHASSIGN exp      { /* part 3 - R13 */ m3dprint("l_val /= exp", "/="); $$ = handle_assign_exp(0, $1, "/=", $3); return_count--; binary_assign = 0; }
    | INCR l_val %prec UINCR            { /* part 3 - R11 */ m3dprint("INCR l_val", "++"); $$ = handle_r11_exp("++", $2); }
    | DECR l_val %prec UDECR            { /* part 3 - R11 */ m3dprint("DECR l_val", "--"); $$ = handle_r11_exp("--", $2); }
    | l_val INCR %prec UINCR            { /* part 3 - R12 */ m3dprint("l_val INCR", "++"); $$ = handle_r12_exp($1, "++"); }
    | l_val DECR %prec UDECR            { /* part 3 - R12 */ m3dprint("l_val DECR", "--"); $$ = handle_r12_exp($1, "--"); }

    /* part 2 - 12. Unary operators (for any expression) are: -, !, ~ */
    | BANG exp %prec UBANG              { /* part 3 - R4 */ m3dprint("UBANG", "!"); $$ = handle_ubang($2); }
    | TILDE exp %prec UTILDE            { /* part 3 - R2 */ m3dprint("UTILDE", "~"); $$ = handle_utilde($2); }
    | MINUS exp %prec UMINUS            { /* part 3 - R3 */ m3dprint("UMINUS", "-"); $$ = handle_uminus($2); }

    /* part 2 - 13. Binary operators are: ==, !=, >, >=, <, <=, +, -, *, /, %, |, &, ||, && */
    | exp MOD exp                       { /* part 3 - R8 */ m3dprint("MOD", "%"); $$ = handle_r8_exp($1, "%", $3); }
    | exp PIPE exp                      { /* part 3 - R8 */ m3dprint("PIPE", "|"); $$ = handle_r8_exp($1, "|", $3); }
    | exp AMP exp                       { /* part 3 - R8 */ m3dprint("AMP", "&"); $$ = handle_r8_exp($1, "&", $3); }
    | exp PLUS exp                      { /* part 3 - R9 */ m3dprint("PLUS", "+"); $$ = handle_r9_exp($1, "+", $3);  }
    | exp MINUS exp                     { /* part 3 - R9 */ m3dprint("MINUS", "-"); $$ = handle_r9_exp($1, "-", $3); }
    | exp STAR exp                      { /* part 3 - R9 */ m3dprint("STAR", "*"); $$ = handle_r9_exp($1, "*", $3); }
    | exp SLASH exp                     { /* part 3 - R9 */ m3dprint("SLASH", "/"); $$ = handle_r9_exp($1, "/", $3); }
    | exp EQUALS exp                    { /* part 3 - R10 */ m3dprint("EQUALS", "=="); $$ = handle_r10_exp($1, "==", $3); }
    | exp NEQUAL exp                    { /* part 3 - R10 */ m3dprint("NEQUAL", "!="); $$ = handle_r10_exp($1, "!=", $3); }
    | exp GT exp                        { /* part 3 - R10 */ m3dprint("GT", ">"); $$ = handle_r10_exp($1, ">", $3); }
    | exp GE exp                        { /* part 3 - R10 */ m3dprint("GE", ">="); $$ = handle_r10_exp($1, ">=", $3); }
    | exp LT exp                        { /* part 3 - R10 */ m3dprint("LT", "<"); $$ = handle_r10_exp($1, "<", $3); }
    | exp LE exp                        { /* part 3 - R10 */ m3dprint("LE", "<="); $$ = handle_r10_exp($1, "<=", $3); }
    | cond_exp2 DPIPE MK cond_exp2 %prec CDPIPE       { /* part 3 - R10 */ m3dprint("DPIPE", "||"); $$ = handle_r10_marker($1, "||", $3, $4); }
    | cond_exp2 DAMP MK cond_exp2 %prec CDAMP       { /* part 3 - R10 */ m3dprint("DAMP", "&&"); $$ = handle_r10_marker($1, "&&", $3, $4); }

    /* part 2 - 14. Assignment operators are: =, +=, -=, *=, /= */
    | cond_exp2 QUEST MK rexp NL COLON MK rexp MK %prec TERNARY      
                                        { /* part 3 - R1 */ m3dprint("exp QUEST exp COLON exp", ""); $$ = handle_ternary_exp($1, $3, $4, $5, $7, $8, $9); }
    | LPAR cast_type RPAR exp           { /* part 3 - R5, R6, R7 */ m3dprint("(type) exp", ""); $$ = handle_cast_exp($4); }
    | LPAR exp RPAR                     { m3dprint("(exp)", ""); $$ = $2; }
    ;

/* part 3 - 2.3 The expression given for the condition 
    is a numerical type (one of char, int, or float). */
cond_exp : rexp                         { $$ = m5handle_cond_exp($1); }
    ;

cond_exp2 : exp                         { $$ = m5handle_cond_exp($1); }
    ;

root_exp : prev_root exp                { m3dprint("root exp", ""); $$ = $2; }
    ;

prev_root : %empty                      { m3dprint("root exp", ""); m4handle_comment("expression"); }
    ;

rexp : prer exp posr                    { $$ = $2; }
    ;

prer : %empty                           { return_count++; }
    ;

posr : %empty                           { return_count--; }
    ;

/* part 5 marker */
MK : %empty                             { $$ = m5handle_label(); }
    ;

/* part 5 next list */
NL : %empty                             { $$ = m5handle_next_line(); }
    ;

lval_assign : l_val                     { return_count++; $$ = $1; }
    ;

lval_bassign : l_val                    { return_count++; binary_assign = 1; $$ = m4handle_lval($1); }
    ;

exp_list : rexp                         { m3dprint("single exp", ""); $$ = handle_single_type($1); }
    | exp_list COMMA rexp               { m3dprint("multiple exps", ""); $$ = list_add_last($1, $3); }
    ; 

/* part 2 - 2.5 and part 3 - 2.8 Extra credit: struct member selection */
l_val : IDENT                               { m3dprint("l_val id", $1); $$ = handle_l_ident($1); }
    | array_ident LBRACKET rexp RBRACKET    { m3dprint("l_val id[exp]", $1->id); $$ = handle_l_array_access($1, $3); }
    | l_val DOT IDENT                       { /* part 3 - R15 */ m3dprint("l_val.member", $3); $$ = handle_l_member($1, $3); }
    | l_val DOT IDENT LBRACKET rexp RBRACKET{ /* part 3 - R15 */ m3dprint("l_val.member[exp]", $3); $$ = handle_l_array_member($1, $3, $5); }
    ;

array_ident : IDENT                         { $$ = m4handle_lval(handle_l_ident($1)); }
    ;

%%
