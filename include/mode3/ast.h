#ifndef AST_H
#define AST_H

#include "deque.h"
#include "map.h"

/* -------------------- Variable AST -------------------- */

typedef struct {
    char *name;
    char is_array;
    char is_init;
} Variable;

Variable *new_variable_ast(char *name, char is_array, char is_init);

void free_variable_ast(void *p);

/* -------------------- Variables AST -------------------- */

typedef struct {
    List *vars;
    HashMap *map;
} Vars;

Vars *new_vars();

void free_vars(Vars *vars);

/* -------------------- Statement AST -------------------- */

typedef struct {
    int lineno;
    Type *type;
} Statement;

Statement *new_statement_ast(int lineno, Type *type);

void free_statement_ast(void *p);

/* -------------------- Struct AST -------------------- */

typedef struct {
    char *name;
    List *vars;
    HashMap *local_var_map;
} Struct;

Struct *new_struct_ast(char *name, List *vars, HashMap *local_var_map);

void free_struct_ast(void *p);

/* -------------------- Function AST -------------------- */

typedef struct {
    Type *return_type;
    char *name;
    List *parameters;

    HashMap *local_var_map;

    List *local_structs;
    List *local_vars;
    List *statements;

    char is_proto;
} Function;

Function *new_function_ast(Type *return_type, char *name, List *parameters);

void free_function_ast(void *p);

#endif