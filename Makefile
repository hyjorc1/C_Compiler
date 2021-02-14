CC 		:= gcc
CFLAGS	:= -Wall -Wextra -g
LFLAGS 	:=
SRC		:= src
INCLUDE	:= include
LIB		:= lib

EXE 	:= main
LEX1	:= $(SRC)/lexer
MAIN	:= $(SRC)/$(EXE)
UTIL	:= $(SRC)/util

INCLUDEDIRS := $(shell find $(INCLUDE) -type d)
LIBDIRS		:= $(shell find $(LIB) -type d)

INCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))
LIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))


all: link
	./$(EXE) hello.c tricky.txt d.c defines.c

################################ project ############################
link: compile
	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXE) $(LEX1).o $(MAIN).o $(UTIL).o $(LIBS)

compile: lexer
	$(CC) $(CFLAGS) $(INCLUDES) -c $(LEX1).yy.c -o $(LEX1).o

	$(CC) $(CFLAGS) $(INCLUDES) -c $(MAIN).c -o $(MAIN).o
	$(CC) $(CFLAGS) $(INCLUDES) -c $(UTIL).c -o $(UTIL).o

lexer:
	flex -o $(LEX1).yy.c $(LEX1).l

.PHONY: clean
clean: latex-clean
	rm -rf $(SRC)/*.o $(SRC)/*.yy.c $(EXE)


################################ latex ############################
latex:
	pdflatex developer.tex
latex-clean:
	rm -rf *.blg *.bbl *.aux *.log *.dvi *.vtc *.out *~ *.fls *.fdb_latexmk *.gz developer.pdf