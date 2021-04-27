#ifndef M4_GLOBAL_H
#define M4_GLOBAL_H

#include "m3global.h"

extern const char *m4_class_name;

extern const char *m4_gvar_tmp_file;
extern const char *m4_gvar_clinit_tmp_file;
extern const char *m4_method_tmp_file;
extern const char *m4_exp_tmp_file;
extern const char *m4_stmt_tmp_file;

extern char *last_exp_inst;

/* mode 4 utilties */

extern int update_depth(int num);

extern void char2int(Type *t);

extern void copy_files(FILE *dest, const char *src_file);

extern char *to_ensembly_binary_op_str(char *op);
extern char *to_ensembly_type_str(Type *t);
extern char *to_ensembly_T_str1(Type *t);
extern char *to_ensembly_T_str2(Type *t);

extern void m4preprocess();
extern void m4process(char *argv[], int i);
extern void m4postprocess();

/* mode 4 print assembly code */
void print_bytecode_class();
void print_file_content(const char *file_name);
void print_bytecode_global_vars();
void print_bytecode_default_constructor();
void print_bytecode_methods();
void print_bytecode_java_main();

#endif