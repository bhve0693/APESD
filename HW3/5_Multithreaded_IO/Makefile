# @brief Makefile for compiling multithreaded_io.c SW to perform multi-threaded file IO
# @Author Bhallaji Venkatesan 
# @Reference http://ecee.colorado.edu/~ecen5623/ecen/ex/Linux/Linux_TCP_Examples/Makefile


CC=gcc

CFLAGS= -O0 -g -w -pthread
OUTPUT= multithreaded_io

CFILES= multithreaded_io.c

SRCS= ${CFILES}
OBJS= $(CFILES:.c=.o)

all:	${OUTPUT}

clean:
	-rm -f *.o *.NEW *~ *.d
	-rm -f ${OUTPUT} ${GARBAGE}


multithreaded_io:multithreaded_io.o
	$(CC) $(CFLAGS) -o $@ multithreaded_io.o $(LIBS)


.c.o:
	$(CC) $(CFLAGS) -c $<
