/*
* FileName        :    multithreaded_io.c
* Description     :    This file contains multithreaded file I/O implementation 
*                        
* File Author Name:    Bhallaji Venkatesan 
* Tools used      :    gcc, gedit
* References      :    
*
*
*/


#include <stdio.h>
#include <string.h>
#include <pthread.h>
long file_size = 0;
void *f_write(void *arg)
{
	printf("\n Entering Write Thread \n");
	//long d = (long)(arg);
	//printf("\n Long is %ld\n",d); 
	char *temp_buff = malloc(sizeof(char)*1024);
	char **new_file = (char **)arg;
	printf("Enter the contens to be written into the file\n");
    fgets(temp_buff, 1024*sizeof(char),stdin);
    printf("\n temp buff is %s \n", temp_buff);
    printf("strlen is %d", strlen(temp_buff));
    printf("Size of tempbuff is %ld and size of char is %ld\n", sizeof(temp_buff), sizeof(char));
  	FILE *fp;
  	fp = fopen(new_file, "w+");
  	fwrite(temp_buff, 1, strlen(temp_buff)*sizeof(char),fp);

  	/*for(int i = 2; i<argc; i++)
  	{

  		fwrite(argv[i], 1, sizeof(argv[i])*sizeof(char),fp);

    }*/
    fclose(fp);
    fp = fopen(new_file, "r+");
    file_size = strlen(temp_buff);
    char *buff = malloc(strlen(temp_buff)*sizeof(char));
    while(!feof(fp))
    {
    	fread(buff, 1,strlen(temp_buff)*sizeof(char),fp);
    }
    printf("File size in write thread is %ld \n", file_size);
    printf("\nBuff is %s\n",buff);
    fclose(fp);
    pthread_exit(NULL);

}

void *f_read(void *arg)
{
	printf("\n Entering Read Thread \n");
	char **new_file = (char **)arg;
	//char new_file[] = {"testing.txt"};
	char ch;
	int count_line, count_char, count_word;
	count_line = 0;
	count_char = 0;
	count_word = 0;
    FILE *fp;
  	fp = fopen(new_file, "r+");
    //printf("\nvalue of fp is %ld",fp);
  	
  	//printf("File size is %d" , file_size);
  	//char *buff = malloc(file_size*sizeof(char));
    while((ch = getc(fp)) != EOF)
    {
    	
    	if((ch != ' ')|| (ch != '\n'))
    	{
    		count_char++;
    	}
    	if((ch == ' ')||(ch == '\n'))
    	{
    		count_word++;
    	}
    	if((ch == '\n'))
    	{
    		count_line++;
    	}
    	//fread(buff, 1,file_size*sizeof(char),fp);
    }
    //printf("\nBuff is %s\n",buff);
    printf("\nCharacter Count is %d\n",count_char-1);
    printf("\nWord Count is %d\n",count_word);
    printf("\nLine Count is %d\n",count_line);
    fclose(fp);
    pthread_exit(NULL);
}

int main(int argc , char **argv)
{
	//char *temp_buff = malloc(sizeof(char)*1024);
	pthread_attr_t attr;
	pthread_t thread_fwrite,thread_fread;
	if (argc <= 2)
  	{
    	printf ("USAGE:  <Filename> <Data to be written>\n");
    	exit(1);
  	}
    long a =10;
  //	char **new_file = argv[1];
  	pthread_attr_init(&attr);
  	pthread_create(&thread_fwrite, NULL, &f_write, (void *)argv[1]);
    pthread_join(thread_fwrite, NULL);
    pthread_create(&thread_fread, NULL, &f_read, (void *)argv[1]);

  	pthread_exit(NULL);

  /*	printf("Enter the contens to be written into the file\n");
    fgets(temp_buff, 1024*sizeof(char),stdin);
    printf("\n temp buff is %s \n", temp_buff);
    printf("strlen is %d", strlen(temp_buff));
    printf("Size of tempbuff is %ld and size of char is %ld\n", sizeof(temp_buff), sizeof(char));
  	FILE *fp;
  	fp = fopen(new_file, "w+");
  	fwrite(temp_buff, 1, strlen(temp_buff)*sizeof(char),fp);

  	/*for(int i = 2; i<argc; i++)
  	{

  		fwrite(argv[i], 1, sizeof(argv[i])*sizeof(char),fp);

    }*/
  /*  fclose(fp);
    fp = fopen(new_file, "r+");
    char *buff = malloc(strlen(temp_buff)*sizeof(char));
    while(!feof(fp))
    {
    	fread(buff, strlen(temp_buff)*sizeof(char),1,fp);
    }
    printf("\nBuff is %s\n",buff);
    fclose(fp);*/
    return 0;
}