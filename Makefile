
all: link 
# latex
# ./$(EXE) -1 ifdefs2.c

.PHONY: clean
clean: compiler-clean latex-clean

############################## compiler ###########################
CC 			:= gcc
CFLAGS		:= -Wall -Wextra -g
SRC			:= src
INCLUDE		:= include
INCLUDEDIRS := $(shell find $(INCLUDE) -type d)
INCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))

EXE 		:= mycc
MAIN		:= $(SRC)/$(EXE)
UTIL		:= $(SRC)/util
OBJ 		= $(MAIN).o $(UTIL).o $(OBJ1)

link: mycc $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXE) $(OBJ)
	@echo '>>>>>>>>>>>>>>>>>>>> Built mycc <<<<<<<<<<<<<<<<<<<<<<<'

mycc: $(MAIN).o $(UTIL).o mode1

compiler-clean: mode1-clean
	rm -rf $(MAIN).o $(UTIL).o $(EXE)
	@echo '================= Cleaned Compiler ===================='

#------------------------------ test -----------------------------#
TEST_CMD	:= ./Check.sh mycc -s *.c
# TEST_CMD	:= ./Check.sh mycc -d *.c

#------------------------------ mode 1 ---------------------------#
LEX1	:= $(SRC)/mode1/lexer
MODE1	:= $(SRC)/mode1/mode1
OBJ1 	:= $(LEX1).yy.o $(MODE1).o
TEST1	:= test/Grading1

test1: link
	@echo '@@@@@@@@@@@@@@@@@@@@ Mode1 Test @@@@@@@@@@@@@@@@@@@@@@@'
	cp $(EXE) $(TEST1) && cd $(TEST1) && $(TEST_CMD) && rm $(EXE) && cd ../../

mode1: $(LEX1).yy.o $(MODE1).o
	@echo '>>>>>>>>>>>>>>>>>>>> Built Mode1 <<<<<<<<<<<<<<<<<<<<<<'

$(LEX1).yy.c:
	flex -o $(LEX1).yy.c $(LEX1).l

mode1-clean:
	rm -rf $(LEX1).yy.c $(OBJ1)
	@echo '=================== Cleaned Mode1 ====================='

#------------------------------ mode 2 ---------------------------#



#----------------------- GNU auto variables ----------------------#
%.o: %.c
	@echo '>>>>>>>>>>>>>>>>>> auto .c to .o <<<<<<<<<<<<<<<<<<<<<<'
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

################################ latex ############################
latex:
	pdflatex developer.tex
	@echo '>>>>>>>>>>>>>>>>>>>> Built Latex <<<<<<<<<<<<<<<<<<<<<<'

latex-clean:
	rm -rf *.blg *.bbl *.aux *.log *.dvi *.vtc *.out *~ *.fls *.fdb_latexmk *.gz developer.pdf
	@echo '=================== Cleaned Latex ====================='