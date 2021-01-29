
########################## general targets ########################

all: project latex
# @echo Executing target 'all' complete!

.PHONY: clean
# @echo Executing target '.PHONY' complete!

clean: project-clean latex-clean

run: project
	./$(MAIN)

test: project
	./$(MAIN) test

############################# project #############################

# define the Cpp compiler to use
CXX = g++
# define any compile-time flags
CXXFLAGS	:= -std=c++17 -Wall -Wextra -g
# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS =
# define output directory
OUTPUT	:= output
# define source directory
SRC		:= src
# define include directory
INCLUDE	:= include
# define lib directory
LIB		:= lib

ifeq ($(OS),Windows_NT)
MAIN	:= mycc.exe
SOURCEDIRS	:= $(SRC)
INCLUDEDIRS	:= $(INCLUDE)
LIBDIRS		:= $(LIB)
FIXPATH = $(subst /,\,$1)
RM			:= del /q /f
MD	:= mkdir
else
MAIN	:= mycc
SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
LIBDIRS		:= $(shell find $(LIB) -type d)
FIXPATH = $1
RM = rm -f
MD	:= mkdir -p
endif

# define any directories containing header files other than /usr/include
INCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))
# define the C libs
LIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))
# define the C source files
SOURCES		:= $(wildcard $(patsubst %,%/*.cpp, $(SOURCEDIRS)))
# define the C object files 
OBJECTS		:= $(SOURCES:.cpp=.o)

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#
# OUTPUTMAIN	:= $(call FIXPATH,$(OUTPUT)/$(MAIN))

project: $(OUTPUT) $(MAIN)
# @echo Built project!

$(OUTPUT):
	$(MD) $(OUTPUT)
# @echo Executing target '$(OUTPUT)' complete!

$(MAIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(MAIN) $(OBJECTS) $(LFLAGS) $(LIBS)
# @echo Executing target '$(MAIN)' complete!

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<  -o $@
# @echo Executing target '.cpp.o' complete!

project-clean:
	$(RM) $(call FIXPATH,$(OBJECTS)) $(MAIN)
# @echo Cleaned project!

################################ latex ############################

DOC = developer
LATEX = pdflatex

latex:
	$(LATEX) $(DOC).tex

latex-clean:
	$(RM) *.blg *.bbl *.aux *.log *.dvi *.vtc *.out *~ *.fls *.fdb_latexmk *.gz $(DOC).pdf