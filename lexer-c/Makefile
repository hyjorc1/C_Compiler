CXX = g++
CXXFLAGS = -Wno-deprecated-register -O0 -std=c++14 -Wall -Wextra -g -ggdb
EXE = mode
LEX = lexer
SCAN = scanner

# echo '1 + 2 * 3' | ./wimpy

# wimpy: wimpy.o lexer.o
# 	$(CXX) $(CXXFLAGS) -o wimpy wimpy.o lexer.o

# wimpy.o: wimpy.cpp tokens.h
# 	$(CXX) $(CXXFLAGS) -c wimpy.cpp

# lexer.o: lexer.cc tokens.h
# 	$(CXX) $(CXXFLAGS) -c lex.yy.cc -o lexer.o

# lexer.cc: lexer.l
# 	flex -o lex.yy.cc lexer.l


all: lexer
	./$(EXE) input1.txt
# input2.txt hello.c tricky.txt input3.txt

lexer:
	flex -o $(LEX).yy.cc $(LEX).l
	$(CXX) $(CXXFLAGS) -c $(LEX).yy.cc -o $(LEX).o
	$(CXX) $(CXXFLAGS) -c $(EXE).cpp
	$(CXX) $(CXXFLAGS) -c $(SCAN).cpp
	$(CXX) $(CXXFLAGS) -o $(EXE) $(EXE).o $(LEX).o $(SCAN).o

clean:
	rm $(EXE) $(EXE).o $(LEX).o $(SCAN).o $(LEX).yy.cc
