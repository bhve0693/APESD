# @brief Makefile for compiling doublelinkedlist and circular buffer
#        Folder structure -> Source Files in /src directory
#                         -> Header Files in /inc directory 
#                         -> Output executables in Makefile directory
# @Author Bhallaji Venkatesan 
# @Reference http://ecee.colorado.edu/~ecen5623/ecen/ex/Linux/Linux_TCP_Examples/Makefile

INCLUDE_DIRS = -Iinc
CC=gcc

CFLAGS= -O0 -g -w $(INCLUDE_DIRS) 
OUTPUT= dllist
SOURCE_DIRS = src
HFILES= doublelinkedlist.h
CFILES= doublelinkedlist.c

SRCS= ${HFILES} ${SOURCE_DIRS}/${CFILES}
OBJS= ${SOURCE_DIRS}/doublelinkedlist.o

all:	${OUTPUT}

clean:
	-rm -f *.o *.NEW *~ *.d
	-rm -f ${OUTPUT} ${GARBAGE}

dllist:doublelinkedlist.o
	$(CC) $(CFLAGS) -o $@ doublelinkedlist.o $(LIBS)


.c.o:
	$(CC) $(CFLAGS) -c $<
