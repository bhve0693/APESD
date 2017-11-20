/*
* FileName        :    kern_char_driver.c
* Description     :    This file contains custom kernel module "char_led_driver" as an LKM for a char LED Driver for BBG 
*                        
* File Author Name:    Bhallaji Venkatesan 
* Tools used      :    gcc, gedit
* References      :    http://derekmolloy.ie/kernel-gpio-programming-buttons-and-leds/
*
*
*/



#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>       // Required for the GPIO functions
#include <linux/device.h>
#include <linux/delay.h> // Using this header for the msleep() function
#include <linux/timer.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/gfp.h>


#define  DEVICE_NAME "ledchar"    ///< The device will appear at /dev/ledchar using this value
#define  CLASS_NAME  "led"        ///< The device class -- this is a character device driver
#define  LEDON  1
#define  LEDOFF 0


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bhallaji Venkatesan ");
MODULE_DESCRIPTION("USR LED Char driver for BBG");
MODULE_VERSION("0.1");

static int    majorNumber;                  ///< Stores the device number -- determined automatically
static char   message[256] = {0};           ///< Memory for the string that is passed from userspace
static short  size_of_message;              ///< Used to remember the size of the string stored
static int    numberOpens = 0;              ///< Counts the number of times the device is opened
static struct class*  ledcharClass  = NULL; ///< The device-driver class struct pointer
static struct device* ledcharDevice = NULL; ///< The device-driver device struct pointer
static unsigned int gpioLED = 55; ///< hard coding the LED gpio for this driver to GPIO55
static uint8_t ledstate = 0;

// The prototype functions for the character driver -- must come before the struct definition
static int     dev_open(struct inode *, struct file *);
static int     dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);
 
/** @brief Devices are represented as file structure in the kernel. The file_operations structure from
 *  /linux/fs.h lists the callback functions that you wish to associated with your file operations
 *  using a C99 syntax structure. char devices usually implement open, read, write and release calls
 */
static struct file_operations fops =
{
   .open = dev_open,
   .read = dev_read,
   .write = dev_write,
   .release = dev_release,
};
 
/** @brief The LKM initialization function
 *  The static keyword restricts the visibility of the function to within this C file. The __init
 *  macro means that for a built-in driver (not a LKM) the function is only used at initialization
 *  time and that it can be discarded and its memory freed up after that point.
 *  @return returns 0 if successful
 */
static int __init ledchar_init(void){

   if(!gpio_is_valid(gpioLED))
   {
   		printk(KERN_ERR "Invalid GPIO\n");
   		return -ENODEV;
   }	
   gpio_request(gpioLED, "sysfs");          // gpioLED is hardcoded to 55, request it
   gpio_direction_output(gpioLED, LEDON);   // Set the gpio to be in output mode and on
   gpio_export(gpioLED, false); // Causes gpio55 to appear in /sys/class/gpio
   printk(KERN_INFO "LEDChar: Initializing the LEDChar LKM\n");
 
   // Try to dynamically allocate a major number for the device -- more difficult but worth it
   majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
   if (majorNumber<0){
      printk(KERN_ALERT "LEDChar failed to register a major number\n");
      return majorNumber;
   }
   printk(KERN_INFO "LEDChar: registered correctly with major number %d\n", majorNumber);
 
   // Register the device class
   ledcharClass = class_create(THIS_MODULE, CLASS_NAME);
   if (IS_ERR(ledcharClass)){                // Check for error and clean up if there is
      unregister_chrdev(majorNumber, DEVICE_NAME);
      printk(KERN_ALERT "Failed to register device class\n");
      return PTR_ERR(ledcharClass);          // Correct way to return an error on a pointer
   }
   printk(KERN_INFO "LEDChar: device class registered correctly\n");
 
   // Register the device driver
   ledcharDevice = device_create(ledcharClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
   if (IS_ERR(ledcharDevice)){               // Clean up if there is an error
      class_destroy(ledcharClass);           // Repeated code but the alternative is goto statements
      unregister_chrdev(majorNumber, DEVICE_NAME);
      printk(KERN_ALERT "Failed to create the device\n");
      return PTR_ERR(ledcharDevice);
   }
   printk(KERN_INFO "LEDChar: device class created correctly\n"); // Made it! device was initialized
   return 0;
}
 
/** @brief The LKM cleanup function
 *  Similar to the initialization function, it is static. The __exit macro notifies that if this
 *  code is used for a built-in driver (not a LKM) that this function is not required.
 */
static void __exit ledchar_exit(void){
   gpio_set_value(gpioLED, 0);              // Turn the LED off, makes it clear the device was unloaded
   gpio_unexport(gpioLED);                  // Unexport the LED GPIO
   gpio_free(gpioLED); // Free the LED GPIO
   device_destroy(ledcharClass, MKDEV(majorNumber, 0));     // remove the device
   class_unregister(ledcharClass);                          // unregister the device class
   class_destroy(ledcharClass);                             // remove the device class
   unregister_chrdev(majorNumber, DEVICE_NAME);             // unregister the major number
   printk(KERN_INFO "LEDChar: Goodbye from the LKM!\n");
}
 
/** @brief The device open function that is called each time the device is opened
 *  This will only increment the numberOpens counter in this case.
 *  @param inodep A pointer to an inode object (defined in linux/fs.h)
 *  @param filep A pointer to a file object (defined in linux/fs.h)
 */
static int dev_open(struct inode *inodep, struct file *filep){
   numberOpens++;
   printk(KERN_INFO "LEDChar: Device has been opened %d time(s)\n", numberOpens);
   return 0;
}
 
/** @brief This function is called whenever device is being read from user space i.e. data is
 *  being sent from the device to the user. In this case is uses the copy_to_user() function to
 *  send the buffer string to the user and captures any errors.
 *  @param filep A pointer to a file object (defined in linux/fs.h)
 *  @param buffer The pointer to the buffer to which this function writes the data
 *  @param len The length of the b
 *  @param offset The offset if required
 */
static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset){
   int error_count = 0;
   // copy_to_user has the format ( * to, *from, size) and returns 0 on success
   error_count = copy_to_user(buffer, message, size_of_message);
 
   if (error_count==0){            // if true then have success
      printk(KERN_INFO "LEDChar: Sent %d characters to the user\n", size_of_message);
      return (size_of_message=0);  // clear the position to the start and return 0
   }
   else {
      printk(KERN_INFO "LEDChar: Failed to send %d characters to the user\n", error_count);
      return -EFAULT;              // Failed -- return a bad address message (i.e. -14)
   }
}
 
/** @brief This function is called whenever the device is being written to from user space i.e.
 *  data is sent to the device from the user. The data is copied to the message[] array in this
 *  LKM using the sprintf() function along with the length of the string.
 *  @param filep A pointer to a file object
 *  @param buffer The buffer to that contains the string to write to the device
 *  @param len The length of the array of data that is being passed in the const char buffer
 *  @param offset The offset if required
 */
static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset)
{
   unsigned long status = 0;
   char *in_kbuff;
   if(!len)
   {
   		printk(KERN_ALERT "Invalid Input String Length\n");
   		return 1;	
   }
   in_kbuff  = (char*)kmalloc((sizeof(char)*len),GFP_KERNEL);
   if(!in_kbuff)
   {
     printk(KERN_ALERT "Error ID %d: Unable to allocate Kernel Memory \n",EINVAL);
     return EFAULT;
   }
   status = copy_from_user(in_kbuff,buffer,(sizeof(char)*len));
   if(status !=0)
   { 
     if(status == (sizeof(char)*len))
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
   if((!strncmp(in_kbuff,"ON",2)) || (!strncmp(in_kbuff,"On",2)) || (!strncmp(in_kbuff,"on",2)) || (!strncmp(in_kbuff,"1",1)))
   {
   		ledstate = LEDON;
   		gpio_set_value(gpioLED,LEDON);
   		printk(KERN_ALERT "LED Is ON\n");

   }
   else if((!strncmp(in_kbuff,"OFF",3)) || (!strncmp(in_kbuff,"Off",3)) || (!strncmp(in_kbuff,"off",3)) || (!strncmp(in_kbuff,"0",1)))
   {
   		ledstate = LEDOFF;
   		gpio_set_value(gpioLED,LEDOFF);
   		printk(KERN_ALERT "LED Is OFF\n");   	
   }
   else
   {
   		printk(KERN_ALERT "Invalid Command from Userspace\n");
   }

   return 0;
}
 
/** @brief The device release function that is called whenever the device is closed/released by
 *  the userspace program
 *  @param inodep A pointer to an inode object (defined in linux/fs.h)
 *  @param filep A pointer to a file object (defined in linux/fs.h)
 */
static int dev_release(struct inode *inodep, struct file *filep){
   printk(KERN_INFO "LEDChar: Device successfully closed\n");
   return 0;
}
 
/** @brief A module must use the module_init() module_exit() macros from linux/init.h, which
 *  identify the initialization function at insertion time and the cleanup function (as
 *  listed above)
 */
module_init(ledchar_init);
module_exit(ledchar_exit);


