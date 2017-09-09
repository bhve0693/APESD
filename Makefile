# @brief Makefile for compiling doublelinkedlist and circular buffer
#        Folder structure -> Source Files in /src directory
#                         -> Header Files in /inc directory 
#                         -> Output executables in Makefile directory
# @Author Bhallaji Venkatesan 
# @Reference http://ecee.colorado.edu/~ecen5623/ecen/ex/Linux/Linux_TCP_Examples/Makefile

INCLUDE_DIRS = -Iinc
CC=gcc

CFLAGS= -O0 -g -w $(INCLUDE_DIRS) 
OUTPUT= cbuf dllist
SOURCE_DIRS = src
HFILES= circularbuffer.h doublelinkedlist.h
CFILES= circualrbuffer.c doublelinkedlist.c

SRCS= ${HFILES} ${CFILES}
OBJS= $(CFILES:.c=.o)

all:	${OUTPUT}

clean:
	-rm -f *.o *.NEW *~ *.d
	-rm -f ${OUTPUT} ${GARBAGE}
cbuf:circularbuffer.o
	$(CC) $(CFLAGS) -o $@ circularbuffer.o $(LIBS)

dllist:doublelinkedlist.o
	$(CC) $(CFLAGS) -o $@ doublelinkedlist.o $(LIBS)


.c.o:
	$(CC) $(CFLAGS) -c $<
