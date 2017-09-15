#include <linux/module.h> 
#include <linux/kernel.h> 
#include <linux/init.h> 
#include <linux/timer.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kern_modtest");
MODULE_AUTHOR("Bhallaji-Venkatesan");

int k_time_interval = 500;
struct timer_list k_timer;
static long time_count_keep = 0;
void _Timercallback(unsigned long data)
{
    /*Restarting the timer...*/
    time_count_keep++;
    mod_timer( &k_timer, jiffies + msecs_to_jiffies(k_time_interval));

    printk(KERN_ALERT "Timer Handler called %lu times.\n",time_count_keep);
}
 
static int __init kernmod_init(void)
{

    printk(KERN_ALERT "Custom Kernel module installed in the kernel!.\n");

    /*Starting the timer.*/
    init_timer(&k_timer);
    k_timer.data = 0;
    k_timer.function = _Timercallback;
    k_timer.expires =  jiffies + msecs_to_jiffies(k_time_interval);
    add_timer(&k_timer);
    return 0;
}

static void __exit kernmod_exit(void)
{
    del_timer_sync(&k_timer);
    printk(KERN_ALERT "Custom Kernel module exited in the kernel!\n");
}

module_init(kernmod_init);
module_exit(kernmod_exit);
