## My generic makefile written by Magnus Sörensen. GPL3.0 Lisense.

## CROSS_TOLL is used if you need co add a cross platform compiler.
CROSS_TOLL=
## CC is the compiler you use in this project.
CC=$(CROSS_TOLL) gcc -std=gnu99
CC_CPP=$(CROSS_TOLL) g++ -std=c++0x
TTY=/dev/pts/2
## Target is the source files with out .c or .cpp  tex main.c ~> main
TARGET_CLIENT=wrapper client
TARGET_CLIENT_CPP=
TARGET_SERVER=server
TARGET_SERVER_CPP=graphics
OBJECTS_CLIENT=$(TARGET_CLIENT:=.o)
OBJECTS_CLIENT_CPP=$(TARGET_CLIENT_CPP:=.o)
OBJECTS_SERVER=$(TARGET_SERVER:=.o)
OBJECTS_SERVER_CPP=$(TARGET_SERVER_CPP:=.o)
EXECFILE_CLIENT=client.out
EXECFILE_SERVER=server.out

## LFLAGS is the libary linker flags like -lncurses or -lpthread.
LFLAGS=-pthread -lrt -lsfml-graphics -lsfml-window -lsfml-system

#LFLAGS=-lncurses -lm
## CFLAGS tells the copmiler to compile with diffrent flaggs mostly -g -Wall
CFLAGS=-g -Wall
## If files is from windows then run
## recode ISO-8859-1..UTF-8 main.c
## or even better for file in *.{c,h} ; do recode ISO-8859-1..UTF-8 $file; done

## Also remember to create ctags in your src dir
##  $ ctags -R

.SUFFIXES:	.cpp
.cpp.o:
	$(CC_CPP) $(LFLAGS) $(CFLAGS) -c $<

.c.o:
	$(CC) $(LFLAGS) $(CFLAGS) -c $<

#all: $(OBJECTS_CLIENT) $(OBJECTS_CLIENT_CPP) $(OBJECTS_SERVER) $(OBJECTS_SERVER_CPP)
serv: $(OBJECTS_SERVER) $(OBJECTS_SERVER_CPP)
	$(CC_CPP) $(CFLAGS) $(LFLAGS) $(OBJECTS_SERVER) $(OBJECTS_SERVER_CPP) -o $(EXECFILE_SERVER)

cli: $(OBJECTS_CLIENT) $(OBJECTS_CLIENT_CPP)
	$(CC_CPP) $(CFLAGS) $(LFLAGS) $(OBJECTS_CLIENT) $(OBJECTS_CLIENT_CPP) -o $(EXECFILE_CLIENT)

all: serv cli

.PHONY: clean valgrind

clean:
	rm -f *.o $(EXECFILE_CLIENT) $(EXECFILE_SERVER) *.gch
