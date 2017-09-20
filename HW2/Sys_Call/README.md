README


Brief : Created a System Call (rand_sort #333) that performed a simple sort opreation on an user-space 
        randomly generated input buffer and returns a sorted buffer from kernel to Userspace
        Several sanity checks are performed to avoid memory leaks, illegal memory access and 
        basic invalid processing of input parameters in the kernel with useful debug strings
        and kernel logs. 
        Developed an User-space SW that tests the system call in a modular fashion.
 
Author : Bhallaji Venkatesan
        
System Call Implementation : 

Steps Done :   
1. Created a system call number in/linux/arch/x86/entry/syscalls/sycall_64.tbl as below :
    <number>    <abi>      <name>       <entry point>
     333        common    rand_sort	    sys_rand_sort
                          
2. Created the system call directory /linux/kernel/randsort 

3. Added syscall.c. The system call was implemented with the macro 
   SYSCALL_DEFINE3(rand_sort,int32_t*,input_buffer,int32_t, size, int32_t*,sorted_buffer)
   
  4.Created the corresponding make-file and add the directory to core-y in the main kernel makefile

5. Performed the folllowing commands at /linux 
   $sudo make -j4 (Compiling and building the kernel in a concurrent fashion)
   $sudo make install 
   $reboot 
   
6. Developed the Userspace software to invoke the system call in below fashion. 
   syscall(CUSTOM_SYSCALL_NO,input_buffer,input_size,output_buffer);
