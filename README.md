# 540-project

The project should be tested at `ssh usr@pyrite.cs.iastate.edu`.

Original repository: `https://git.linux.iastate.edu/hyj/540-project.git`.

## Building, Testing, and Cleaning

This project is implemented in C(clang 12.0.0), FLex(2.6.4), and GNU Bison(3.7.5).

1. `make` builds both the documentation `developers.pdf` and the executable compiler `mycc`.

2. `make clean` removes all generated files.

3. `make test` tests mode 1 and 2. For testing mode X only then `make testX`.

### New Features

1. **Executable Compiler**
   - `mycc -mode [-o outfile] [infile] ... [infile]`
     1. **Usage Info**: Command `mycc` will provide usage information.
     2. **Mode Switch**: This compiler contains 6 modes (0 - 5).
     3. **Output File**: If no output file is specified, then the output will be written to standard output.
     4. **Input Files**: Each mode (1 - 5) can process multiple input files.

2) **Mode 0**: This mode provides version information, which doesn't accept input file(s).

3. **Mode 1**: This mode provides a lexer to process input files. The compiler reads the specificized input file(s) and process tokens contained in the inputs. The output stream contains a line for each token, exactly of the form

   - **_filename_** line **_line number_** text ’**_text_**’ token **_TOKENNAME_**

   The input file(s) may be C header files, C source files, or arbitrary text files; in any case, the lexer will split the input stream into tokens and handle the [preprocessor features](./doc/mode1.md).

4) **Mode 2**: This mode utilizes a lexer and a parser to read the specified input file and check
   that the file has correct C syntax. If the input file is not syntactically correct, then display
   an appropriate error message. The implemented rules are [here](./doc/mode2.md).
