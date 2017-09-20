#include <stdint.h>
#include <math.h>
#include<stdio.h>
#include<stdlib.h>
#include "doublelinkedlist.h"


/* Global Variables */ 
uint32_t global_index = 0;

enum Err_code add_node(struct NODE **hdnode_ptr, uint32_t data, uint32_t index)
{
  struct NODE *new_node = (struct NODE *)malloc(sizeof(struct NODE));
  struct NODE *temp = NULL;
  /*malloc fail Case*/ 
  if(!new_node)
  {
     return ERR_MALLOC_FAIL;
  }

  new_node->element = data;

  if(index > (global_index)) /*Invalid Index*/
  {
    return ERR_INVALID_INDEX;
  }

    /*No Head Case*/
  if(!(*hdnode_ptr))
  {
    new_node->next = NULL;
    new_node->prev = NULL;
    *hdnode_ptr = new_node;
    global_index++;
    return SUCCESS;
  }
  
    /*Adding at Head Node*/
  if(!index)
  {
    new_node->next = *hdnode_ptr;
    new_node->prev = NULL;
    (*hdnode_ptr)->prev = new_node;
    *hdnode_ptr = new_node;
    global_index++;
    return SUCCESS;
  }
  if(index == global_index) /*Adding New Node at Tail*/
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
    return SUCCESS; 
  }
    /*Any general Node*/
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
    return SUCCESS;
  }
}

enum Err_code remove_node(struct NODE **hdnode_ptr, uint32_t index)
{
  //struct NODE *new_node = (struct NODE *)malloc(sizeof(struct NODE));
  struct NODE *temp = NULL;
  //struct NODE *temp_remove = NULL;

      /*No Head Case*/
  if(!(*hdnode_ptr))
  {
     return ERR_DLL_EMPTY;
  }
  
  
  if(index > (global_index)) /*Invalid Index*/
  {
     return ERR_INVALID_INDEX;
  }
    /*Removing Head Node */
  if(!index)
  {
    temp = (*hdnode_ptr)->next;
    (*hdnode_ptr)->next = NULL;
    *hdnode_ptr = temp;
    global_index--;
    return SUCCESS;
  }
  if(index == global_index) /*Removing Node at Tail*/
  {
	
      temp = *hdnode_ptr;
      while(temp->next)
      {
        temp = temp->next;	
      }
      temp->prev->next = NULL;
      temp = NULL;
      free(temp);
      global_index--;
      return SUCCESS; 
  }
    /*Removing Any general Node*/
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
    free(temp);
    global_index--;
    return SUCCESS;
  }
}


enum Err_code destroy(struct NODE **hdnode_ptr)
{
 
  struct NODE *temp = (struct NODE *)malloc(sizeof(struct NODE));
  
  if (!(*hdnode_ptr))
    return ERR_DLL_EMPTY; /*if no nodes are present */

  else 
  {
     while(*hdnode_ptr)
     {
       temp = *hdnode_ptr;
       *hdnode_ptr = temp->next;
       free(temp);	
     }
     global_index = 0;
     return SUCCESS;
  }
}

uint32_t size(struct NODE **hdnode_ptr)
{
  uint32_t node_size=0;
  struct NODE *temp = NULL;
  temp = *hdnode_ptr;
  while(temp->next)
  { 
     node_size++;
     temp= temp->next;
  }
  return (node_size+1); 
}

enum Err_code search(struct NODE **node_ptr, uint32_t data, uint32_t *index)
{
  uint32_t temp_index =0;
  if(!(*node_ptr))
  {
    return ERR_DLL_EMPTY;
  }
  struct NODE *temp = NULL;
  temp = *node_ptr;
  
  while(temp->element !=data)
  {
    temp= temp->next;
    if(!temp)
    {
       return ERR_DATA_NOT_FOUND;
    } 
    
    temp_index++;	
  }
  printf("Data %d is found at index %d \r\n",data,temp_index);
  *index = temp_index;
  return SUCCESS;
}


  
