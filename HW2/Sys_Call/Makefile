# @brief Makefile for compiling testsyscall.c SW to test rand_sort syscall
# @Author Bhallaji Venkatesan 
# @Reference http://ecee.colorado.edu/~ecen5623/ecen/ex/Linux/Linux_TCP_Examples/Makefile


CC=gcc

CFLAGS= -O0 -g -w 
OUTPUT= testsyscall

CFILES= testsyscall.c

SRCS= ${CFILES}
OBJS= $(CFILES:.c=.o)

all:	${OUTPUT}

clean:
	-rm -f *.o *.NEW *~ *.d
	-rm -f ${OUTPUT} ${GARBAGE}


testsyscall:testsyscall.o
	$(CC) $(CFLAGS) -o $@ testsyscall.o $(LIBS)


.c.o:
	$(CC) $(CFLAGS) -c $<
