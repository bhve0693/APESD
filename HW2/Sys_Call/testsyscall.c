/*
*
* FileName        :    testsycall.c
* Description     :    This file contains Demo SW implementation that calls system call implementation of rand_sort system call
*                      (Sycall No.333).                       
* File Author Name:    Bhallaji Venkatesan 
* Tools used      :    gcc, gedit
* References      :    None
*
*/


#include<unistd.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdio.h>
#include<string.h>


/* Macros */
#define CUSTOM_SYSCALL_NO 333


/* Function Prototypes */
void rand_input(int32_t *input, int size);
void print_buffer(int32_t *buffer,int size);
void ltos_sort(int32_t *input, int32_t *output,int size);



/**
​ * ​ ​ @brief​ : Generates Random input and populates input buffer
​ *
​ * ​ ​ No Returns. Updates the input buffer pointer
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ input  ​ A pointer to the input buffer 
 *           size    Size of the input buffer 
​ *
​ * ​ ​ @return​ ​ None
​ */
void rand_input(int32_t *input, int size)
{  
   if(!input)
   {
     printf("Invalid Input buffer for random data loading! Retry! \n");
     exit(0);
   }
   int i = 0;
   for (i=0;i<size;i++)
     *(input+i) = rand()%size; 
}

/**
​ * ​ ​ @brief​ : Prints a given buffer
​ *
​ * ​ ​ No Returns. 
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ buffer  ​ A pointer to the input buffer 
 *           size    Size of the input buffer 
​ *
​ * ​ ​ @return​ ​ None
​ */
void print_buffer(int32_t *buffer,int size)
{
   int i =0;
   for (i=0;i<size;i++)
   {
    printf("%d",*(buffer+i));
    printf(" ");
   }
   
   printf("\n");
   
}


/**
​ * ​ ​ @brief​ : Userspace Test Function that Sorts the input buffer 
 *            in the order of large to small and updates the input 
 *            buffer pointer
​ *
​ * ​ ​ No Returns. Updates the Output Buffer to be sorted
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ input  ​ A pointer to the input buffer 
 *           output  A pointer to the output buffer to be sorted 
 *           size    Size of the input buffer to be sorted
​ *
​ * ​ ​ @return​ ​ None
​ */
void ltos_sort(int32_t *input, int32_t *output,int size)
{
   int outer,inner,temp = 0;
   memcpy(output,input,(sizeof(int32_t)*size)); 
   for(outer =0;outer<size;outer++)
   {
     for(inner = outer+1;inner<=size;inner++)
     {
       if(*(output+outer) < *(output+inner))
       { 
	 temp = *(output+outer);
         *(output+outer) = *(output+inner); 
         *(output + inner) = temp;
       }
      }
    }
}


/**
​ * ​ ​ @brief​ : Test function for valid syscall invoke.
​ * ​ ​ No Returns. 
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ None
​ *
​ * ​ ​ @return​ ​ None
​ */
void test_syscall_valid()
{
   long temp_return = 0;
   int32_t input_size = 0;
   printf("-------------TESTCASE 1---------------- \r\n\n");
   printf("Enter the Size of the buffer to be sorted (Minimum of 256)\r\n");
   scanf("%d",&input_size);
   if(input_size < 256)
   {
     printf("Invalid Size! Enter a value more than 256 next time! \n");
     exit(0);
   }
   int32_t *input_buffer = malloc(sizeof(int32_t)*input_size);
   int32_t *output_buffer = malloc(sizeof(int32_t)*input_size);
   if(!input_buffer || !output_buffer)
   {
   	printf("Userspace Malloc Error!! \n");
   	exit(0);
   }   
   rand_input(input_buffer,input_size);
   printf("\nInput_Buffer \n\n");
   print_buffer(input_buffer,input_size);   
   printf("\n");
   printf("Valid System call check 1 with buffer size as %d :\n\n",input_size);
   temp_return = syscall(CUSTOM_SYSCALL_NO,input_buffer,input_size,output_buffer);
   if(!temp_return)
   {
     printf("Sorted_Buffer \n\n");
     print_buffer(output_buffer,input_size);
   }
   else
   {
     printf("Error in syscall with Error ID : %ld \n\n",temp_return);
   }
   free(input_buffer);
   free(output_buffer);  

}

/**
​ * ​ ​ @brief​ : Test function for valid syscall invoke with increased size.
​ * ​ ​ No Returns. 
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ None
​ *
​ * ​ ​ @return​ ​ None
​ */

void test_syscall_valid_incsize()
{
   long temp_return = 0;
   int32_t input_size = 300;
   int32_t *input_buffer = malloc(sizeof(int32_t)*input_size);
   int32_t *output_buffer = malloc(sizeof(int32_t)*input_size);
   printf("-------------TESTCASE 2---------------- \r\n\n");
   printf("Valid System call check 2 with buffer size as 300: \n\n");
   if(!input_buffer || !output_buffer)
   {
   	printf("Userspace Malloc Error!! \n");
   	exit(0);
   }   
   rand_input(input_buffer,input_size);
   printf("Input_Buffer \n\n");
   print_buffer(input_buffer,input_size);   
   printf("\n");
   temp_return = syscall(CUSTOM_SYSCALL_NO,input_buffer,input_size,output_buffer);
   if(!temp_return)
   {
     printf("Sorted_Buffer \n\n");
     print_buffer(output_buffer,input_size);
   }
   else
   {
     printf("Error in syscall with Error ID : %ld \n\n",temp_return);
   }
   free(input_buffer);
   free(output_buffer);  
}

/**
​ * ​ ​ @brief​ : Test function for invalid syscall invoke with NULL I/P parameters.
​ * ​ ​ No Returns. 
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ None
​ *
​ * ​ ​ @return​ ​ None
​ */

void test_syscall_invalid_input()
{
   long temp_return = 0;
   int32_t input_size = 300;
   printf("-------------TESTCASE 3---------------- \r\n\n");
   printf("Invalid System call with NULL Input and Output buffers: \r\n\n");
   temp_return = syscall(CUSTOM_SYSCALL_NO,NULL,input_size,NULL);
   if(!temp_return)
   {
     printf("Sorted_Buffer \n\n");
   }
   else
   {
     printf("Error in syscall with Error ID : %ld \n\n",temp_return);
   }
}


/**
​ * ​ ​ @brief​ : Test function for invalid syscall invoke with size < 256.
​ * ​ ​ No Returns. 
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ None
​ *
​ * ​ ​ @return​ ​ None
​ */
void test_syscall_invalid_inputsize()
{
   long temp_return = 0;
   int32_t input_size = 100;
   int32_t *input_buffer = malloc(sizeof(int32_t)*input_size);
   int32_t *output_buffer = malloc(sizeof(int32_t)*input_size);
   printf("-------------TESTCASE 4---------------- \r\n\n");
   printf("Invalid System call with size less than 256: \r\n\n");
   temp_return = syscall(CUSTOM_SYSCALL_NO,input_buffer,input_size,output_buffer);
   if(!temp_return)
   {
     printf("Sorted_Buffer \n\n");
     print_buffer(output_buffer,input_size);
   }
   else
   {
     printf("Error in syscall with Error ID : %ld \n\n",temp_return);
   }
   free(input_buffer);
   free(output_buffer);  
}



int main()
{
   test_syscall_valid();
   test_syscall_valid_incsize();
   test_syscall_invalid_input();
   test_syscall_invalid_inputsize();
   return 0;
}
