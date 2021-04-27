NAME := user4

all: link
	./$(EXE) -5 $(NAME).c

jassemble: link
	./$(EXE) -5 -o $(NAME).j $(NAME).c
	./test/Krakatau/assemble.py $(NAME).j
	java $(NAME)

.PHONY: clean
clean: compiler-clean latex-clean

test: link mode1-test mode2-test mode3-test mode4-test

#=================================================================#
################################ latex ############################
#=================================================================#
latex:
	pdflatex developer.tex
	@echo '>>>>>>>>>>>>>>>>>>>> Built Latex <<<<<<<<<<<<<<<<<<<<<<'

latex-clean:
	rm -rf *.blg *.bbl *.aux *.log *.dvi *.vtc *.out *~ *.fls *.fdb_latexmk *.gz developer.pdf
	@echo '=================== Cleaned Latex ====================='

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
OBJ 		= $(MAIN).o $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) $(OBJ5)

link: mycc $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXE) $(OBJ)
	@echo '========================================================'
	@echo '>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Built mycc'
	@echo '========================================================'
	@echo ''
	@echo ''

mycc: $(MAIN).o mode1 mode2 mode3 mode4 mode5

compiler-clean: mode1-clean mode2-clean mode3-clean mode4-clean mode5-clean
	rm -rf $(MAIN).o $(EXE)
	@echo '================= Cleaned Compiler ===================='

#=================================================================#
#------------------------------ test -----------------------------#
#=================================================================#
TEST_CMD	:= ./Check.sh mycc -s *.c
# TEST_CMD	:= ./Check.sh mycc -d struct*.c

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
TEST3	:= test/Grading3

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
#------------------------------ mode 4 ---------------------------#
#=================================================================#
SRC4	:= $(SRC)/mode4
MODE4	:= $(SRC4)/mode4
UTIL4   := $(patsubst %.c,%.o,$(wildcard $(SRC4)/util/*.c))
OBJ4 	:= $(MODE4).o $(UTIL4)
TMP4	:= m4_gvar_tmp_tmp m4_gvar_clinit_tmp m4_method_tmp_tmp m4_exp_tmp m4_stmt_tmp
TEST4	:= test/Grading4
T4_OWN	:= test/Tests4
T4_RUN	:= ./Run.sh mycc -s *.c
T4_USR	:= ./CheckUser.sh mycc user*.c
T4_JXP	:= ./CheckJexpr.sh mycc *.c

test4: link mode4-test

mode4-test:
	@echo '@@@@@@@@@@@@@@@@@@@@ Mode 4 Test @@@@@@@@@@@@@@@@@@@@@@@'
	cp $(EXE) $(T4_OWN) && cd $(T4_OWN) && $(T4_RUN) && rm $(EXE) && cd ../../
	cp $(EXE) $(TEST4) && cd $(TEST4) && $(T4_RUN) && rm $(EXE) && cd ../../
	cp $(EXE) $(TEST4) && cd $(TEST4) && $(T4_USR) && rm $(EXE) && cd ../../
# cp $(EXE) $(TEST4) && cd $(TEST4) && $(T4_JXP) && rm $(EXE) && cd ../../

mode4: $(OBJ4)
	@echo '========================================================'
	@echo '>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Built Mode 4'
	@echo '========================================================'
	@echo ''
	@echo ''

mode4-clean:
	rm -rf $(OBJ4) $(TMP4)
	@echo '=================== Cleaned Mode4 ====================='

#=================================================================#
#------------------------------ mode 5 ---------------------------#
#=================================================================#
SRC5	:= $(SRC)/mode5
MODE5	:= $(SRC5)/mode5
UTIL5   := $(patsubst %.c,%.o,$(wildcard $(SRC5)/util/*.c))
OBJ5 	:= $(MODE5).o $(UTIL5)
TEST5	:= test/Grading5

test5: link mode5-test

mode5-test:
	@echo '@@@@@@@@@@@@@@@@@@@@ Mode 5 Test @@@@@@@@@@@@@@@@@@@@@@@'
# cp $(EXE) $(T5_OWN) && cd $(T5_OWN) && $(T5_RUN) && rm $(EXE) && cd ../../
# cp $(EXE) $(TEST5) && cd $(TEST5) && $(T5_RUN) && rm $(EXE) && cd ../../
# cp $(EXE) $(TEST5) && cd $(TEST5) && $(T5_USR) && rm $(EXE) && cd ../../
# cp $(EXE) $(TEST5) && cd $(TEST5) && $(T5_JXP) && rm $(EXE) && cd ../../

mode5: $(OBJ5)
	@echo '========================================================'
	@echo '>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Built Mode 5'
	@echo '========================================================'
	@echo ''
	@echo ''

mode5-clean:
	rm -rf $(OBJ5) $(TMP5)
	@echo '=================== Cleaned Mode5 ====================='

#=================================================================#
#----------------------- GNU auto variables ----------------------#
#=================================================================#
%.o: %.c
	@echo '>>>>>>>>>>>>>>>>>> auto .c to .o <<<<<<<<<<<<<<<<<<<<<<'
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

