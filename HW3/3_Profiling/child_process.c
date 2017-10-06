/*
* FileName        :    child_process.c
* Description     :    This file contains profiling of fork and exec system calls in the child's context.
*                        
* File Author Name:    Bhallaji Venkatesan 
* Tools used      :    gcc, gedit
* References      :    https://stackoverflow.com/questions/23417442/how-to-match-string-to-execvp-in-c
*
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/times.h>
#include <time.h>

int main(int argc , char **argv)
{
	clock_t end_time = 0;
	end_time = clock();
	printf("\nEntering Child Process\n");
	long int argument = atoi(argv[1]);
	printf("\nStart time of clock in parent is %lu CPU Clocks\n",argument);
	printf("\nClocks used by child process to startup after exec is  %lu CPU Clocks\n",end_time);
	return 0;
}