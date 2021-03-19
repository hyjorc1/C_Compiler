#ifndef AST_H
#define AST_H

#include "deque.h"

/* -------------------- Type AST -------------------- */

typedef struct {
    char *name;
    char is_const;
    char is_struct;
} Type;

Type *new_type_ast(char *name, char is_const, char is_struct);

Type *deep_copy_type_ast(Type *t);

void free_type_ast(void *p);

/* -------------------- Variable AST -------------------- */

typedef struct {
    Type *type;
    char *name;
    char is_array;
    char is_init;
} Variable;

Variable *new_variable_ast(Type *type, char *name, char is_array, char is_init);

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
} Struct;

Struct *new_struct_ast(char *name, List *vars);

void free_struct_ast(void *p);

/* -------------------- Function AST -------------------- */

typedef struct {
    Type *return_type;
    char *name;
    List *parameters;
    List *local_structs;
    List *local_vars;
    List *statements;
    char is_proto;
} Function;

Function *new_function_ast(Type *return_type, char *name, List *parameters);

void free_function_ast(void *p);

#endif