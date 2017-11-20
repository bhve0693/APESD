/*
* FileName        :    test_usrspace_char_driver.c
* Description     :    This file contains userspace test code for the custom led char driver
*                        
* File Author Name:    Bhallaji Venkatesan 
* Tools used      :    gcc, gedit
* References      :    http://derekmolloy.ie/kernel-gpio-programming-buttons-and-leds/
*
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#define CMD_LENGTH 3
 
 
int main(){
   int ret, fd;
   char *cmd;
   cmd = (char*)malloc(sizeof(char)*CMD_LENGTH);
   if(!cmd)
   {
   		perror("Unable to allocate memory\n");
   		return 1;
   }
   printf("Starting device test code example...\n");
   fd = open("/dev/ledchar", O_RDWR | O_SYNC);             // Open the device with read/write access
   if (fd < 0){
      perror("Failed to open the device...");
      return errno;
   }
   strncpy(cmd,"ON",2);               
   printf("Writing message to the device [%s].\n", cmd);
   ret = write(fd, cmd, strlen(cmd)); // Send the string to the LKM
   if (ret < 0){
      perror("Failed to write the message to the device.");
      return errno;
   }
 
   printf("Press ENTER to perform the next operation\n");
   getchar();
   strncpy(cmd,"OFF",3);               
   printf("Writing message to the device [%s].\n", cmd);
   ret = write(fd, cmd, strlen(cmd)); // Send the string to the LKM
   if (ret < 0){
      perror("Failed to write the message to the device.");
      return errno;
   }
   printf("End of the program\n");
   return 0;
}