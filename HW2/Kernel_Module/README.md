README 

Brief : Created an external Kernel Module for the Linux Kernel v 4.12.10, which implements a timer that 
        wakes up the kernel module every 500ms. Debug messages and useful strings are logged in the kernel
        logs.
        
Author : Bhallaji Venkatesan  

Kernel-Module Implementation (External): 
Steps Done :
1. Created custom kernel module directory 
2. Developed kernel module code “kern_modtest.c” and the corresponding Makefile to generate .ko file. 
3. Make 
4. Installed the module using sudo insmod ./kern_modtest.ko 
5. Copied the file to /lib/modules/4.12.10/kernel/drivers to deploy the module using $sudo depmod -a 
6. Performed modinfo kern_modtes and lsmod | grep kern_modtest to check the
                          deployed module.
