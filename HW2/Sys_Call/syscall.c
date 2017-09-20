/*

* FileName        :    sycall.c
* Description     :    This file contains system call implementation of rand_sort system call
                       (Sycall No.333) that sorts a randomly generated input buffer from userspace
                       in the order of largest -> smallest in kernel space and returns the sorted
		       buffer. 
                      
                        
* File Author Name:    Bhallaji Venkatesan 
* Tools used      :    gcc, gedit
* References      :    https://github.com/afosdick/ecen5013/tree/develop/tutorials/unit_tests

*/


#include<linux/kernel.h>
#include<linux/syscalls.h>
#include<linux/err.h>
#include<linux/slab.h>
#include<linux/gfp.h>
#include<uapi/asm-generic/errno-base.h>



/**
​ * ​ ​ @brief​ : Sorts the input buffer in the order of large to small and updates
 *            the input buffer pointer
​ *
​ * ​ ​ No Returns. Updates the input buffer pointer
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ input  ​ A pointer to the input buffer to be sorted
 *           size    Size of the input buffer to be sorted
​ *
​ * ​ ​ @return​ ​ None
​ */

void ltos_sort(int32_t *input, int size)
{
   int outer,inner,temp = 0; 
   /* Basic Sorting Algorithm */
   for(outer =0;outer<size;outer++)
   {
     for(inner = outer+1;inner<size;inner++)
     {
       if(*(input+outer) < *(input+inner))
       { 
	 temp = *(input+outer);
         *(input + outer) = *(input + inner); 
         *(input + inner) = temp;
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

SYSCALL_DEFINE3(rand_sort,int32_t*,input_buffer,int32_t, size, int32_t*,sorted_buffer)
{
   int32_t *in_kbuff = NULL;
   unsigned long status = 0;
   printk(KERN_ALERT "Entering Random Sort Syscall\n");
   
   /* Checking if the input parameters are valid */
   if(!input_buffer || !sorted_buffer || (size<=0) )
   {
     printk(KERN_ALERT "Error ID %d: Invalid Arguments \n",EINVAL);
     printk(KERN_ALERT "Exiting Random Sort Syscall\n");
     return EINVAL;
   }
   
   in_kbuff = kmalloc((sizeof(int32_t)*size),GFP_KERNEL);
   /* Checking if the kernel memory operation is successful */
   if(!in_kbuff)
   {
     printk(KERN_ALERT "Error ID %d: Unable to allocate Kernel Memory \n",EINVAL);
     printk(KERN_ALERT "Exiting Random Sort Syscall\n");
     return EFAULT;
   }
  
   /* Copying User Space buffer to Kernel Space buffer and performing Sanity check
      on the operation. This involves checking if the input buffer points to a valid 
      userspace memory and destination buffer is a valid kernel space buffer*/
   status = copy_from_user(input_buffer,in_kbuff,(sizeof(int32_t)*size));
   if(status !=0)
   { 
     if(status == (sizeof(int32_t)*size))
     {
       printk(KERN_ALERT "Error ID %d:Invalid sorce or destination address during copy_from_user\n",EFAULT);
       return EFAULT;
     }
     else 
     {
       printk(KERN_ALERT "Error ID %d:Memory pointers extending to invalid address space during copy_from_user\n",EFAULT);
       return EFAULT;
     }
   }
   
   printk(KERN_ALERT "Size of Buffer: %d \n",size);
   printk(KERN_ALERT "Starting the sort in Random Sort Syscall\n");
   ltos_sort(in_kbuff, size);
   printk(KERN_ALERT "End of sort in  Random Sort Syscall\n");
   status = 0;
   
   /*Copying Kernel Space buffer to User Space buffer and performing Sanity check
      on the operation. This involves checking if the input buffer points to a valid 
      userspace memory and destination buffer is a valid kernel space buffer */

   status = copy_to_user(sorted_buffer,in_kbuff,(sizeof(int32_t)*size));
   if(status !=0)
   { 
     if(status == (sizeof(int32_t)*size))
     {
       printk(KERN_ALERT "Error ID %d:Invalid source or destination address during copy_to_user\n",EFAULT);
       return EFAULT;
     }
     else 
     {
       printk(KERN_ALERT "Error ID %d:Memory pointers extending to invalid address space during copy_to_user\n",EFAULT);
       return EFAULT;
     }
   }
   printk(KERN_ALERT "Exiting Random Sort Syscall\n");
   return 0;
}
