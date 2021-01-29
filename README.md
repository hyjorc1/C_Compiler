# 540-project

Test project at `ssh hyj@pyrite.cs.iastate.edu`.

## Ease of Building and Cleaning

1. `make` will build both the documentation `developers.pdf` and the executable compiler `mycc`.

2. `make clean` will remove all generated files.

## PART 0

### New Features
1. **Executable Compiler**
   1. `mycc -mode [-o outfile] [infile] ... [infile]`
      1. **The Mode Switch** `-mode`
         1. Mode 0 provides version information.
         2. Modes 1 to 5 are not implemented yet.
      2. **The Output File** `[-o outfile]`
      3. **Input Files** `[infile]` (Currently only support one input file)
   
   
