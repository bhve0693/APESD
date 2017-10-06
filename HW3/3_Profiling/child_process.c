/*
* FileName        :    child_process.c
* Description     :    This file contains profiling of fork and exec system calls in the child's context.
*                        
* File Author Name:    Bhallaji Venkatesan 
* Tools used      :    gcc, gedit
* References      :    
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
	printf("\n Argument is %s\n",argv[1]);
	double argument = atof(argv[1]);
	printf("\nStart time of clock is %lu\n",argument);
	printf("\nEnd time of clock is %lu\n",end_time);

	printf("\n Fork Exec Profiling time is  %lf",(end_time -argument)/CLOCKS_PER_SEC);


	return 0;
}