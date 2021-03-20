#include "ast.h"
#include "global.h"

/* -------------------- Variable AST -------------------- */

Variable *new_variable_ast(char *name, char is_array, char is_init) {
    Variable *v = (Variable *)malloc(sizeof(Variable));
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
    free(v->name);
    print(">>>>>>>>free_variable_ast 3\n");
    free(p);
    print(">>>>>>>>free_variable_ast 4\n");
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

Struct *new_struct_ast(char *name, List *vars, HashMap *local_var_map) {
    Struct *s = (Struct *)malloc(sizeof(Struct));
    s->name = name;
    s->vars = vars;
    s->local_var_map = local_var_map;
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
    map_free(s->local_var_map);
    print(">>>>>>>>free_struct_ast 4\n");
    free(p);
    print(">>>>>>>>free_struct_ast 5\n");
}

/* -------------------- Function AST -------------------- */

Function *new_function_ast(Type *return_type, char *name, List *parameters) {
    Function *f = (Function *)malloc(sizeof(Function));
    f->return_type = return_type;
    f->name = name;
    f->parameters = parameters;

    f->local_var_map = NULL;

    f->local_structs = NULL;
    f->local_vars = NULL;
    f->statements = NULL;

    f->is_proto = 0;
    return f;
}

void free_function_ast(void *p) {
    if (!p)
        return;
    Function *f = (Function *)p;
    print(">>>>>>>>free_function_ast 1\n");
    free(f->return_type);
    print(">>>>>>>>free_function_ast 2\n");
    free(f->name);
    print(">>>>>>>>free_function_ast 3\n");
    list_destroy(f->parameters);
    
    print(">>>>>>>>free_function_ast 4\n");
    map_free(f->local_var_map);
    
    print(">>>>>>>>free_function_ast 5\n");
    list_destroy(f->local_structs);
    print(">>>>>>>>free_function_ast 6\n");
    list_destroy(f->local_vars);
    print(">>>>>>>>free_function_ast 7\n");
    list_destroy(f->statements);
    print(">>>>>>>>free_function_ast 8\n");

    free(p);
    print(">>>>>>>>free_function_ast 9\n");
}