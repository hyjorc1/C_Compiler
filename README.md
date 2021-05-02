## Building, Cleaning, and Testing

This project is a C compiler implemented in C(clang 12.0.0), FLex(2.6.4), and GNU Bison(3.7.5).

1. `make` builds both the documentation `developers.pdf` and the executable compiler `mycc`.

2. `make clean` removes all generated files.

3. `make test` tests mode (1 - 4). For testing mode X only then `make testX`.

NOTE: The `Makefile` only works for linux like system (tested under Mac OS X 10.15.7).

## New Features

1. **Executable Compiler**
   - `mycc -mode [-o outfile] [infile] ... [infile]`
     1. **Usage Info**: Command `mycc` will provide usage information.
     2. **Mode Switch**: This compiler contains 6 modes (0 - 5).
     3. **Output File**: If no output file is specified, then the output will be written to standard output.
     4. **Input Files**: Each mode (1 - 5) can process multiple input files.

2. **[Mode 0](./doc/post-0.pdf)**: This mode provides version information, which doesn't accept input file(s).

3. **[Mode 1](./doc/post-1.pdf)**: This mode provides a lexer to process input files. The compiler reads the specificized input file(s) and process tokens contained in the inputs. The output stream contains a line for each token, exactly of the form

   - **_filename_** line **_line number_** text ’**_text_**’ token **_TOKENNAME_**

   The input file(s) may be C header files, C source files, or arbitrary text files; in any case, the lexer will split the input stream into tokens and handle the [preprocessor features](./doc/mode1.md).

4. **[Mode 2](./doc/post-2.pdf)**: This mode utilizes a lexer and a parser to read the specified input file and check
   that the file has correct C syntax. If the input file is not syntactically correct, then display
   an appropriate error message. The implemented rules are [here](./doc/mode2.md).

5. **[Mode 3](./doc/post-3.pdf)**: When executed with a mode of 3, the compiler reads the specified input file and check that the file has correct C syntax, and perform type checking on all expressions.

6. **[Mode 4](./doc/post-4.pdf)**: The compiler reads the specified input file and check it for correctness (including type checking) as done in mode 3. If there are no errors, then the compiler  output ans equivalent Java assembly code consists of JVM instructions.

7. **[Mode 5](./doc/post-5.pdf)**: The compiler reads the specified input file and generates correct code for expressions (from mode 4), and for (possibly nested) branching statements and loops.

## Note

The project should be tested at `ssh usr@pyrite.cs.iastate.edu`.

The original repository: `https://git.linux.iastate.edu/hyj/540-project.git`.