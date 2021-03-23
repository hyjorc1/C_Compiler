all: link latex
# ./$(EXE) -3 array1.c

.PHONY: clean
clean: compiler-clean latex-clean

test: link mode1-test mode2-test mode3-test

#=================================================================#
############################## compiler ###########################
#=================================================================#
CC 			:= gcc
CFLAGS		:= -Wall -Wextra -g
SRC			:= src
INCLUDE		:= include
INCLUDEDIRS := $(shell find $(INCLUDE) -type d)
INCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))

EXE 		:= mycc
MAIN		:= $(SRC)/$(EXE)
UTIL		:= $(SRC)/util
OBJ 		= $(MAIN).o $(UTIL).o $(OBJ1) $(OBJ2)  $(OBJ3)

link: mycc $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXE) $(OBJ)
	@echo '========================================================'
	@echo '>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Built mycc'
	@echo '========================================================'
	@echo ''
	@echo ''

mycc: $(MAIN).o $(UTIL).o mode1 mode2 mode3

compiler-clean: mode1-clean mode2-clean mode3-clean
	rm -rf $(MAIN).o $(UTIL).o $(EXE)
	@echo '================= Cleaned Compiler ===================='

#=================================================================#
#------------------------------ test -----------------------------#
#=================================================================#
TEST_CMD	:= ./Check.sh mycc -s *.c
# TEST_CMD	:= ./Check.sh mycc -d struct3.c

#=================================================================#
#------------------------------ mode 1 ---------------------------#
#=================================================================#
SRC1	:= $(SRC)/mode1
LEX1	:= $(SRC1)/lexer1
MODE1	:= $(SRC1)/mode1
OBJ1 	:= $(LEX1).yy.o $(MODE1).o
TEST1	:= test/Grading1

test1: link mode1-test

mode1-test:
	@echo '@@@@@@@@@@@@@@@@@@@@ Mode 1 Test @@@@@@@@@@@@@@@@@@@@@@@'
	cp $(EXE) $(TEST1) && cd $(TEST1) && $(TEST_CMD) && rm $(EXE) && cd ../../

mode1: $(OBJ1)
	@echo '========================================================'
	@echo '>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Built Mode 1'
	@echo '========================================================'
	@echo ''
	@echo ''

$(LEX1).yy.c:
	flex -o $(LEX1).yy.c $(LEX1).l

mode1-clean:
	rm -rf $(LEX1).yy.c $(OBJ1)
	@echo '=================== Cleaned Mode1 ====================='

#=================================================================#
#------------------------------ mode 2 ---------------------------#
#=================================================================#
SRC2	:= $(SRC)/mode2
LEX2	:= $(SRC2)/lexer2
PASER2	:= $(SRC2)/parser2
MODE2	:= $(SRC2)/mode2
OBJ2 	:= $(PASER2).tab.o $(LEX2).yy.o $(MODE2).o $(SRC2)/node_list.o $(SRC2)/struct_list.o $(SRC2)/func_list.o
TEST2	:= test/Grading2

test2: link mode2-test

mode2-test:
	@echo '@@@@@@@@@@@@@@@@@@@@ Mode 2 Test @@@@@@@@@@@@@@@@@@@@@@@'
	cp $(EXE) $(TEST2) && cd $(TEST2) && $(TEST_CMD) && rm $(EXE) && cd ../../

mode2: $(OBJ2)
	@echo '========================================================'
	@echo '>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Built Mode 2'
	@echo '========================================================'
	@echo ''
	@echo ''

$(PASER2).tab.h $(PASER2).tab.c: $(PASER2).y
	bison -d -o $(PASER2).tab.c $(PASER2).y

$(LEX2).yy.c: $(LEX2).l
	flex -o $(LEX2).yy.c $(LEX2).l

mode2-clean:
	rm -rf $(LEX2).yy.c $(PASER2).tab.* $(OBJ2)
	@echo '=================== Cleaned Mode2 ====================='

#=================================================================#
#------------------------------ mode 3 ---------------------------#
#=================================================================#
SRC3	:= $(SRC)/mode3
LEX3	:= $(SRC3)/lexer3
PASER3	:= $(SRC3)/parser3
MODE3	:= $(SRC3)/mode3
HAND3   := $(patsubst %.c,%.o,$(wildcard $(SRC3)/handler/*.c))
UTIL3   := $(patsubst %.c,%.o,$(wildcard $(SRC3)/util/*.c))
AST3    := $(patsubst %.c,%.o,$(wildcard $(SRC3)/ast/*.c))
OBJ3 	:= $(PASER3).tab.o $(LEX3).yy.o $(MODE3).o $(AST3) $(UTIL3) $(HAND3)
TEST3	:= test/Tests3

test3: link mode3-test

mode3-test:
	@echo '@@@@@@@@@@@@@@@@@@@@ Mode 3 Test @@@@@@@@@@@@@@@@@@@@@@@'
	cp $(EXE) $(TEST3) && cd $(TEST3) && $(TEST_CMD) && rm $(EXE) && cd ../../

mode3: $(OBJ3)
	@echo '========================================================'
	@echo '>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Built Mode 3'
	@echo '========================================================'
	@echo ''
	@echo ''

$(PASER3).tab.h $(PASER3).tab.c: $(PASER3).y
	bison -d -o $(PASER3).tab.c $(PASER3).y

$(LEX3).yy.c: $(LEX3).l
	flex -o $(LEX3).yy.c $(LEX3).l

mode3-clean:
	rm -rf $(LEX3).yy.c $(PASER3).tab.* $(OBJ3)
	@echo '=================== Cleaned Mode3 ====================='

#=================================================================#
#----------------------- GNU auto variables ----------------------#
#=================================================================#
%.o: %.c
	@echo '>>>>>>>>>>>>>>>>>> auto .c to .o <<<<<<<<<<<<<<<<<<<<<<'
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

#=================================================================#
################################ latex ############################
#=================================================================#
latex:
	pdflatex developer.tex
	@echo '>>>>>>>>>>>>>>>>>>>> Built Latex <<<<<<<<<<<<<<<<<<<<<<'

latex-clean:
	rm -rf *.blg *.bbl *.aux *.log *.dvi *.vtc *.out *~ *.fls *.fdb_latexmk *.gz developer.pdf
	@echo '=================== Cleaned Latex ====================='