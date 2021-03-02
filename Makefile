all: link
	./$(EXE) -2 extra.c
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
OBJ 		= $(MAIN).o $(UTIL).o $(OBJ1) $(OBJ2)

link: mycc $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXE) $(OBJ)
	@echo '>>>>>>>>>>>>>>>>>>>> Built mycc <<<<<<<<<<<<<<<<<<<<<<<'

mycc: $(MAIN).o $(UTIL).o mode1 mode2

compiler-clean: mode1-clean mode2-clean
	rm -rf $(MAIN).o $(UTIL).o $(EXE)
	@echo '================= Cleaned Compiler ===================='

#------------------------------ test -----------------------------#
TEST_CMD	:= ./Check.sh mycc -s *.c
# TEST_CMD	:= ./Check.sh mycc -d *.c

#------------------------------ mode 1 ---------------------------#
SRC1	:= $(SRC)/mode1
LEX1	:= $(SRC1)/lexer1
MODE1	:= $(SRC1)/mode1
OBJ1 	:= $(LEX1).yy.o $(MODE1).o
TEST1	:= test/Grading1

test1: link
	@echo '@@@@@@@@@@@@@@@@@@@@ Mode1 Test @@@@@@@@@@@@@@@@@@@@@@@'
	cp $(EXE) $(TEST1) && cd $(TEST1) && $(TEST_CMD) && rm $(EXE) && cd ../../

mode1: $(OBJ1)
	@echo '>>>>>>>>>>>>>>>>>>>> Built Mode1 <<<<<<<<<<<<<<<<<<<<<<'

$(LEX1).yy.c:
	flex -o $(LEX1).yy.c $(LEX1).l

mode1-clean:
	rm -rf $(LEX1).yy.c $(OBJ1)
	@echo '=================== Cleaned Mode1 ====================='

#------------------------------ mode 2 ---------------------------#
SRC2	:= $(SRC)/mode2
LEX2	:= $(SRC2)/lexer2
PASER2	:= $(SRC2)/parser2
MODE2	:= $(SRC2)/mode2
OBJ2 	:= $(PASER2).tab.o $(LEX2).yy.o $(MODE2).o $(SRC2)/node_list.o $(SRC2)/struct_list.o $(SRC2)/func_list.o
TEST2	:= test/Test2

mode2: $(OBJ2)
	@echo '>>>>>>>>>>>>>>>>>>>> Built Mode2 <<<<<<<<<<<<<<<<<<<<<<'

$(PASER2).tab.h $(PASER2).tab.c: $(PASER2).y
	bison -d -o $(PASER2).tab.c $(PASER2).y

$(LEX2).yy.c: $(LEX2).l
	flex -o $(LEX2).yy.c $(LEX2).l

mode2-clean:
	rm -rf $(LEX2).yy.c $(PASER2).tab.* $(OBJ2)
	@echo '=================== Cleaned Mode2 ====================='

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