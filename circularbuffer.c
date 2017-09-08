#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
struct cbuffer{
//uint32_t *const buffer;
uint32_t *head;
uint32_t *tail;
uint32_t *base;
uint32_t size;
uint32_t num_items;
};


uint8_t wrap_around = 0;
uint8_t allocate(struct cbuffer **buffer,uint32_t size);
uint8_t destroy(uint32_t **buffer);
uint8_t Is_buffer_full(struct cbuffer **buffer);
uint8_t Is_buffer_empty(struct cbuffer **buffer);
uint8_t add_item(struct cbuffer **buffer,uint32_t item);
uint8_t remove_item(struct cbuffer **buffer);
void dump(struct cbuffer **buffer);
uint8_t size(uint32_t **buffer); 


uint8_t allocate(struct cbuffer **buffer, uint32_t size)
{
 uint32_t *value_buff = malloc(sizeof(uint32_t)*size);
 if(!value_buff)
  return 1;

 (*buffer)->head = value_buff;
 (*buffer)->tail = value_buff;
 (*buffer)->base = value_buff;
 (*buffer)->size = size;
 (*buffer)->num_items = 0;

 return 0;
}

uint8_t add_item(struct cbuffer **buffer,uint32_t item)
{
uint8_t status =0;
status = Is_buffer_full(buffer);
if(!status)
{
(*buffer)->head = (*buffer)->base;
(*buffer)->num_items = 0;
//(*buffer)->num_items = (*buffer)->size;
//printf("Number of items:%d",(*buffer)->num_items);
wrap_around = 1;
}

 *(*buffer)->head = item;
 printf("Item in add item %d \r\n",  *(*buffer)->head);
  (*buffer)->head++;
  (*buffer)->num_items++;
 // if((*buffer)->num_items > (*buffer)->size)
 //	(*buffer)->num_items = (*buffer)->size;
  return 0;
}
uint8_t remove_item(struct cbuffer **buffer)
{
 int status =0;
 status = Is_buffer_empty(buffer);
 printf("No. of items %d \r\n", (*buffer)->num_items);
 if(!status)
    return 1;
 uint32_t *temp;
 temp = (*buffer)->tail;
 (*buffer)->tail++;
 (*buffer)->num_items--;
  return 0;
}

void dump(struct cbuffer **buffer)
{
 uint32_t *temp;
 uint32_t index =0;
if(wrap_around == 0)
{
 temp = (*buffer)->tail;
 //temp = (*buffer)->head-1;
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
  // printf("else case\r\n");
   temp = (*buffer)->base;
   index = (*buffer)->size;
   //index = (*buffer)->num_items;
   printf("Index:%d",index);
   while(index)
   {
        printf(" %d | ",*temp);
	temp++;
        index --;

   }
   printf("\r\n");
}

}

uint8_t Is_buffer_empty(struct cbuffer **buffer)
{
 if((*buffer)->num_items == 0)
      return 0;
 return 1;
}

uint8_t Is_buffer_full(struct cbuffer **buffer)
{
  //if((*buffer)->head == ((*buffer)->base +(*buffer)->size))
   if((*buffer)->num_items == (*buffer)->size)
      //(*buffer)->num_items = (*buffer)->size;
      return 0;
 return 1;
}
void main()
{
struct cbuffer *header;
uint8_t status= 0;
status = allocate(&header,3);
printf("Status %d\r\n",status);
add_item(&header,5);
add_item(&header,6);
add_item(&header,7);

dump(&header);
add_item(&header,8);
dump(&header);
add_item(&header,9);
dump(&header);
//printf("Tail is %d\r\n",*header->tail);
status = remove_item(&header);
printf("Remove Status %d\r\n",status);
status = remove_item(&header);
printf("Remove Status %d\r\n",status);
status = remove_item(&header);
printf("Remove Status %d\r\n",status);
dump(&header);

//printf("Tail is %d\r\n",*header->tail);


}


