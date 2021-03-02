# 540-project

The project should be tested at `ssh usr@pyrite.cs.iastate.edu`.

## Building, Testing, and Cleaning
This project is implemented in C, FLex(2.6.4), and GNU Bison(3.7.5).

1. `make` will build both the documentation `developers.pdf` and the executable compiler `mycc`.

2. `make clean` will remove all generated files.

3. `make test` will test mode 1 and 2. For testing mode X only then `make testX`.

### New Features

1. **Executable Compiler**

   * `mycc -mode [-o outfile] [infile] ... [infile]`

      1. **Usage Information**: Command `mycc` will provide usage information.
      2. **The Mode Switch**: This compiler contains 6 modes (0 - 5).
      3. **The Output File**: If no output file is specified, then the output will be written to standard output.
      4. **Input Files**: Each mode (1 - 5) can process multiple input files.

   * **Note** that any incorrect input format will abort the execution and end with a error message or the usage information.

2. **Mode 0**: This mode provides version information, which doesn't accept input file(s).

3. **Mode 1**: This mode provides a lexer to process input files.

   * In mode 1, the compiler reads the specificized input file(s) and process tokens contained in the inputs. The output stream contains a line for each token, exactly of the form

      + **_filename_** line **_line number_** text ’**_text_**’ token **_TOKENNAME_**

   The input file(s) may be C header files, C source files, or arbitrary text files; in any case, the lexer will split the input stream into tokens and handle the preprocessor features.

   * **#include**
      + While processing input file A, if the lexer encounters a line `#include "B"` then the lexer will immediately begin processing file B. Once the end of file is reached on B, the lexer should continue processing file A where it left off.
   * **#define**
      + Your lexer maintains a set of defined preprocessor symbols. An input line of the form `#define identifier arbitrary text on one line` will define a symbol with name “identifier”. As long as this pre-processor symbol is defined, the text “identifier” is replaced by “arbitrary text on one line”.
   * **#ifdef**
      + Implement the `#ifdef`, `#ifndef`, `#else`, and `#endif` directives. These directives tell the lexer to process or ignore input based on whether a preprocessor symbol has been defined or not.

4. **Mode 2**: This mode utilizes a lexer and a parser to read the specified input file and check
that the file has correct C syntax. If the input file is not syntactically correct, then display
an appropriate error message. The implemented rules are:

   1. A C program is a sequence of zero or more (global) variable declarations, function prototypes, and function definitions, appearing in any order.
   2. A variable declaration is a type name, followed by a comma-separated list of one or more identifiers, each identifier optionally followed by a left bracket, an integer constant, and a right bracket. The list is terminated with a semicolon. Note that this restricts arrays to a single dimension.
   3. A type name is one of the simple types: void, char, int, float.
   4. A function prototype is a function declaration followed by a semicolon.
   5. A function declaration is a type name (the return type of the function), followed by an identifier (the name of the function), a left parenthesis, an optional comma-separated list of formal parameters, and a right parenthesis.
   6. A formal parameter is a type name, followed by an identifier, and optionally followed by a left and right bracket.
   7. A function definition is a function declaration followed by a left brace, a sequence of zero or more variable declarations, a sequence of zero or more statements, and a right brace. Note that this definition requires all variable declarations to appear before statements.
   8. A statement block is a left brace, a sequence of zero or more statements, and a right brace.
   9. A statement is one of the following.
      - An empty string followed by a semicolon.
      - An expression followed by a semicolon.
      - Keywords break or continue followed by a semicolon. Note: you do not need to check that these statements are within a loop.
      - Keyword return, followed by an optional expression, and a semicolon.
      - Keyword if, followed by a left parenthesis, an expression, and a right parenthesis, followed by either a statement block or a single statement followed by a semicolon. Then, optionally, the following: keyword else, followed by either a statement block, or a single statement followed by a semicolon.
      - Keyword for, followed by a left parenthesis, an optional expression, a semicolon, an optional expression, a semicolon, an optional expression, a right parenthesis, and then either a statement block, or a single statement followed by a semicolon.
      - Keyword while, followed by a left parenthesis, an expression, and a right parenthesis, and then either a statement block, or a single statement followed by a semicolon.
      - Keyword do, followed by either a statement block or a statement and a semicolon, followed by keyword while, a left parenthesis, an expression, a right parenthesis, and a semicolon.
   10. An expression is one of the following.
       - A literal (constant) value.
       - An identifier, left parenthesis, a comma-separated list of zero or more expressions, and a right parenthesis.
       - An l-value.
       - An l-value, an assignment operator, and an expression.
       - An l-value, preceeded by or followed by the increment or decrement operator.
       - A unary operator, and an expression.
       - An expression, a binary operator, and an expression.
       - An expression, a question mark, an expression, a colon, and an expression.
       - A left parenthesis, a type name, a right parenthesis, and an expression.
       - A left parenthesis, an expression, and a right parenthesis.
   11. An l-value is an identifier, optionally followed by a left bracket, an expression, and a right bracket. Note that this restricts array access to a single dimension.
   12. Unary operators (for any expression) are: -, !, ~
   13. Binary operators are: ==, !=, >, >=, <, <=, +, -, \*, /, %, |, &, ||, &&
   14. Assignment operators are: =, +=, -=, \*=, /=

