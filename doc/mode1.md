# Mode 1 Preprocessor Features

- **#include** + While processing input file A, if the lexer encounters a line `#include "B"` then the lexer will immediately begin processing file B. Once the end of file is reached on B, the lexer should continue processing file A where it left off.
- **#define** + Your lexer maintains a set of defined preprocessor symbols. An input line of the form `#define identifier arbitrary text on one line` will define a symbol with name “identifier”. As long as this pre-processor symbol is defined, the text “identifier” is replaced by “arbitrary text on one line”.
- **#ifdef** + Implement the `#ifdef`, `#ifndef`, `#else`, and `#endif` directives. These directives tell the lexer to process or ignore input based on whether a preprocessor symbol has been defined or not.
