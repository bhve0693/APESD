/*
* FileName        :    kthread_profile.c
* Description     :    This file contains kernel module for profiling of kthread_create
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
#include <linux/sched/task.h>
#include <linux/timex.h>
#include <linux/kthread.h>
#include <linux/time.h>

cycles_t start_time = 0;

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("kthread_profile");
MODULE_AUTHOR("Bhallaji-Venkatesan");

struct task_struct *kthread_prof;

int profile_thread(void *arg)
{
 	cycles_t end_time = get_jiffies_64();
 	printk(KERN_ALERT "\nProfiling time of kthreade_create : %llu jiffies\n",(end_time-start_time));
 	return 0;
}

static int __init kernmod_init(void)
{
    
    start_time = get_jiffies_64();
    kthread_prof = kthread_create(profile_thread, NULL, "kthread_prof");
    if(kthread_prof)
    {
    	printk(KERN_ALERT "\nValid Kernel Thread\n");
    	wake_up_process(kthread_prof);
    }

	return 0;
}

static void __exit kernmod_exit(void)
{
    printk(KERN_ALERT "Custom Kernel module exited in the kernel!\n");
}

module_init(kernmod_init);
module_exit(kernmod_exit);