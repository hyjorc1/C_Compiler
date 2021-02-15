# 540-project

The project should be tested at `ssh usr@pyrite.cs.iastate.edu`.

## Building, Testing, and Cleaning

1. `make` will build both the documentation `developers.pdf` and the executable compiler `mycc`.

2. `make clean` will remove all generated files.
   
3. `make test` will test mode 1.

### New Features
1. **Executable Compiler**

   1. `mycc -mode [-o outfile] [infile] ... [infile]`
      1. **Usage Information**: Command `mycc` will provide usage information.
      2. **The Mode Switch**: This compiler contains 6 modes (0 - 5).
      3. **The Output File**: If no output file is specified, then the output will be written to standard output.
      4. **Input Files**: Each mode (1 - 5) can process multiple input files.
   
   2. **Note** that any incorrect input format will abort the execution and end with a error message or the usage information.

2. **Mode 0**: This mode provides version information, which doesn't accept input file(s).

3. **Mode 1**: This mode provides a lexer built with FLex (2.6.4) to process input files.
   1. In mode 1, the compiler reads the specificized input file(s) and process tokens contained in the inputs. The output stream contains a line for each token, exactly of the form 
   
      1. ***filename*** line ***line number*** text ’***text***’ token ***TOKENNAME***
   
   The input file(s) may be C header files, C source files, or arbitrary text files; in any case, the lexer will split the input stream into tokens and handle the preprocessor features.

   2. **#include** 
      1. While processing input file A, if the lexer encounters a line `#include "B"` then the lexer will immediately begin processing file B. Once the end of file is reached on B, the lexer should continue processing file A where it left off.
   3. **#define**
      1. Your lexer maintains a set of defined preprocessor symbols. An input line of the form `#define identifier arbitrary text on one line` will define a symbol with name “identifier”. As long as this pre-processor symbol is defined, the text “identifier” is replaced by “arbitrary text on one line”.
   4. **#ifdef**
      1. Implement the `#ifdef`, `#ifndef`, `#else`, and `#endif` directives. These directives tell the lexer to process or ignore input based on whether a preprocessor symbol has been defined or not.





