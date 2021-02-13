CXX = gcc
CXXFLAGS = 
#-Wall -Wextra -g
EXE = mode
LEX = lexer

all: lexer
	./$(EXE) d.c hello.c tricky.txt input3.txt tricky2.txt hello.c
# input1.txt input2.txt tricky.txt
# hello.c 
# tricky.txt input3.txt

lexer:
	flex -o $(LEX).yy.c $(LEX).l
	$(CXX) $(CXXFLAGS) -c $(LEX).yy.c -o $(LEX).o
	$(CXX) $(CXXFLAGS) -c $(EXE).c
	$(CXX) $(CXXFLAGS) -o $(EXE) $(EXE).o $(LEX).o

clean:
	rm $(EXE) $(EXE).o $(LEX).o $(LEX).yy.c
