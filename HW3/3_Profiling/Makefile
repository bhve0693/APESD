# @brief Makefile for compiling pthread_fork.c SW to test pthreads api's
# @Author Bhallaji Venkatesan 
# @Reference http://ecee.colorado.edu/~ecen5623/ecen/ex/Linux/Linux_TCP_Examples/Makefile


CC=gcc

CFLAGS= -O0 -g -w -pthread
OUTPUT= pthread_fork child_process

CFILES= pthread_fork.c child_process.c

SRCS= ${CFILES}
OBJS= $(CFILES:.c=.o)

all:	${OUTPUT}

clean:
	-rm -f *.o *.NEW *~ *.d
	-rm -f ${OUTPUT} ${GARBAGE}


pthread_fork:pthread_fork.o
	$(CC) $(CFLAGS) -o $@ pthread_fork.o $(LIBS)

child_process:child_process.o
	$(CC) $(CFLAGS) -o $@ child_process.o $(LIBS)


.c.o:
	$(CC) $(CFLAGS) -c $<
