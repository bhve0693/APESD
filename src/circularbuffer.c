/*

* FileName        :     circularbuffer.c
* Description     :    This file implements the following operations on a circular buffer
*                      with a double pointer implementation , the allocation of buffer, 
*		       addition and removal of nodes, full or empty status of buffer, dump
*                      ,searching a value in the nodes, size of the buffer and destroying of the buffer.
             
* File Author Name:    Bhallaji Venkatesan 
* Tools used      :    gcc, gdb, gedit
* References      :    https://embedjournal.com/implementing-circular-buffer-embedded-c/

*/


#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include "circularbuffer.h"

/*** Global Variable ***/
uint8_t wrap_around = 0;

/*** Functions ***/
enum Err_code allocate(struct cbuffer **buffer, uint32_t size)
{
  uint32_t *value_buff = malloc(sizeof(uint32_t)*size);
  struct cbuffer *temp = (struct cbuffer *)malloc(sizeof(struct cbuffer));
  if(!value_buff) //Malloc Fail
    return ERR_MALLOC_FAIL;
  
  temp->head = value_buff;
  temp->tail = value_buff;
  temp->base = value_buff;
  temp->size = size;
  temp->num_items = 0;
  *buffer= temp;

 
  return SUCCESS;
}

enum Err_code add_item(struct cbuffer **buffer,uint32_t item)
{
  uint8_t status =0;
  status = Is_buffer_full(buffer);
  if(!status) 
  {
    (*buffer)->head = (*buffer)->base;
    (*buffer)->num_items = (*buffer)->size;
    wrap_around = 1;
  }
  if(!wrap_around)
  {
    (*buffer)->num_items++;
  }
 
  *(*buffer)->head = item;
  printf("Item in add item %d \r\n",  *(*buffer)->head);
  
  (*buffer)->head++;
   return SUCCESS;
}
enum Err_code remove_item(struct cbuffer **buffer)
{
  int status =0;
  status = Is_buffer_empty(buffer);
  if(!status)
    return ERR_CBUFF_EMPTY;
  uint32_t *temp;
  temp = (*buffer)->tail;
  *(*buffer)->tail =0;
  (*buffer)->tail++;
  (*buffer)->num_items--;
  return SUCCESS;
}


uint32_t size(struct cbuffer **buffer)
{
  return ((*buffer)->num_items);
}

enum Err_code destroy(struct cbuffer **buffer)
{
  if(!(*buffer))
    return ERR_CBUFF_EMPTY;
  *buffer = NULL;
  free(*buffer);
  return SUCCESS;
}

void dump(struct cbuffer **buffer)
{
  uint32_t *temp;
  uint32_t index =0;
  printf("Head Value%u \r\n",*(*buffer)->head);
  printf("Tail Value %u \r\n",*(*buffer)->tail);
  printf("base Value %u \r\n",*(*buffer)->base);
  if((*buffer)->head > ((*buffer)->base +(*buffer)->size))
  {
    (*buffer)->head = (*buffer)->base;
  }
  if(wrap_around == 0)
  {
    temp = (*buffer)->tail;
    printf("Index -->");
    while (temp <= (*buffer)->head-1)
    {
      printf("%d | ",index);
      index++;
      temp++;
    }
    printf("\r\n");
    temp = (*buffer)->tail;
    printf("Value -->");
    while (temp <= (*buffer)->head-1)
    {
      printf("%d | ",*temp); 
      temp++;
    }
    printf("\r\n");
  }
  else
  {
    printf("Head %p \r\n",(*buffer)->head);
    printf("Tail %p \r\n",(*buffer)->tail);
    printf("base %p \r\n",(*buffer)->base);
    temp = (*buffer)->tail;
    index = 0;
    printf("Index -->");
     while(temp != ((*buffer)->base + (*buffer)->size))
    {
      printf("%d |", index);
      index++;
      temp++;
    }
    printf("\r\n");
    printf("Value -->");
    temp = (*buffer)->tail;
    while(temp != ((*buffer)->base + (*buffer)->size))
    {
      printf("%d |", *temp);
      temp++;
    }
    printf("\r\n");
  }

}

uint8_t Is_buffer_empty(struct cbuffer **buffer)
{
  if((*buffer)->num_items == 0)
  {
    return 0;
  }
  return 1;
}

uint8_t Is_buffer_full(struct cbuffer **buffer)
{
  if((*buffer)->head == ((*buffer)->base +(*buffer)->size))
  {
    return 0;
  }
  return 1;
}
void cbuffer_menu()
{
  struct cbuffer *header;
  enum Err_code status= 0;
  uint32_t item,size_buffer,ch;
  printf("Enter the size of buffer to be allocated:");
  scanf("%u",&size_buffer);
  status = allocate(&header,size_buffer);
  if(status == ERR_MALLOC_FAIL)
  {
    printf("Malloc Failure\n");
    exit(0);
  }
  printf("Enter your choice(1-6)\n1.Add\n2.Remove\n3.Dump\n");
  printf("4.Get size of list\n5.Delete buffer\n6.Exit\n");
  scanf("%u",&ch);
  while(ch!=6)
  {   
    switch(ch)
    {
      case 1: printf("Enter the item to be added :");
              scanf("%u",&item);
              status = add_item(&header,item);
              if(!status)
              {
                printf("Added Successfully \n");
              }
              break;
      case 2: status = remove_item(&header);
              if(status  == 1)
              {
                printf("Nothing to remove in Empty Buffer! \n");
              }
              break;

      case 3: dump(&header);
              break;

      case 4: size_buffer = 0;
              size_buffer=size(&header);
              printf("Number of items in buffer :%u\n",size_buffer);               
              break;
      case 5: status=destroy(&header);
              if(!status)
	      {
	        printf("Succesfully destroyed\n");
	      }	
              else 
	      {
                printf("No buffer to destroy\r\n");
	      }
              break;
   
     case 6: exit(0);
     
     default: printf("Invalid Request. Please Request again! \r\n");
              break;
   }
   printf("Enter your choice(1-6)\n1.Add\n2.Remove\n3.Dump\n");
   printf("4.Get size of list\n5.Delete buffer\n6.Exit\n");
   scanf("%u",&ch);
   }
}
int main()
{
  cbuffer_menu();
  return 0;
}


