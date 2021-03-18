#ifndef AST_H
#define AST_H

#include "deque.h"

/* -------------------- Type AST -------------------- */

typedef struct {
    char *name;
    char is_const;
    char is_array;
} Type;

Type *new_type_ast(char *name, char is_const, char is_array);

void free_type_ast(void *p);

/* -------------------- Variable AST -------------------- */

typedef struct {
    Type *type;
    char *name;
    char is_init;
} Variable;

Variable *new_variable_ast(Type *type, char *name, char is_init);

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

Struct *new_struct_ast(char *name);

void free_struct_ast(void *p);

/* -------------------- Function AST -------------------- */

typedef struct {
    char *name;
    List *parameters;
    Type *return_type;
    List *local_structs;
    List *local_vars;
    List *statements;
} Function;

Function *new_function_ast(char *name, Type *return_type);

void free_function_ast(void *p);

#endif