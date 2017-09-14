#include<linux/kernel.h>
#include<linux/syscalls.h>
#include<linux/err.h>
#include<linux/slab.h>
#include<linux/gfp.h>
#include<uapi/asm-generic/errno-base.h>
void ltos_sort(int32_t *input, int32_t *output,int size)
{
   int outer,inner,temp = 0;
   memcpy(output,input,(sizeof(int32_t)*size)); 
   for(outer =0;outer<size;outer++)
   {
     for(inner = outer+1;inner<size;inner++)
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

void print_buffer(int32_t *buffer,int size)
{
   int i =0;
   for (i=0;i<size;i++)
   {
    printk(KERN_ALERT "%d",*(buffer+i));
    printk(KERN_ALERT " ");
   }
   
   printk(KERN_ALERT "\n");
   
}

asmlinkage long sys_rand_sort(int32_t *input_buffer, int32_t size, int32_t *sorted_buffer)
{
   int32_t *in_kbuff = NULL;
   int32_t *out_kbuff = NULL;
   //Validation of Input buffer and sorted buffer
   printk(KERN_ALERT "Enterning Random Sort Syscall\n");
   
   //To check validity of memory (access and memoryspace)
   
   /*long in_buff_error = 0;
   long out_buff_error = 0;*/
   if(!input_buffer || !sorted_buffer || (size<=0) )
   {
     printk(KERN_ALERT "Error ID %d: Invalid Arguments \n",EINVAL);
     return EINVAL;
   }
   
   in_kbuff = kmalloc((sizeof(int32_t)*size),GFP_KERNEL);
   out_kbuff = kmalloc((sizeof(int32_t)*size),GFP_KERNEL);
   if(!in_kbuff || !out_kbuff)
   {
     printk(KERN_ALERT "Error ID %d: Unable to allocate Kernel Memory \n",EINVAL);
     return EFAULT;
   }
   /*in_buff_error = PTR_ERR_OR_ZERO(input_buffer); 
   if(in_buff_error !=0) 
   {
       printk(KERN_ALERT "Input buffer Pointer Error %ld",in_buff_error);
       return 0;   
   }
   out_buff_error = PTR_ERR_OR_ZERO(sorted_buffer);
   if(out_buff_error !=0) 
   {
       printk(KERN_ALERT "Output buffer Pointer Error %ld",out_buff_error);
       return 0;   
   } */
   copy_from_user(in_kbuff,input_buffer,(sizeof(int32_t)*size));
   printk(KERN_ALERT "Size of Buffer: %d /n",size);
   printk(KERN_ALERT "Starting the sort in Random Sort Syscall\n");
   ltos_sort(input_buffer,out_kbuff,size);
   printk(KERN_ALERT "End of sort in  Random Sort Syscall\n");

   copy_to_user(sorted_buffer,out_kbuff,(sizeof(int32_t)*size));
   
   
   printk(KERN_ALERT "Tested the New Random Sort Syscall\n");
   printk(KERN_ALERT "Exiting Random Sort Syscall\n");
   return 0;
}
