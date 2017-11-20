/*
* FileName        :    test_client.c
* Description     :    This file contains UDP Client that test custom kernel module "char_led_driver" as an LKM for a char LED Driver for BBG 
*					   by interacting with USP Test application.
*                        
* File Author Name:    Bhallaji Venkatesan 
* Tools used      :    gcc, gedit
* References      :    http://derekmolloy.ie/kernel-gpio-programming-buttons-and-leds/
*
*
*/

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <stdlib.h>
#include <memory.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <netinet/in.h>
#include <string.h> 
#include <dirent.h>
int sockfd;
void exit_handler(int sig)
{
	if(sig !=SIGINT)
	{
		exit(1);
	}
	close(sockfd);
	exit(0);
}

int main(int argc, char * argv[])
{

    char buff[2000];
	int connfd,len;
	char *frame_send;
	frame_send = (char*)malloc(sizeof(char)*1024);
	struct sockaddr_in servaddr,cliaddr;
	signal(SIGINT,exit_handler);
	    if (argc < 3)
	   {
	      printf("USAGE:  <server_ip> <server_port>\n");
	      exit(1);
	   }

	    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	    if(sockfd==-1)
	    {
	      printf(" socket not created in client\n");
	      exit(0);
	    }
	    else
	   {
	      printf("socket created in  client\n");
	   }
	   bzero(&servaddr, sizeof(servaddr)); 
	   servaddr.sin_family = AF_INET;
	   servaddr.sin_addr.s_addr = inet_addr(argv[1]);  // ANY address or use specific address
	   servaddr.sin_port =    htons(atoi(argv[2]));  // Port address
	   
	      struct timeval tv;
          tv.tv_sec = 50;
          tv.tv_usec = 0;
	  if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) {
	    perror("Error");
	   
	    
	}
	 strcpy(frame_send,"ON");
	 printf("Sending Frame %s \n",frame_send);
	 sendto(sockfd, frame_send, sizeof(char)*1024, 0,(struct sockaddr *)&servaddr, sizeof(struct sockaddr));
	 usleep(5000000);
	 bzero(frame_send,sizeof(frame_send));
	 strcpy(frame_send,"OFF");
	 printf("Sending Frame %s \n",frame_send);
	 sendto(sockfd, frame_send, sizeof(char)*1024, 0,(struct sockaddr *)&servaddr, sizeof(struct sockaddr));
	 usleep(5000000); 
	 strcpy(frame_send,"DUTY");
	 printf("Sending Frame %s \n",frame_send);
	 sendto(sockfd, frame_send, sizeof(char)*1024, 0,(struct sockaddr *)&servaddr, sizeof(struct sockaddr));
	 usleep(50000000);  
	 strcpy(frame_send,"FREQ");
	 printf("Sending Frame %s \n",frame_send);
	 sendto(sockfd, frame_send, sizeof(char)*1024, 0,(struct sockaddr *)&servaddr, sizeof(struct sockaddr));
	 usleep(50000000);
     strcpy(frame_send,"READALL");
	 printf("Sending Frame %s \n",frame_send);
	 sendto(sockfd, frame_send, sizeof(char)*1024, 0,(struct sockaddr *)&servaddr, sizeof(struct sockaddr));
	 usleep(500000);
	 bzero(frame_send,sizeof(frame_send));
	 strcpy(frame_send,"READSTATE");
	 printf("Sending Frame %s \n",frame_send);
	 sendto(sockfd, frame_send, sizeof(char)*1024, 0,(struct sockaddr *)&servaddr, sizeof(struct sockaddr));
	 usleep(500000);
	 bzero(frame_send,sizeof(frame_send));
	/* strcpy(frame_send,"READDUTY");
	 printf("Sending Frame %s \n",frame_send);
	 sendto(sockfd, frame_send, sizeof(char)*1024, 0,(struct sockaddr *)&servaddr, sizeof(struct sockaddr));
	 usleep(500000);*/
	  bzero(frame_send,sizeof(frame_send));
	      strcpy(frame_send,"READPERIOD");
	 printf("Sending Frame %s \n",frame_send);
	 sendto(sockfd, frame_send, sizeof(char)*1024, 0,(struct sockaddr *)&servaddr, sizeof(struct sockaddr));
	 usleep(500000);

	close(sockfd);
}