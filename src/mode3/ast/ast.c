#include "ast.h"
#include "global.h"

/* -------------------- Type AST -------------------- */
Type *new_type_ast(char *name, char is_const, char is_struct, char is_array) {
    Type *t = (Type *)malloc(sizeof(Type));
    t->name = name;
    t->is_const = is_const;
    t->is_struct = is_struct;
    t->is_array = is_array;
    t->lineno = -1;
    // mode 4
    t->addr = -1;
    t->id = NULL;
    t->is_global = -1;
    return t;
}

Type *deep_copy_type_ast(Type *t) {
    if (t == NULL)
        return NULL;
    Type *copy = (Type *)malloc(sizeof(Type));
    copy->name = strdup(t->name);
    copy->is_const = t->is_const;
    copy->is_struct = t->is_struct;
    copy->is_array = t->is_array;
    copy->lineno = t->lineno;
    // mode 4
    copy->addr = t->addr;
    copy->id = t->id ? strdup(t->id) : NULL;
    copy->is_global = t->is_global;
    return copy;
}

void free_type_ast(void *p) {
    if (!p)
        return;
    // print(">>>>>>>>free_type_ast 1\n");
    Type *t = (Type *)p;
    // print(">>>>>>>>free_type_ast 2\n");
    free(t->name);
    // print(">>>>>>>>free_type_ast 3\n");
    free(p);
    // print(">>>>>>>>free_type_ast 4\n");
    free(t->id);
}

/* caller needs to free the return string */
char *type_to_str(Type *t) {
    if (t == NULL)
        return NULL;
    int len = 0;
    if (t->is_const) len += 6;
    if (t->is_struct) len += 7;
    if (t->is_array) len += 2;
    len += strlen(t->name) + 2;
    char *str = (char *)malloc(sizeof(char) * len);
    strcpy(str, "");
    if (t->is_const) strcat(str, "const ");
    if (t->is_struct) strcat(str, "struct ");
    strcat(str, t->name);
    strcat(str, t->is_array ? "[]" : "");
    return str;
}

char exact_match_type(Type *from, Type *to) {
    if (from == NULL || to == NULL
        || strcmp(from->name, to->name)
        || from->is_array != to->is_array
        || from->is_struct != to->is_struct)
        return 0;
    return 1;
}

/* -------------------- Variable AST -------------------- */

Variable *new_variable_ast(char *name, char is_array, char is_init, int lineno) {
    Variable *v = (Variable *)malloc(sizeof(Variable));
    v->name = name;
    v->is_array = is_array;
    v->is_init = is_init;
    v->lineno = lineno;
    return v;
}

void free_variable_ast(void *p) {
    if (!p)
        return;
    // print(">>>>>>>>free_variable_ast 1\n");
    Variable *v = (Variable *)p;
    // print(">>>>>>>>free_variable_ast 2\n");
    free(v->name);
    // print(">>>>>>>>free_variable_ast 3\n");
    free(p);
    // print(">>>>>>>>free_variable_ast 4\n");
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
    Statement *s = (Statement *)p;
    // print(">>>>>>>>free_statement_ast 1\n");
    free_type_ast(s->type);
    // print(">>>>>>>>free_statement_ast 2\n");
    free(p);
    // print(">>>>>>>>free_statement_ast 3\n");
}

/* -------------------- Struct AST -------------------- */

Struct *new_struct_ast(char *name, List *vars, HashMap *local_var_map, int lineno) {
    Struct *s = (Struct *)malloc(sizeof(Struct));
    s->name = name;
    s->vars = vars;
    s->local_var_map = local_var_map;
    s->lineno = lineno;
    return s;
}

void free_struct_ast(void *p) {
    if (!p)
        return;
    Struct *s = (Struct *)p;
    // print(">>>>>>>>free_struct_ast 1\n");
    free(s->name);    
    // print(">>>>>>>>free_struct_ast 2\n");
    list_destroy(s->vars);
    // print(">>>>>>>>free_struct_ast 3\n");
    map_free(s->local_var_map);
    // print(">>>>>>>>free_struct_ast 4\n");
    free(p);
    // print(">>>>>>>>free_struct_ast 5\n");
}

/* -------------------- Function AST -------------------- */

Function *new_function_ast(Type *return_type, char *name, int lineno) {
    Function *f = (Function *)malloc(sizeof(Function));
    f->return_type = return_type;
    f->name = name;
    f->parameters = NULL;

    f->local_var_map = NULL;

    f->local_structs = NULL;
    f->local_vars = NULL;
    f->statements = NULL;

    f->is_proto = 0;
    f->lineno = lineno;

    // mode 4
    f->depth = 0;
    f->max = 0;
    return f;
}

void free_function_ast(void *p) {
    if (!p)
        return;
    Function *f = (Function *)p;
    // print(">>>>>>>>free_function_ast 1\n");
    free(f->return_type);
    // print(">>>>>>>>free_function_ast 2\n");
    free(f->name);
    // print(">>>>>>>>free_function_ast 3\n");
    list_destroy(f->parameters);
    
    // print(">>>>>>>>free_function_ast 4\n");
    map_free(f->local_var_map);
    
    // print(">>>>>>>>free_function_ast 5\n");
    list_destroy(f->local_structs);
    // print(">>>>>>>>free_function_ast 6\n");
    list_destroy(f->local_vars);
    // print(">>>>>>>>free_function_ast 7\n");
    list_destroy(f->statements);
    // print(">>>>>>>>free_function_ast 8\n");

    free(p);
    // print(">>>>>>>>free_function_ast 9\n");
}