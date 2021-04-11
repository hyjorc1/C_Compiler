#ifndef M4_GLOBAL_H
#define M4_GLOBAL_H

#include "m3global.h"

extern const char *m4_class_name;

extern const char *m4_gvar_tmp_file;
extern const char *m4_gvar_clinit_tmp_file;
extern const char *m4_method_tmp_file;
extern const char *m4_exp_tmp_file;
extern const char *m4_stmt_tmp_file;

extern const char *ident4;
extern const char *ident8;

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
extern void m4postprocess();

#endif