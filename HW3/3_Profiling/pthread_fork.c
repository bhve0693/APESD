/*
* FileName        :    pthread_fork.c
* Description     :    This file contains profiling of pthread_create, fork and exec system calls.
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

void *profile_pthread(void *arg)
{
	int32_t *input = (int32_t*)arg;
	printf("\n Inisde Thread \n");
	pthread_exit(NULL);

}

int main()
{
  	clock_t start_time =0;
  	clock_t end_time = 0;
    pthread_attr_t attr;
  	pthread_t thread_profile;
  	int32_t profile_ptr;
    pid_t pid;
    char buffer[12];

  	if(pthread_attr_init(&attr))
    {
    		printf("\nERR:Thread attribute initialization Failed!\n");
      	return 1;
    }
     

  	start_time = clock();
  	if(pthread_create(&thread_profile, NULL, &profile_pthread, (void *)profile_ptr))
    {
    		printf("\nERR:Thread Creation Failed!\n");
      	return 1;
    }
    end_time = clock();
    /* Provind the output in CPU clocks as the question mentions CPU time and not humar time */
    printf("\nProfiling time of pthreade_create : %lu CPU clocks\n",(end_time-start_time));
    start_time = 0;
    start_time = clock();
    snprintf(buffer,12,"%lu",start_time); 
    pid = fork();
    if(pid < 0)
    {
        printf("\nERR: Fork Failed \n");
        exit(0);
    }

    else if(!pid)
    {
        char *args[]={"./child_process",buffer,NULL};
        execv(args[0],args);
    }
     
       
    end_time = clock();
    printf("\nProfiling time of fork and exec is  : %lu CPU clocks \n", (end_time - start_time));
    wait(NULL);

    return 0;
    
}