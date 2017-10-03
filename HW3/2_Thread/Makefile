# @brief Makefile for compiling threadapi_demo.c SW to test pthreads and kthreads api's
# @Author Bhallaji Venkatesan 
# @Reference http://ecee.colorado.edu/~ecen5623/ecen/ex/Linux/Linux_TCP_Examples/Makefile


CC=gcc

CFLAGS= -O0 -g -w -pthreads
OUTPUT= thread

CFILES= threadapi_demo.c

SRCS= ${CFILES}
OBJS= $(CFILES:.c=.o)

all:	${OUTPUT}

clean:
	-rm -f *.o *.NEW *~ *.d
	-rm -f ${OUTPUT} ${GARBAGE}


threadapi_demo:threadapi_demo.o
	$(CC) $(CFLAGS) -o $@ threadapi_demo.o $(LIBS)


.c.o:
	$(CC) $(CFLAGS) -c $<
