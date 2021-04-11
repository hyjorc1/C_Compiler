#ifndef AST_H
#define AST_H

#include "deque.h"
#include "map.h"

/* -------------------- Variable AST -------------------- */

typedef struct {
    char *name;
    char is_array;
    char is_init;
    int lineno;
} Variable;

Variable *new_variable_ast(char *name, char is_array, char is_init, int lineno);

void free_variable_ast(void *p);

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
    int lineno;
} Struct;

Struct *new_struct_ast(char *name, List *vars, HashMap *local_var_map, int lineno);

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
    int lineno;

    // mode 4
    int depth;
    int max;
    char *class_name;
} Function;

Function *new_function_ast(Type *return_type, char *name, int lineno);

void free_function_ast(void *p);

#endif