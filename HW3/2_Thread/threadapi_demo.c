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
* References      :    
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

          printf("\n Input Buffer\n");
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
               // sleep(3);
             }
           }
           break;
       }
    }
   return NULL;
}



void *ltos_sort(void *arg)
{
   printf("\nltos_sort pthread thread ID : %lu\n", pthread_self());
   while(1)
   {

        if(!pthread_mutex_trylock(&mutex))
        {
		        pthread_cond_wait( &cond, &mutex);
		        if(thread_status)
		        {
		       
		          // pthread_cond_wait( & cond, & mutex );
		           printf("\n Entering sorting Thread\n");
		           int outer,inner,temp = 0;
		           int size = 50;
		           int i =0;
		           int *input = (int *)arg;
		           printf("\n Input Buffer in sorting thread\n");
		           for (i=0;i<size;i++)
		             printf("%d,",*(input+i));
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
		            printf("\n Input Buffer after sorting \n");
		            for (i=0;i<size;i++)
		            printf("%d,",*(input+i));
		            pthread_mutex_unlock(&mutex);
		            break;
		        }
    	}

    }
    return NULL;
}



int main()
{
  //Thread 1 
  //pthread create 
  //pthread exit 
// Random Input Generation in an array
// Condition Thread 2 after array generation
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
    if(result) printf("Error in setting stack size\n");
  }
  pthread_mutex_init(&mutex,NULL);
  pthread_cond_init(&cond,NULL);
  //pthread_attr_init(&attr);
  pthread_getattr_default_np(&attr);
 // pthread_setattr_np(&attr);
  pthread_create(&rinput_thread,&attr, &rand_input,(void *)buffer);
  pthread_create(&sort_thread, &attr, &ltos_sort, (void *)buffer);
  result = pthread_getattr_np(rinput_thread,&attr);
  printf("\n Result of getattr %d \n");
  pthread_join(rinput_thread, NULL);
  pthread_join(sort_thread, NULL);
  
  printf("\nSorted buffer\n");
  for(i = 0; i<50; i++)
  {
    printf("%d,",*(buffer+i));
  }

  pthread_exit(NULL);
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond);
  //Thread 2
  // Wait on condition for input array creation 
  //Perform sort 

}