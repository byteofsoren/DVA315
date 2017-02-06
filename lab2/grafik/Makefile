## My generic makefile written by Magnus Sörensen. GPL3.0 Lisense.

## CROSS_TOLL is used if you need co add a cross platform compiler.
CROSS_TOLL=
## CC is the compiler you use in this project.
CC=$(CROSS_TOLL) g++
TTY=/dev/pts/2
## Target is the source files with out .c or .cpp  tex main.c ~> main
TARGET_C=
TARGET_CPP=main grafik 
OBJECTS_C=$(TARGET_C:=.o)
OBJECTS_CPP=$(TARGET_CPP:=.o)
## EXECFILE is the name on the exe file you want
EXECFILE=prog.out
## LFLAGS is the libary linker flags like -lncurses or -lpthread.
LFLAGS_C=
LFLAGS_CPP=-std=c++0x -lSDL2 -lSDL_ttf 
#LFLAGS=-lncurses -lm
## CFLAGS tells the copmiler to compile with diffrent flaggs mostly -g -Wall
FLAGS_C=-g -Wall
FLAGS_CPP=-g -Wall
## If files is from windows then run
## recode ISO-8859-1..UTF-8 main.c
## or even better for file in *.{c,h} ; do recode ISO-8859-1..UTF-8 $file; done
## Also remember to create ctags in your src dir
##  $ ctags -R

$(TARGET_C):
	$(CC) $(FLAGS_C) $(LFLAGS_C) -c $@.c

$(TARGET_CPP):
	$(CC) $(FLAGS_CPP) $(LFLAGS_CPP) -c $@.cpp

all: clean $(TARGET_CPP) $(TARGET_C)
	$(CC)  $(LFLAGS_CPP) $(FLAGS_CPP) $(OBJECTS_CPP) $(OBJECTS_C) -o $(EXECFILE)

run: clean all
	./$(EXECFILE)

debug: clean all
	cgdb ./$(EXECFILE)

ddd: clean all
	ddd ./$(EXECFILE) &

.PHONY: clean valgrind

valgrind: clean all
	valgrind ./$(EXECFILE)

clean:
	rm -f *.o $(EXECFILE) *.gch
