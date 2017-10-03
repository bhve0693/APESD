#include<stdio.h>
#include<stdlib.h>
#include<linux/sched.h>
#include<sys/types.h>
#include<unistd.h>
#include<linux/kernel.h>


int main()
{    
	struct task_struct *myparent = current->parent;
	printf("My current process PID is : %d \n", getpid());
    
	printf("State of my parent is: %ld \n", myparent->state);
	return 0;
}

