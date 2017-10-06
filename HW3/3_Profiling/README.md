README 

Brief : Created an userspace code to profile pthread_create and fork and exec syscalls for thread and process creation.
        
Author : Bhallaji Venkatesan  

Profiling Implementation (External): 
Steps Done :
1. Created userspace code that uses the time library to provide CPU time in CPU clock

2. used POSIX API's for pthread_create and profiled.

3. created a child_process.c by passing arguments through fork and execvp
 
4. $make for creating output files for pthread_fork.c and child_process.c

5. Run the code by ./pthread_fork

