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
#include <signal.h>

#define WRITE_THREAD  0
#define READ_THREAD   1
#define REPORT_THREAD 2
#define DEFAULT 	  3
#define MAX_FILENAME_SIZE 50
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


void signal_handler(int signal)
{   
	printf("\nEntering Here\n");
	switch (signal)
	{
    	case SIGUSR1:
    	    if(sig_status == MAIN_THREAD_PROCESSING_DONE)
    	    {
        		flag = READ_THREAD;
        		sig_status = SIG1_DONE;
            }
            else
            {
            	sig_status = READ_THREAD_WAITING;
            	printf("\nWaiting for Write thread to be finished. Try sending SIGUSR1 at a later point\n");
            }
        	break;

        case SIGUSR2: 
        	if(sig_status == SIG1_DONE)
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
        default:
        	break;

	}
}

void *f_write(void *arg)
{
	//pthread_mutex_lock( &mutex );
	FILE *fp;
	while(1)
	{
		if(flag == WRITE_THREAD)
		{
			printf("Current Process ID is %d \n",getpid());
			printf("\n Entering Write Thread \n");
			//long d = (long)(arg);
			//printf("\n Long is %ld\n",d); 
			struct shared_datastruct *input = (struct shared_datastruct *)arg;
			//char *temp_buff = malloc(sizeof(char)*1024);
			//char **new_file = (char **)arg;
			printf("Enter the contens to be written into the file\n");
	    	//fgets(temp_buff, 1024*sizeof(char),stdin);
	    	//printf("\n temp buff is %s \n", temp_buff);
	    	//printf("strlen is %d", strlen(temp_buff));
	    	//printf("Size of tempbuff is %ld and size of char is %ld\n", sizeof(temp_buff), sizeof(char));
	  		
	  		char input_buff;
	  		fp = fopen(input->filename, "w+");
	  		while((input_buff = fgetc(stdin)) != '#')
	  		{
	  			fputc(input_buff, fp);
	  		}
	  		//fwrite(temp_buff, 1, strlen(temp_buff)*sizeof(char),fp);

	  		/*for(int i = 2; i<argc; i++)
	  		{
	  			fwrite(argv[i], 1, sizeof(argv[i])*sizeof(char),fp);
		    }*/
	    	fclose(fp);
	    	/*fp = fopen(input->filename, "r+");
	    	file_size = strlen(temp_buff);
	    	char *buff = malloc(strlen(temp_buff)*sizeof(char));
	    	while(!feof(fp))
	    	{
	    		fread(buff, 1,strlen(temp_buff)*sizeof(char),fp);
	    	}
	    	printf("File size in write thread is %ld \n", file_size);
	    	printf("\nBuff is %s\n",buff);
	    	fclose(fp);*/
	    	//pthread_cond_signal( &cond ); 
	   		//pthread_mutex_unlock( & mutex );
	   		//kill(getpid(),SIGUSR1);
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
  //  pthread_exit(NULL);

}//Exiting f_write Thread

void *f_read(void *arg)
{
	//pthread_mutex_lock( &mutex );
	//pthread_cond_wait( & cond, & mutex ); 

	while(1)
	{
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
	    	FILE *fp;
	  		fp = fopen(report->filename, "r+");
		    //printf("\nvalue of fp is %ld",fp);
		  	
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
		    break;

		   // pthread_mutex_unlock( & mutex );
		}

	}	    
    return NULL;
    //pthread_exit(NULL);
}

void *f_report(void *arg)
{
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
	//char *temp_buff = malloc(sizeof(char)*1024);
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
  //	char **new_file = argv[1];
  	pthread_attr_init(&attr);
  	printf("\nargv 1 length is %d\n",strlen(argv[1]));
  	pthread_create(&thread_fwrite, NULL, &f_write, &report);
    //pthread_join(thread_fwrite, NULL);
    pthread_create(&thread_fread, NULL, &f_read, &report);
    pthread_create(&thread_report, NULL, &f_report, &report);
    pthread_join(thread_fwrite, NULL);
    //pthread_kill(thread_fread, SIGUSR1);
    pthread_join(thread_fread, NULL);
    //pthread_kill(thread_report, SIGUSR2);
    pthread_join(thread_report, NULL);
  	pthread_exit(NULL);

  /*	printf("Enter the contens to be written into the file\n");
    fgets(temp_buff, 1024*sizeof(char),stdin);
    printf("\n temp buff is %s \n", temp_buff);
    printf("strlen is %d", strlen(temp_buff));
    printf("Size of tempbuff is %ld and size of char is %ld\n", sizeof(temp_buff), sizeof(char));
  	FILE *fp;
  	fp = fopen(new_file, "w+");
  	fwrite(temp_buff, 1, strlen(temp_buff)*sizeof(char),fp);
  	/*for(int i = 2; i<argc; i++)
  	{
  		fwrite(argv[i], 1, sizeof(argv[i])*sizeof(char),fp);
    }*/
  /*  fclose(fp);
    fp = fopen(new_file, "r+");
    char *buff = malloc(strlen(temp_buff)*sizeof(char));
    while(!feof(fp))
    {
    	fread(buff, strlen(temp_buff)*sizeof(char),1,fp);
    }
    printf("\nBuff is %s\n",buff);
    fclose(fp);*/
    return 0;
}