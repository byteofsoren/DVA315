## My generic makefile written by Magnus Sörensen. GPL3.0 Lisense.

## CROSS_TOLL is used if you need co add a cross platform compiler.
CROSS_TOLL=
## CC is the compiler you use in this project.
CC=$(CROSS_TOLL) g++
TTY=/dev/pts/2
## Target is the source files with out .c or .cpp  tex main.c ~> main
TARGET_CLIENT=client wrapper
TARGET_SERVER=server wrapper
OBJECTS_CLIENT=$(TARGET_CLIENT:=.o) 
OBJECTS_SERVER=$(TARGET_SERVER:=.o)
EXECFILE_CLIENT=client.out
EXECFILE_SERVER=server.out

## LFLAGS is the libary linker flags like -lncurses or -lpthread.
LFLAGS=-pthread -lrt
#LFLAGS=-lncurses -lm
## CFLAGS tells the copmiler to compile with diffrent flaggs mostly -g -Wall
CFLAGS=-g -Wall
## If files is from windows then run
## recode ISO-8859-1..UTF-8 main.c
## or even better for file in *.{c,h} ; do recode ISO-8859-1..UTF-8 $file; done

## Also remember to create ctags in your src dir
##  $ ctags -R

$(TARGET_SERVER):
	$(CC) $(CFLAGS) $(LFLAGS) -c $@.c

server: $(TARGET_SERVER)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJECTS_SERVER) -o $(EXECFILE_SERVER)

$(TARGET_CLIENT):
	$(CC) $(CFLAGS) $(LFLAGS) -c $@.c

client: $(TARGET_CLIENT)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJECTS_CLIENT) -o $(EXECFILE_CLIENT)

.PHONY: clean valgrind

clean:
	rm -f *.o $(EXECFILE_CLIENT) $(EXECFILE_SERVER) *.gch
