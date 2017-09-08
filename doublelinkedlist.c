/*
@Brief : Addition, Removal of Nodes and searching a value in Double-Linked List with double pointer Implementation
@Author: Bhallaji Venkatesan 
@Purpose: Homework 1 Code for Advanced Practical Embedded Software Design
@Mentor : Mr. Alex Fosdick, Instructor, The University of Colorado Boulder
*/


#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#define HEAD 0
//typedef uint8_t STATUS 

struct NODE{
uint32_t element;
struct NODE *prev;
struct NODE *next;
};
uint32_t global_index = 0;
/*
enum STATUS{
0,1,
};*/
/*


uint8_t destroy(struct NODE **hdnode_ptr);
uint8_t add_node(struct NODE **hdnode_ptr, uint32_t data, uint32_t index);
uint8_t remove_node(struct NODE **bsnode_ptr, uint32_t data, uint32_t index);
void search(struct NODE **node_ptr, uint32_t data, uint32_t *index);
uint32_t size(struct NODE **hdnode_ptr);

uint8_t destroy(struct NODE **hdnode_ptr)
{
 
struct NODE *temp = (struct NODE *)malloc(sizeof(struct NODE));


if (!(*hdnode_ptr))
    return 1; /*if no nodes are present */
/*
else 
    {
         while(*hdnode_ptr)
	 {
		
	     temp = *hdnode_ptr;
	     *hdnode_ptr = temp->next;
	     free(temp);	
	 }
	 global_index = 0;
	 return 0;
     }
}
*/
uint8_t add_node(struct NODE **hdnode_ptr, uint32_t data, uint32_t index)
{
  struct NODE *new_node = (struct NODE *)malloc(sizeof(struct NODE));
  struct NODE *temp;
  //malloc fail Case 
  if(!new_node)
     return 1;

  new_node->element = data;
  
  
  if(index > (global_index+1)) //Invalid Index
     return 2;

  else
  {
 
    //No Head Case
    if(!(*hdnode_ptr))
    {
        new_node->next = NULL;
        new_node->prev = NULL;
        *hdnode_ptr = new_node;
        global_index++;
        return 0;
    }
  
    //Adding at Head Node
    if(!index)
    {
        new_node->next = *hdnode_ptr;
        new_node->prev = NULL;
        (*hdnode_ptr)->prev = new_node;
	*hdnode_ptr = new_node;
        global_index++;
        return 0;
    }
    if(index == global_index) //Adding New Node at Tail
    {
        temp = *hdnode_ptr;
        while(temp->next)
        {
	     temp = temp->next;	
        }
        new_node->prev = temp;
        new_node->next = NULL;
        temp->next = new_node;
        global_index++;
        return 0; 
    }
    //Any general Node
    else
    {  
        temp = *hdnode_ptr;
        while((index >=1))
        {
            temp=temp->next;
            index--;
        }
        new_node->next = temp;
        new_node->prev = temp->prev;
        temp->prev = new_node;
	new_node->prev->next = new_node;
        global_index++;
        return 0;
     }
  }// Valid Index
}//Function


uint8_t remove_node(struct NODE **hdnode_ptr, uint32_t index)
{
  struct NODE *new_node = (struct NODE *)malloc(sizeof(struct NODE));
  struct NODE *temp,*temp_remove;

  
  
  if(index > (global_index)) //Invalid Index
     return 2;

  else
  {
 
    //No Head Case
    if(!(*hdnode_ptr))
    {
        return 1;
    }
  
    //Removing Head Node
    if(!index)
    {
        temp = (*hdnode_ptr)->next;
        (*hdnode_ptr)->next = NULL;
	*hdnode_ptr = temp;
        global_index--;
        return 0;
    }
    if(index == global_index) //Removing Node at Tail
    {
	
        temp = *hdnode_ptr;
        while(temp->next)
        {
	     temp = temp->next;	
        }
	temp->prev->next = NULL;
	temp = NULL;
        global_index--;
        return 0; 
    }
    //Removing Any general Node
    else
    {  
        temp = *hdnode_ptr;
        while((index >=1))
        {
            temp=temp->next;
            index--;
        }

        temp->next->prev = temp->prev;
        temp->prev->next = temp->next;
	temp->prev = NULL;
	temp->next = NULL;
        global_index--;
        return 0;
     }
  }// Valid Index
}//Function

void search(struct NODE **node_ptr, uint32_t data, uint32_t *index)
{
  uint32_t temp_index =0;
  struct NODE *temp;
  temp = *node_ptr;
  while(temp->element !=data)
  {
    temp= temp->next;
    temp_index++;	
  }
  printf("Data %d is found at index %d \r\n",data,temp_index);
  *index = temp_index;
  
}

int main()
{
struct NODE *head =NULL;
struct NODE *temp;
uint8_t status=0;
uint8_t ind = 0;
uint32_t search_index = 0;
/*Test Code */
status = add_node(&head,15,0); 
status = add_node(&head,16,1); 
status = add_node(&head,17,1); 
status = add_node(&head,18,3); 
status = add_node(&head,20,2); 
status = add_node(&head,14,0);
status = add_node(&head,13,0);
status = add_node(&head,12,0);
status = add_node(&head,11,0);
status = add_node(&head,10,0);
status = add_node(&head,0,1);
status = add_node(&head,0,1);
status = add_node(&head,0,1);
status = add_node(&head,0,1);
status = add_node(&head,0,1);
status = add_node(&head,14,global_index);
status = add_node(&head,13,global_index);
status = add_node(&head,12,global_index);
status = add_node(&head,11,global_index);
status = add_node(&head,10,global_index);
status = add_node(&head,0,global_index/2);
status = add_node(&head,1,global_index/2);
status = add_node(&head,2,global_index/2);
status = add_node(&head,3,global_index/2);
status = add_node(&head,4,global_index/2);
status = remove_node(&head,0);
status = remove_node(&head,0);
status = remove_node(&head,0);
status = remove_node(&head,0);
status = remove_node(&head,0);
status = remove_node(&head,0);
status = remove_node(&head,global_index);
status = remove_node(&head,global_index);
status = remove_node(&head,global_index);
status = remove_node(&head,global_index);
status = remove_node(&head,global_index/2);
status = remove_node(&head,global_index/2);
status = remove_node(&head,global_index/2);
temp = head; 
while(temp)
{
 printf("Data in Index %d is %d \r\n",ind,temp->element);
 ind++;
 temp =temp->next; 
}

search(&head,14,&search_index);
search(&head,11,&search_index);
search(&head,17,&search_index);
printf("Search index value in main is %d",search_index);
}

