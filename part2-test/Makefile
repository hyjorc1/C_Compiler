
all: wimpy1 calc 
# tree

clean:
	rm -rf *.yy.* *.tab.* *.o wimpy1 calc

wimpy1: wimpy1.tab.o wimpy1.yy.o
	gcc -o wimpy1 wimpy1.tab.o wimpy1.yy.o

wimpy1.tab.h wimpy1.tab.c: wimpy1.y
	bison -d wimpy1.y

wimpy1.yy.c: wimpy1.l
	flex -o wimpy1.yy.c wimpy1.l


calc: calc.tab.o calc.yy.o
	gcc -o calc calc.tab.o calc.yy.o

calc.tab.h calc.tab.c: calc.y
	bison -d calc.y

calc.yy.c: calc.l
	flex -o calc.yy.c calc.l


tree: tree.tab.o tree.yy.o parse.o
	gcc -o tree tree.tab.o tree.yy.o parse.o

tree.tab.h tree.tab.c: tree.y
	bison -d tree.y

tree.yy.c: tree.l
	flex -o tree.yy.c tree.l


%.o: %.c
	gcc -Wall -c $<

# dependencies

wimpy1.yy.o: wimpy1.tab.h
wimpy1.tab.o: wimpy1.tab.h

calc.yy.o: calc.tab.h
calc.tab.o: calc.tab.h

tree.yy.o: tree.tab.h 
tree.tab.o: tree.tab.h parse.h

