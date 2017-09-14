#include<unistd.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdio.h>
#include<string.h>
#include<err.h>

#define sizer 20

void rand_input(int32_t *input, int size);
void print_buffer(int32_t *buffer,int size);
void ltos_sort(int32_t *input, int32_t *output,int size);

void rand_input(int32_t *input, int size)
{
   int i = 0;
   for (i=0;i<size;i++)
     *(input+i) = rand()%sizer; 
}

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
int main()
{

   int32_t *input_buffer = malloc(sizeof(int32_t)*sizer);
   int32_t *output_buffer = malloc(sizeof(int32_t)*sizer);   
   rand_input(input_buffer,sizer);
   printf("Input_Buffer \n");
   print_buffer(input_buffer,sizer);   
   printf("\n");
   //ltos_sort(input_buffer,output_buffer,sizer);
  // output_buffer = NULL;
   int temp = 0;
   input_buffer = NULL;
   long temp_return = 0;
   temp_return = syscall(333,input_buffer,sizer,output_buffer);
   if(!temp_return)
   {
     printf("Sorted_Buffer \n");
     print_buffer(output_buffer,sizer);
   }
   else
   {
     printf("Error in syscall with Error ID : %ld \n",temp_return);
   }
     
   return 0;
}
