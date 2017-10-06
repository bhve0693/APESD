/*
* FileName        :    threadapi_demo.c
* Description     :    This file contains implementation that uses create, join, exit,
					             self, getattr, getattr_default, setattr, mutex_init, mutex_destroy, 
			                 mutex_lock, mutex_trylock,cond_init, cond_signal, cond_wait 
			                 and cond_destroy api's of pthreads to generate a random input
			                 buffer, and sort it. 
*                        
* File Author Name:    Bhallaji Venkatesan 
* Tools used      :    gcc, gedit
* References      :    man pages
*
*
*/


#define _GNU_SOURCE 	
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>



int thread_status = 0;
pthread_mutex_t mutex;
pthread_cond_t cond;

void *rand_input(void *arg)
{  
   printf("\nrand_input pthread thread ID : %lu\n", pthread_self());
   while(1)
   {
       pthread_mutex_lock(&mutex); 
       if(!thread_status)
       {
           printf("\n Entering input Thread\n");
           int *input = (int*)arg;
           int size = 50;
           if(!input)
           {
             printf("Invalid Input buffer for random data loading! Retry! \n");
             exit(0);
           }
           int i = 0;
           for (i=0;i<size;i++)
             *(input+i) = rand()%size; 

          printf("\nInput Buffer\n");
          for(i = 0 ;i<size-1;i++)
          {
            printf("%d,",*(input+i));
          }
          *(input+size-1)=22;
           for (i=0;i<size;i++)
           {
            
             if(*(input+i) == 22)
             { 
               pthread_cond_signal(&cond);
                
               thread_status = 1;
                 
               pthread_mutex_unlock(&mutex);
             }
           }
           break;
       }
    }
   return NULL;
}



void *ltos_sort(void *arg)
{
   printf("\nltos_sort pthread self ID : %lu\n", pthread_self());
   while(1)
   {

        if(!pthread_mutex_trylock(&mutex))
        {
		        pthread_cond_wait( &cond, &mutex);
		        if(thread_status)
		        {
		           int outer,inner,temp = 0;
		           int size = 50;
		           int i =0;
		           int *input = (int *)arg;
		           for(outer =0;outer<size;outer++)
		           {
		             for(inner = outer+1;inner<=size;inner++)
		             {
		               if(*(input+outer) < *(input+inner))
		               { 
		        	       temp = *(input+outer);
		                 *(input+outer) = *(input+inner); 
		                 *(input + inner) = temp;
		               }
		              }
		            }

		            pthread_mutex_unlock(&mutex);
		            break;
		        }
    	}

    }
    return NULL;
}



int main()
{
    int i =0;
    int result = 0;
    long long stacksize=0;
    int *buffer = malloc(100*sizeof(int));
    if(!buffer)
    {
      printf("\n Malloc Failed \n");
      exit(0);
    }
    pthread_t rinput_thread,sort_thread;
    pthread_attr_t attr;
    printf("Enter stack size(greate than or equal to 0:)");
    scanf("%lld",&stacksize);
    if(stacksize>=0)
    {
      result = pthread_attr_setstacksize(&attr,stacksize);
      if(!result) printf("ERR:In setting stack size\n");
    }
    else
    {
      printf("\nERR:INVALID STACK SIZE! Exiting!\n");
      exit(0);
    }

    if(pthread_mutex_init(&mutex,NULL) != 0)
    {
      printf("\nERR:Mutex Init Failed!\n");
      return 1;
    }
    if(pthread_cond_init(&cond,NULL) != 0)
    {
      printf("\nERR:Condition Init Failed!\n");
      return 1;
    }

    if(pthread_getattr_default_np(&attr) !=0)
    {
       printf("\nERR:get attribute default Failed!\n");
       return 1;

    }
    if(pthread_create(&rinput_thread,&attr, &rand_input,(void *)buffer) != 0)
    {
      printf("\nERR:Thread Creation Failed!\n");
      return 1;
    }
    if(pthread_create(&sort_thread, &attr, &ltos_sort, (void *)buffer) != 0)
    {
      printf("\nERR:Thread Creation Failed!\n");
      return 1;
    }
    if(result = pthread_getattr_np(rinput_thread,&attr) != 0)
    {
      printf("\nERR:get attribute  Failed!\n");
       return 1;
    }
    printf("\n Result of successfull getattr %d\n");

    if(pthread_join(rinput_thread, NULL) != 0)
    { 
      printf("\nERR:Thread Joining Failed!\n");
      return 1;
    }

    if(pthread_join(sort_thread, NULL) != 0)
    { 
      printf("\nERR:Thread Joining Failed!\n");
      return 1;
    }

    
    printf("\n\nSorted buffer\n");
    for(i = 0; i<50; i++)
    {
      printf("%d,",*(buffer+i));
    }
    printf("\n");

    pthread_exit(NULL);
    if(pthread_mutex_destroy(&mutex) != 0)
    {
      printf("\nERR:Mutex destroy Failed!\n");
      return 1;

    }
    if(pthread_cond_destroy(&cond) !=0)
    {
      printf("\nERR:Condition destroy Failed!\n");
      return 1;

    }
    return 0;

}