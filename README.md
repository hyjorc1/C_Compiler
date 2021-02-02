# 540-project

Test project at `ssh hyj@pyrite.cs.iastate.edu`.

## Ease of Building and Cleaning

1. `make` will build both the documentation `developers.pdf` and the executable compiler `mycc`.

2. `make clean` will remove all generated files.

## PART 0

### New Features
1. **Executable Compiler**

   1. `mycc -mode [-o outfile] [infile] ... [infile]`
      1. **The Mode Switch** (`-mode`)
         1. The mode is an integer from 0 to 5, and corresponds to each part of the project. Mode 0 provides version information. Currently, modes 1 to 5 are not implemented yet.
      2. **The Output File** (`[-o outfile]`)
         1. If no output file is specified, then the output should be written to standard output. Otherwise, output should be written to the specified output file.
      3. **Input Files** (`[infile]`)
         1. Each mode (1 - 5) can process a single input file.
   
   2. Note that any incorrect input format will abort the execution and end with a error message or the usage information.
   
   
