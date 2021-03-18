#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

/* -------------------- Type AST -------------------- */
Type *new_type_ast(char *name, char is_const, char is_array) {
    Type *t = (Type *)malloc(sizeof(Type));
    t->name = name;
    t->is_const = is_const;
    t->is_array = is_array;
    return t;
}

void free_type_ast(void *p) {
    Type *t = (Type *)p;
    free(t->name);
    free(p);
}

/* -------------------- Variable AST -------------------- */

Variable *new_variable_ast(Type *type, char *name, char is_init) {
    Variable *v = (Variable *)malloc(sizeof(Variable));
    v->type= type;
    v->name = name;
    v->is_init = is_init;
    return v;
}

void free_variable_ast(void *p) {
    Variable *v = (Variable *)p;
    free_type_ast(v->type);
    free(v->name);
    free(p);
}

/* -------------------- Variable AST -------------------- */

Statement *new_statement_ast(int lineno, Type *type) {
    Statement *stmt = (Statement *)malloc(sizeof(Statement));
    stmt->lineno = lineno;
    stmt->type = type;
    return stmt;
}

void free_statement_ast(void *p) {
    Statement *stmt = (Statement *)p;
    free_type_ast(stmt->type);
    free(p);
}

/* -------------------- Struct AST -------------------- */

Struct *new_struct_ast(char *name) {
    Struct *s = (Struct *)malloc(sizeof(Struct));
    s->name = name;
    s->vars = list_new(sizeof(Variable), free_variable_ast);
    return s;
}

void free_struct_ast(void *p) {
    Struct *s = (Struct *)p;
    free(s->name);
    list_destroy(s->vars);
    free(p);
}

/* -------------------- Function AST -------------------- */

Function *new_function_ast(char *name, Type *return_type) {
    Function *f = (Function *)malloc(sizeof(Function));
    f->name = name;
    f->parameters = list_new(sizeof(Variable), free_variable_ast);
    f->return_type = return_type;
    f->local_structs = list_new(sizeof(Struct), free_struct_ast);
    f->local_vars = list_new(sizeof(Variable), free_variable_ast);
    f->statements = list_new(sizeof(Statement), free_statement_ast);
    return f;
}

void free_function_ast(void *p) {
    Function *f = (Function *)p;
    free(f->name);
    list_destroy(f->parameters);
    free(f->return_type);
    list_destroy(f->local_structs);
    list_destroy(f->local_vars);
    list_destroy(f->statements);
    free(p);
}