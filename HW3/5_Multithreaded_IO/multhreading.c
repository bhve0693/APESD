/*
* FileName        :    multhreading.c
* Description     :    This file contains multithreaded file I/O implementation 
*                        
* File Author Name:    Bhallaji Venkatesan 
* Tools used      :    gcc, gedit
* References      :    https://beginnersbook.com/2014/01/c-file-io/
*				  :	   http://aspyct.org/blog/2012/08/25/unix-signal-handling-example/
*
*
*/


#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>


/* Macros */
#define WRITE_THREAD  0
#define READ_THREAD   1
#define REPORT_THREAD 2
#define DEFAULT 	  3
#define SIG1_NOT_DONE 0
#define SIG1_DONE 1
#define MAIN_THREAD_PROCESSING 2
#define MAIN_THREAD_PROCESSING_DONE 3
#define READ_THREAD_WAITING 4

int sig_status = MAIN_THREAD_PROCESSING;


static volatile sig_atomic_t flag = WRITE_THREAD;
void signal_handler(int signal);

struct shared_datastruct{
	int count_char;	
	int count_word;	
	int count_line;
	char *filename;
};

long file_size = 0;
FILE *fp = NULL;

void signal_handler(int signal)
{   
	printf("\nEntering Signal Handler!\n");
	switch (signal)
	{
    	case SIGUSR1:
    	    if(sig_status == MAIN_THREAD_PROCESSING_DONE || sig_status == SIG1_DONE) //waiting on main thread to gracefully complete
    	    {
        		flag = READ_THREAD;
        		sig_status = SIG1_DONE;
            }
            else if(sig_status == MAIN_THREAD_PROCESSING)
            {
            	sig_status = READ_THREAD_WAITING;
            	printf("\nWaiting for Write thread to be finished.Press '#' to end write thread and try sending SIGUSR1 at a later point\n");
            }
            else
            {
            	printf("\nRead Thread already processed! Try SIGUSR2 for report statistics\n");
            }
        	break;

        case SIGUSR2: 
        	if(sig_status == SIG1_DONE) //Waiting for report thread to gracefully complete
        	{
        		flag = REPORT_THREAD;
       		}
       		else if(sig_status == MAIN_THREAD_PROCESSING || sig_status == READ_THREAD_WAITING)
       		{
       			printf("\n Thread1 still processing! Report not Ready!\n");
       		}
       		else
       		{
       			printf("\n SIGUSR1 not yet received! Report not Ready!\n");
       		}
        	break;

       	case SIGINT: 
       		printf("\nReceived SIGINT, proceeding to gracefully exit parent and child!\n");
       		if(fp != NULL)
       			fclose(fp);
       		exit(0);
       		break;


        default:
        	//Do Nothing
        	break;

	}
}

void *f_write(void *arg)
{
	if(!arg)
	{
		printf("\nERR:Invalid Arguments to thread\n");
		pthread_exit(NULL);
	}
	
	while(1)
	{
		if(flag == WRITE_THREAD)
		{
			printf("Current Process ID is %d \n",getpid());
			printf("\n Entering Write Thread \n"); 
			struct shared_datastruct *input = (struct shared_datastruct *)arg;
			printf("Enter the contens to be written into the file (To Terminate contents, enter '#' in a new line)\n");
	  		
	  		char input_buff;
	  		if(!(fp = fopen(input->filename, "w+")))
	  		{
	  			printf("\nERR:File open failed\n");
	  			pthread_exit(NULL);
	  		}
	  		while((input_buff = fgetc(stdin)) != '#')
	  		{
	  			fputc(input_buff, fp);
	  		}

	    	fclose(fp);

	   		break;
		}
		if(sig_status == READ_THREAD_WAITING)
		{
			fclose(fp);
			break;
		}
	}	
	sig_status = MAIN_THREAD_PROCESSING_DONE;
    return NULL;

}//Exiting f_write Thread

void *f_read(void *arg)
{

	if(!arg)
	{
		printf("\nERR:Invalid Arguments to thread\n");
		pthread_exit(NULL);
	}

	while(1)
	{
		if(flag == READ_THREAD)
		{
			printf("\nEntering Read Thread \n");
			struct shared_datastruct *report = (struct shared_datastruct *)arg;
			char ch;
			int count_line, count_char, count_word;
			report->count_line = 0;
			report->count_char = 0;
			report->count_word = 0; 
	  		if(!(fp = fopen(report->filename, "r+"))) 
	  		{
	  			printf("\nERR:File open failed\n");
	  			pthread_exit(NULL);
	  		}

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
		    }

		    printf("\nCharacter Count is %d\n",(report->count_char)-1);
		    printf("\nWord Count is %d\n",report->count_word);
		    printf("\nLine Count is %d\n",report->count_line);
		    fclose(fp);
		    break;

		   // pthread_mutex_unlock( & mutex );
		}

	}	    
    return NULL;
    //pthread_exit(NULL);
}

void *f_report(void *arg)
{
	if(!arg)
	{
		printf("\nERR:Invalid Arguments to thread\n");
		pthread_exit(NULL);
	}
	while(1)
	{
		if(flag == REPORT_THREAD)
		{
			if(sig_status == SIG1_DONE)
			{
				printf("\nEntering Report Thread \n");
				struct shared_datastruct *report = (struct shared_datastruct *)arg;
				printf("\nCharacter Count is %d\n",(report->count_char)-1);
		    	printf("\nWord Count is %d\n",report->count_word);
		    	printf("\nLine Count is %d\n",report->count_line);
		    	break;
		    }
		}
	}
	return NULL;
}

int main(int argc , char **argv)
{

	if (argc <= 1)
  	{
    	printf ("USAGE:  <Filename> \n");
    	exit(1);
  	}
	struct sigaction custom_signal;
	struct shared_datastruct report;
	pthread_attr_t attr;
	pthread_t thread_fwrite,thread_fread,thread_report;

	report.count_char = 0;
	report.count_word = 0;
	report.count_line = 0;
	report.filename = malloc(50 *sizeof(char));

	if(!report.filename)
	{
		printf("\nERR:Malloc Failed\n");
		return 1;
	}

	printf("Current Process ID is %d \n",getpid());
  	if(!memcpy(report.filename,argv[1],strlen(argv[1])))
  	{
  		printf("\nERR:Memcpy Failed!\n");
		return 1;
  	}

    custom_signal.sa_handler = signal_handler;

    if(sigfillset(&custom_signal.sa_mask) == -1)
    {
    	printf("\nERR:Signal Mask Setting Failed!\n");
		return 1;
    }
    if(sigaction(SIGUSR1, &custom_signal, NULL) == -1)
    {
    	printf("\nERR:Cannot Handle SIGUSR1!\n");
    	return 1;
    }

    if(sigaction(SIGUSR2, &custom_signal, NULL) == -1)
    {
    	printf("\nERR:Cannot Handle SIGUSR2!\n");
    	return 1;
    }

    if(sigaction(SIGINT, &custom_signal, NULL) == -1)
    {
    	printf("\nERR:Cannot Handle SIGINT!\n");
    	return 1;
    }

  	if(pthread_attr_init(&attr))
  	{
  		printf("\nERR:Thread attribute initialization Failed!\n");
    	return 1;
  	}

  	if(pthread_create(&thread_fwrite, NULL, &f_write, &report))
  	{
  		printf("\nERR:Thread Creation Failed!\n");
    	return 1;
  	}
    
    if(pthread_create(&thread_fread, NULL, &f_read, &report))
    {
  		printf("\nERR:Thread Creation Failed!\n");
    	return 1;
  	}	
    if(pthread_create(&thread_report, NULL, &f_report, &report))
	{
  		printf("\nERR:Thread Creation Failed!\n");
    	return 1;
  	}

    if(pthread_join(thread_fwrite, NULL) != 0)
	{
  		printf("\nERR:Thread Joining Failed!\n");
    	return 1;
  	}
    //pthread_kill(thread_fread, SIGUSR1);
    if(pthread_join(thread_fread, NULL) != 0)
    {
  		printf("\nERR:Thread Joining Failed!\n");
    	return 1;
  	}
    //pthread_kill(thread_report, SIGUSR2);

    if(pthread_join(thread_report, NULL) != 0)
    {	
    	printf("\nERR:Thread Joining Failed!\n");
    	return 1;
    }

    /* pthread_exit always succeeds */
  	pthread_exit(NULL);

    return 0;
}