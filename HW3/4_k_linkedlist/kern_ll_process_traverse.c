/*
* FileName        :    kern_ll_process_traverse.c
* Description     :    This file contains custom kernel module "kern_ll_process_traverse" 
*                        
* File Author Name:    Bhallaji Venkatesan 
* Tools used      :    gcc, gedit
* References      :    
*
*
*/

#include <linux/module.h> 
#include <linux/kernel.h> 
#include <linux/init.h> 
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/types.h>
#include <linux/list.h>
#include <uapi/linux/unistd.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("kern_process");
MODULE_AUTHOR("Bhallaji-Venkatesan");

static int __init kernmod_init(void)
{
	long long i = 0;
	long long p =0;
	struct task_struct *mycurrent = current;
	struct task_struct *myparent = current->parent;
	struct task_struct *temp;
	struct task_struct *temp1;
	current_thread_info();
    printk(KERN_ALERT "Custom Kernel module installed in the kernel!.\n"); 	
	printk(KERN_ALERT "My current process PID is : %d \n", current->pid);
	printk(KERN_ALERT "My current State  : %ld \n", current->state);
	printk(KERN_ALERT "My current process name  : %s \n", current->comm);
	printk(KERN_ALERT "My Parent process name  : %s \n", myparent->comm);
	printk(KERN_ALERT "My current Thread ID  : %d \n", current->tgid);
	printk(KERN_ALERT "My Parent Thread ID  : %d \n", myparent->tgid);
	printk(KERN_ALERT "State of my parent is: %ld \n", myparent->state);
    temp = myparent;
    for_each_process(mycurrent)
    {
    	printk(KERN_ALERT "My current process PID is : %d \n", mycurrent->pid);
    	printk(KERN_ALERT "My Parent process PID is : %d \n", mycurrent->parent->pid);
    	p++;
    }
     printk(KERN_ALERT "list with p%lld\n",p);
    while(temp->parent->pid != 1)
    {
       temp = temp->parent;
       	printk(KERN_ALERT "My current process PID is : %d \n", temp->pid);
		printk(KERN_ALERT "My current State  : %ld \n", temp->state);
		printk(KERN_ALERT "My current process name  : %s \n", temp->comm);
		printk(KERN_ALERT "My current Thread ID  : %d \n", temp->tgid);

       i++;
    }
    printk(KERN_ALERT "Done with i %lld\n",i);
    return 0;
}

static void __exit kernmod_exit(void)
{
    printk(KERN_ALERT "Custom Kernel module exited in the kernel!\n");
}

module_init(kernmod_init);
module_exit(kernmod_exit);