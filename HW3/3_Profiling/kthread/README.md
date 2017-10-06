README 

Brief : Created an external Kernel Module for the Linux Kernel v 4.12.10, which profiles the kthread_create in jiffies
        
Author : Bhallaji Venkatesan  

Kernel-Module Implementation (External): 
Steps Done :
1. Created custom kernel module directory 

2. Developed kernel module code kthread_profile.c” and the corresponding Makefile to generate .ko file

3. $make
 
4. Installed the module using sudo insmod ./kthread_profile.ko 

5. Copied the file to /lib/modules/4.12.10/kernel/drivers to deploy the module using $sudo depmod -a 

6. Performed modinfo kthread_profile and lsmod | grep kthread_profile to check the deployed module.
