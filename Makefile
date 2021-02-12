
########################## general targets ########################
all: project latex
# @echo Executing target 'all' complete!

run: project
	./$(MAIN)

test: project
	./$(MAIN) test

.PHONY: clean
clean: project-clean latex-clean

############################# project #############################
CXX			 = g++ # define the Cpp compiler to use
CXXFLAGS	:= -std=c++14 -Wall -Wextra -g # define any compile-time flags
LFLAGS 		 =
OUTPUT		:= output # define output directory
SRC			:= src # define source directory
INCLUDE		:= include # define include directory
LIB			:= lib # define lib directory

ifeq ($(OS),Windows_NT)
MAIN	    := mycc.exe
SOURCEDIRS	:= $(SRC)
INCLUDEDIRS	:= $(INCLUDE)
LIBDIRS		:= $(LIB)
FIXPATH      = $(subst /,\,$1)
RM			:= del /q /f
MD	        := mkdir
else
MAIN	    := mycc
SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
LIBDIRS		:= $(shell find $(LIB) -type d)
FIXPATH      = $1
RM =        rm -f
MD	        := mkdir -p
endif

INCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%)) # define any directories containing header files other than /usr/include
LIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%)) # define the C libs
SOURCES		:= $(wildcard $(patsubst %,%/*.cpp, $(SOURCEDIRS))) # define the C source files
OBJECTS		:= $(SOURCES:.cpp=.o) # define the C object files 

project: $(MAIN)

$(MAIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(MAIN) $(OBJECTS) $(LFLAGS) $(LIBS)
	@echo Executing target '$(MAIN)' complete! $(OBJECTS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<  -o $@
	@echo Executing target '.cpp.o' complete!

project-clean:
	$(RM) $(call FIXPATH,$(OBJECTS)) $(MAIN) 
	$(RM) lexer.yy.cc lexer.o
# @echo Cleaned project!

lexer: lexer.l
	flex --outfile=lexer.yy.cc  $<
	g++  -Wno-deprecated-register -O0  -g -Wall -std=c++14 -c lexer.yy.cc -o lexer.o

################################ latex ############################
DOC = developer
LATEX = pdflatex
latex:
	$(LATEX) $(DOC).tex
latex-clean:
	$(RM) *.blg *.bbl *.aux *.log *.dvi *.vtc *.out *~ *.fls *.fdb_latexmk *.gz $(DOC).pdf