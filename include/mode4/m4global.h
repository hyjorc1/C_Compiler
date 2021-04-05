#ifndef M4_GLOBAL_H
#define M4_GLOBAL_H

#include "m3global.h"

extern const char *m4_class_name;

extern const char *global_var_tmp_file;
extern const char *global_var_clinit_tmp_file;
extern const char *global_method_tmp_file;
extern const char *global_exp_tmp_file;

extern char *ensemble_type_str(Type *t);

extern void m4preprocess();
extern void m4postprocess();

#endif