#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "global.h"

/* -------------------- Type AST -------------------- */
Type *new_type_ast(char *name, char is_const, char is_struct) {
    Type *t = (Type *)malloc(sizeof(Type));
    t->name = name;
    t->is_const = is_const;
    t->is_struct = is_struct;
    return t;
}

Type *deep_copy_type_ast(Type *t) {
    Type *copy = (Type *)malloc(sizeof(Type));
    copy->name = strdup(t->name);
    copy->is_const = t->is_const;
    copy->is_struct = t->is_struct;
    return copy;
}

void free_type_ast(void *p) {
    if (!p)
        return;
    print(">>>>>>>>free_type_ast 1\n");
    Type *t = (Type *)p;
    print(">>>>>>>>free_type_ast 2\n");
    free(t->name);
    print(">>>>>>>>free_type_ast 3\n");
    free(p);
    print(">>>>>>>>free_type_ast 4\n");
}

/* -------------------- Variable AST -------------------- */

Variable *new_variable_ast(Type *type, char *name, char is_array, char is_init) {
    Variable *v = (Variable *)malloc(sizeof(Variable));
    v->type = type;
    v->name = name;
    v->is_array = is_array;
    v->is_init = is_init;
    return v;
}

void free_variable_ast(void *p) {
    if (!p)
        return;
    print(">>>>>>>>free_variable_ast 1\n");
    Variable *v = (Variable *)p;
    print(">>>>>>>>free_variable_ast 2\n");
    free_type_ast(v->type);
    print(">>>>>>>>free_variable_ast 3\n");
    free(v->name);
    print(">>>>>>>>free_variable_ast 4\n");
    free(p);
    print(">>>>>>>>free_variable_ast 5\n");
}

/* -------------------- Statement AST -------------------- */

Statement *new_statement_ast(int lineno, Type *type) {
    Statement *stmt = (Statement *)malloc(sizeof(Statement));
    stmt->lineno = lineno;
    stmt->type = type;
    return stmt;
}

void free_statement_ast(void *p) {
    if (!p)
        return;
    Statement *stmt = (Statement *)p;
    print(">>>>>>>>free_statement_ast 1\n");
    free_type_ast(stmt->type);
    print(">>>>>>>>free_statement_ast 2\n");
    free(p);
    print(">>>>>>>>free_statement_ast 3\n");
}

/* -------------------- Struct AST -------------------- */

Struct *new_struct_ast(char *name, List *vars) {
    Struct *s = (Struct *)malloc(sizeof(Struct));
    s->name = name;
    s->vars = vars;
    return s;
}

void free_struct_ast(void *p) {
    if (!p)
        return;
    Struct *s = (Struct *)p;
    print(">>>>>>>>free_struct_ast 1\n");
    free(s->name);
    print(">>>>>>>>free_struct_ast 2\n");
    list_destroy(s->vars);
    print(">>>>>>>>free_struct_ast 3\n");
    free(p);
    print(">>>>>>>>free_struct_ast 4\n");
}

/* -------------------- Function AST -------------------- */

Function *new_function_ast(Type *return_type, char *name, List *parameters) {
    Function *f = (Function *)malloc(sizeof(Function));
    f->return_type = return_type;
    f->name = name;
    f->parameters = parameters;
    f->local_structs = list_new(sizeof(Struct), free_struct_ast);
    f->local_vars = list_new(sizeof(Variable), free_variable_ast);
    f->statements = list_new(sizeof(Statement), free_statement_ast);
    f->is_proto = 0;
    return f;
}

void free_function_ast(void *p) {
    if (!p)
        return;
    Function *f = (Function *)p;
    print(">>>>>>>>free_function_ast 1\n");
    free(f->name);
    print(">>>>>>>>free_function_ast 2\n");
    list_destroy(f->parameters);
    print(">>>>>>>>free_function_ast 3\n");
    free(f->return_type);
    print(">>>>>>>>free_function_ast 4\n");
    list_destroy(f->local_structs);
    print(">>>>>>>>free_function_ast 5\n");
    list_destroy(f->local_vars);
    print(">>>>>>>>free_function_ast 6\n");
    list_destroy(f->statements);
    print(">>>>>>>>free_function_ast 7\n");
    free(p);
    print(">>>>>>>>free_function_ast 8\n");
}