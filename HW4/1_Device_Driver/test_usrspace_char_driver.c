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
#include <sys/socket.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <signal.h>
#define CMD_LENGTH 100
#define READ_LENGTH 5
int fd,sd;
char *read_ledstate;
char *read_dutycycle;
char *read_frequency;
char *temp_ptr;

void exit_handler(int sig) {
    if (sig != SIGINT) {
        printf("Received invalid signum = %d in exit_handler()\n", sig);
        exit(0);
    }
    printf("Received SIGINT. Exiting Application\n");
    //if(fp!=NULL)
    close(fd);
    close(sd);
    exit(0);
}

 
int main(){

  int connfd,len;
  long count,read_len =0;
  struct sockaddr_in servaddr,cliaddr;
  char *frame_recv;
  frame_recv= (char*)malloc(sizeof(char)*1024);
   int ret;
   char *cmd;
   int duty_cycle = 0;
   int frequency = 0;
   char readbuff[100];
   signal(SIGINT,exit_handler);
   cmd = (char*)malloc(sizeof(char)*CMD_LENGTH);
   read_ledstate = (char*)malloc(sizeof(char)*READ_LENGTH);
   read_dutycycle = (char*)malloc(sizeof(char)*READ_LENGTH);
   read_frequency = (char*)malloc(sizeof(char)*READ_LENGTH);
   temp_ptr = (char*)malloc(sizeof(char)*100);

  sd = socket(AF_INET, SOCK_DGRAM, 0);
 
  if(sd==-1)
    {
      printf(" socket not created in server\n");
      exit(0);
    }
  else
    {
      printf("socket created in  server\n");
    }
 
  bzero(&servaddr, sizeof(servaddr));
 
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(8001);
    struct timeval tv;
  tv.tv_sec = 70;
tv.tv_usec = 0;
    if (setsockopt(sd, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) {
    perror("Error");
  }
 
  if ( bind(sd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0 )
    printf("Not binded\n");
  else
    printf("Binded\n");
  len=sizeof(cliaddr);
  while(1)
  {
    printf("\n Waiting for command from client\n");
  recvfrom(sd,frame_recv,sizeof(char)*10,0,(struct sockaddr *)&servaddr, &len);
  printf("\nRecvd Frame is %s\n",frame_recv);

  //exit_handler(SIGINT);


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

   if(!strncmp(frame_recv,"ON",2))
   {
     strncpy(cmd,"ON",2);               
     printf("Writing message to the device [%s].\n", cmd);
     ret = write(fd, cmd, strlen(cmd)); // Send the string to the LKM
     if (ret < 0){
        perror("Failed to write the message to the device.");
        return errno;
     }
 }
  bzero(readbuff,sizeof(readbuff));
  //Write ON

  //Write OFF
  //Write Frequency
  //Write DutyCycle

  //Read All 
  //Read LED State
  //Read Dutycycle
  //Read Frequency





   //getchar();
   if(!strncmp(frame_recv,"OFF",3))
   {
     strncpy(cmd,"OFF",3);               
     printf("Writing message to the device [%s].\n", cmd);
     ret = write(fd, cmd, strlen(cmd)); // Send the string to the LKM
     if (ret < 0){
        perror("Failed to write the message to the device.");
        return errno;
     }
 }
   bzero(cmd,sizeof(cmd));

   if(!strncmp(frame_recv,"DUTY",4))
   {
     printf("Enter the required duty cycle value (0 - 100)\n");
     scanf("%d",&duty_cycle);
     if(!((duty_cycle>=0)|| duty_cycle <=100))
      printf("Invalid duty cycle");
    else 
    {
      sprintf(cmd,"DUTY:%d",duty_cycle);
      ret = write(fd,cmd,strlen(cmd));
    }
}
bzero(cmd,sizeof(cmd));


  if(!strncmp(frame_recv,"FREQ",4))
   {
    printf("Enter the required Frequency value\n");
     scanf("%d",&frequency);
     if(!((frequency>=0)|| frequency <=5000))
      printf("Invalid frequence");
    else 
    {
      sprintf(cmd,"FREQ:%d",frequency);
      ret = write(fd,cmd,strlen(cmd));
    }
}
   bzero(cmd,sizeof(cmd));

   if(!strncmp(frame_recv,"READALL",7))
   {

     ret = read(fd,readbuff,100);
     printf("\nReadbuff value is %s",readbuff);
     temp_ptr = readbuff;
     read_ledstate = strsep(&temp_ptr," ");
     read_dutycycle = strsep(&temp_ptr," ");
     read_frequency = strsep(&temp_ptr," ");

     printf("Light State is %s \n",read_ledstate);
     printf("Duty Cycle %s \n",read_dutycycle);
     printf("Frequency is %s \n",read_frequency);
    }
    bzero(cmd,sizeof(cmd));
     if(!strncmp(frame_recv,"READDUTY",8))
   {
     strncpy(cmd,"READDUTY",8);               
     printf("Writing message to the device [%s].\n", cmd);
     ret = write(fd, cmd, strlen(cmd)); // Send the string to the LKM
     if (ret < 0){
        perror("Failed to write the message to the device.");
        return errno;
     }

     ret = read(fd,readbuff,100);
     printf("\nReadbuff value is %s",readbuff);
     temp_ptr = readbuff;
      
     printf("Duty Cycle %s \n",readbuff);
   
    }
    if(!strncmp(frame_recv,"READSTATE",9))
   {
     strncpy(cmd,"READSTATE",9);               
     printf("Writing message to the device [%s].\n", cmd);
     ret = write(fd, cmd, strlen(cmd)); // Send the string to the LKM
     if (ret < 0){
        perror("Failed to write the message to the device.");
        return errno;
     }

     ret = read(fd,readbuff,100);
     printf("\nReadbuff value is %s",readbuff);
     temp_ptr = readbuff;
     

     printf("Light State is %s \n",readbuff);
    }
    bzero(cmd,sizeof(cmd));
   
    bzero(cmd,sizeof(cmd));
    if(!strncmp(frame_recv,"READPERIOD",10))
   {

     strncpy(cmd,"READPERIOD",10);               
     printf("Writing message to the device [%s].\n", cmd);
     ret = write(fd, cmd, strlen(cmd)); // Send the string to the LKM
     if (ret < 0){
        perror("Failed to write the message to the device.");
        return errno;
     }

     ret = read(fd,readbuff,100);
     printf("\nReadbuff value is %s",readbuff);
     temp_ptr = readbuff;
    

     printf("Frequency (1/T) is %s \n",readbuff);

    }

}
   printf("End of the program\n");
   exit_handler(SIGINT);
   return 0;
}