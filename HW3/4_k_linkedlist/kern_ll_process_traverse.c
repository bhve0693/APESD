/*
* FileName        :    kern_ll_process_traverse.c
* Description     :    This file contains custom kernel module "kern_ll_process_traverse" 
*                        
* File Author Name:    Bhallaji Venkatesan 
* Tools used      :    gcc, gedit
* References      :    https://isis.poly.edu/kulesh/stuff/src/klist/
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

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("kern_process");
MODULE_AUTHOR("Bhallaji-Venkatesan");

static int __init kernmod_init(void)
{
	long long i = 0;
	int k = 0;
  int count_child = 0;
  int count_sibling = 0;
	struct task_struct *mycurrent = current;
	struct task_struct *temp;
  struct list_head *list;
  struct list_head *list_new;
	current_thread_info();
  printk(KERN_ALERT "Custom Kernel module installed in the kernel!.\n"); 	
  temp = mycurrent;
  while(temp != &init_task)
  {
       
      list_for_each(list, &temp->children)
      {
         count_child++;
      }
      list_for_each(list, &temp->sibling)
      {
         count_sibling++;
      }
      printk(KERN_ALERT "My current process PID is : %d \n", temp->pid);
		  printk(KERN_ALERT "My current State  : %ld \n", temp->state);
		  printk(KERN_ALERT "My current process name  : %s \n", temp->comm); 
		  printk(KERN_ALERT "My current Thread Group ID  : %d \n", temp->tgid);
      printk(KERN_ALERT "No. of Children of this process : %d \n", count_child);
      printk(KERN_ALERT "No. of Siblings for this process : %d \n", count_sibling);
      count_child = 0;
      count_sibling = 0;
      temp = temp->parent; 
       
  }

  return 0;
}

static void __exit kernmod_exit(void)
{
    printk(KERN_ALERT "Custom Kernel module exited in the kernel!\n");
}

module_init(kernmod_init);
module_exit(kernmod_exit);