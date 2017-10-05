/*
* FileName        :    multithreaded_io.c
* Description     :    This file contains multithreaded file I/O implementation 
*                        
* File Author Name:    Bhallaji Venkatesan 
* Tools used      :    gcc, gedit
* References      :    
*
*
*/


#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define WRITE_THREAD  0
#define READ_THREAD   1
#define REPORT_THREAD 2
#define DEFAULT       3
#define MAX_FILENAME_SIZE 40

static volatile sig_atomic_t flag = WRITE_THREAD;
void signal_handler(int signal);

struct shared_datastruct{
	int count_char;	
	int count_word;	
	int count_line;
	char *filename;
};

long file_size = 0;
FILE *fp;

void signal_handler(int signal)
{   
	switch (signal)
	{
    	case SIGUSR1:
        	flag = READ_THREAD;
        	break;

        case SIGUSR2: 
        	flag = REPORT_THREAD;
        	break;
        default:
        	break;

	}
}

void *f_write(void *arg)
{
	//pthread_mutex_lock( &mutex );
	char temp_data;
	int i = 0;
	//while(1)
	//{
		if(flag == WRITE_THREAD)
		{   
			printf("Current Process ID is %d \n",getpid());
			printf("\n Entering Write Thread \n");
			//long d = (long)(arg);
			//printf("\n Long is %ld\n",d); 
			struct shared_datastruct *input = (struct shared_datastruct *)arg;
			char *temp_buff = malloc(sizeof(char)*1024);
			
			//char **new_file = (char **)arg;
			printf("Enter the contens to be written into the file\n");
			fp = fopen(input->filename, "w+");
			while((temp_data = fgetc(stdin)) != '#')
			{
				//*(temp_buff +i) = temp_data;
				fputc(temp_data,fp);
	  	    }
	  	    
	  	   /* if(flag == READ_THREAD)
	  	    {
	  	    	//flag = READ_THREAD;
	  	  		printf("\n COming here after signal handler\n");
	  	    	fclose(fp);
	  	    	pthread_exit(NULL);
	  	    }*/
	  	    
	  	
	    	printf("\n temp buff is %s \n", temp_buff);
	    	printf("strlen is %d", strlen(temp_buff));
	    	printf("Size of tempbuff is %ld and size of char is %ld\n", sizeof(temp_buff), sizeof(char));
	    	fclose(fp);
	    	//pthread_cond_signal( &cond ); 
	   		//pthread_mutex_unlock( & mutex );
	   		//kill(getpid(),SIGUSR1);
	  		//break;
		}
		else
		{
			printf("\n Exiting Write Thread \n");
			pthread_exit(NULL);
			//break;
		}
	//}	

    //return NULL;
  printf("\n Exiting Write Thread \n");
  pthread_exit(NULL);

}//Exiting f_write Thread

void *f_read(void *arg)
{
	//pthread_mutex_lock( &mutex );
	//pthread_cond_wait( & cond, & mutex ); 

	//while(1)
	//{
		if(flag == READ_THREAD)
		{
			printf("\nEntering Read Thread \n");
			struct shared_datastruct *report = (struct shared_datastruct *)arg;
			//main_struct = (shared_datastruct *)arg;
			//char **new_file = (char **)arg;
		//char new_file[] = {"testing.txt"};
			//memcpy(main_struct.filename,argv[1],strlen(argv[1])*sizeof(char));
			char ch;
			int count_line, count_char, count_word;
			report->count_line = 0;
			report->count_char = 0;
			report->count_word = 0;
	    	//FILE *fp;
	    	if(fp !=NULL)
	    	{
	    		printf("File was not closed.. CLosing now\n");
	    		fclose(fp);
	    	}
	    	printf("\nvalue of fp1 is %ld",fp);
	  		fp = fopen(report->filename, "r+");
		    printf("\nvalue of fp is %ld",fp);
		  	
		  	//printf("File size is %d" , file_size);
		  	//char *buff = malloc(file_size*sizeof(char));
		    while((ch = getc(fp)) != EOF)
		    {
		    	
		    	if((ch != ' ')|| (ch != '\n'))
		    	{
		    		report->count_char++;
		    	}
		    	if((ch == ' ')||(ch == '\n'))
		    	{
		    		report->count_word++;
		    	}
		    	if((ch == '\n'))
		    	{
		    		report->count_line++;
		    	}
		    	//fread(buff, 1,file_size*sizeof(char),fp);
		    }
		    //printf("\nBuff is %s\n",buff);
		    printf("\nCharacter Count is %d\n",(report->count_char)-1);
		    printf("\nWord Count is %d\n",report->count_word);
		    printf("\nLine Count is %d\n",report->count_line);
		    fclose(fp);
		    //break;

		   // pthread_mutex_unlock( & mutex );
		}

	//}	    
    //return NULL;
    printf("\n Exiting Read Thread \n");

    pthread_exit(NULL);
}

void *f_report(void *arg)
{
	while(1)
	{
		if(flag == REPORT_THREAD)
		{
			printf("\nEntering Report Thread \n");
			struct shared_datastruct *report = (struct shared_datastruct *)arg;
			printf("\nCharacter Count is %d\n",(report->count_char)-1);
		    printf("\nWord Count is %d\n",report->count_word);
		    printf("\nLine Count is %d\n",report->count_line);
		    break;
		}
	}
	printf("\n Exiting Report Thread \n");
	pthread_exit(NULL);
	//return NULL;
}

int main(int argc , char **argv)
{
	//char *temp_buff = malloc(sizeof(char)*1024);
	printf("\n Parent Process ID is %d\n",getpid());
	int pid =0;
	if (argc <= 1)
  	{
    	printf ("USAGE:  <Filename> \n");
    	exit(1);
  	}
	struct sigaction custom_signal;
	struct shared_datastruct report;

	char filename[MAX_FILENAME_SIZE];
	report.count_char = 0;
	report.count_word = 0;
	report.count_line = 0;
	report.filename = malloc(50 *sizeof(char));
	if(!report.filename)
	{
		printf("\nMalloc Failed\n");
		exit(0);
	}
	pthread_attr_t attr;
	pthread_t thread_fwrite,thread_fread,thread_report;
	printf("Current Process ID is %d \n",getpid());
  	memcpy(report.filename,argv[1],strlen(argv[1]));
    long a =10;
    custom_signal.sa_handler = signal_handler;
    sigfillset(&custom_signal.sa_mask);
    if(sigaction(SIGUSR1, &custom_signal, NULL) == -1)
    {
    	printf("\\n Cannot Handle SIGUSR1\n");
    }

    if(sigaction(SIGUSR2, &custom_signal, NULL) == -1)
    {
    	printf("\\n Cannot Handle SIGUSR2\n");
    }
  	pthread_attr_init(&attr);
  	printf("\nargv 1 length is %d\n",strlen(argv[1]));
  	pthread_create(&thread_fwrite, NULL, &f_write, &report);

    //pthread_join(thread_fwrite, NULL);
    pthread_create(&thread_fread, NULL, &f_read, &report);
    pthread_create(&thread_report, NULL, &f_report, &report);
     /*if(!(pid = fork()))
     {
     	printf("\n New Process ID is %d\n",getpid());
     }*/
    
    //pthread_kill(thread_fread, SIGUSR1);
    pthread_join(thread_fwrite, NULL);
    pthread_join(thread_fread, NULL);
    //pthread_kill(thread_report, SIGUSR2);
    pthread_join(thread_report, NULL);
  	pthread_exit(NULL);

  	printf("Exiting Main \n !");

    return 0;
}