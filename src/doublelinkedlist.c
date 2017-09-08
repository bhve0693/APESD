/*
@Brief : Addition, Removal of Nodes, searching a value and size of the DLL in Double-Linked List with double pointer Implementation
@Author: Bhallaji Venkatesan 
@Purpose: Homework 1 Code for Advanced Practical Embedded Software Design
@Mentor : Mr. Alex Fosdick, Instructor, The University of Colorado Boulder
*/


#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include"doublelinkedlist.h"


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

enum Err_code add_node(struct NODE **hdnode_ptr, uint32_t data, uint32_t index)
{
  struct NODE *new_node = (struct NODE *)malloc(sizeof(struct NODE));
  struct NODE *temp;
  //malloc fail Case 
  if(!new_node)
     return ERR_MALLOC_FAIL;

  new_node->element = data;

  if(index > (global_index)) //Invalid Index
  {

    return ERR_INVALID_INDEX;
  }

    //No Head Case
    if(!(*hdnode_ptr))
    {
        new_node->next = NULL;
        new_node->prev = NULL;
        *hdnode_ptr = new_node;
        global_index++;
        return SUCCESS;
    }
  
    //Adding at Head Node
    if(!index)
    {
        new_node->next = *hdnode_ptr;
        new_node->prev = NULL;
        (*hdnode_ptr)->prev = new_node;
	*hdnode_ptr = new_node;
        global_index++;
        return SUCCESS;
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
        return SUCCESS; 
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
        return SUCCESS;
     }
  // Valid Index
}//Function


enum Err_code remove_node(struct NODE **hdnode_ptr, uint32_t index)
{
  struct NODE *new_node = (struct NODE *)malloc(sizeof(struct NODE));
  struct NODE *temp,*temp_remove;

      //No Head Case
    if(!(*hdnode_ptr))
    {
        return ERR_DLL_EMPTY;
    }
  
  
  if(index > (global_index)) //Invalid Index
     return ERR_INVALID_INDEX;

 
 

    //Removing Head Node
    if(!index)
    {
        temp = (*hdnode_ptr)->next;
        (*hdnode_ptr)->next = NULL;
	*hdnode_ptr = temp;
        global_index--;
        return SUCCESS;
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
	free(temp);
        global_index--;
        return SUCCESS; 
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
	free(temp);
        global_index--;
        return SUCCESS;
     }
  // Valid Index
}//Function

enum Err_code search(struct NODE **node_ptr, uint32_t data, uint32_t *index)
{
  uint32_t temp_index =0;
  if(!(*node_ptr))
  {
    return ERR_DLL_EMPTY;
  }
  struct NODE *temp;
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
uint32_t size(struct NODE **hdnode_ptr)
{
  uint32_t node_size=0;
 struct NODE *temp;
 temp = *hdnode_ptr;
 while(temp->next)
 { 
   node_size++;
   temp= temp->next;
 }
 return (node_size+1);
  
}
void display(struct NODE *head)
{
  struct NODE *temp;
  temp = head;
  uint8_t status =0;
  uint32_t index=0; 
  while(temp)
  {
   printf("Data in Index %d is %d \r\n",index,temp->element);
   index++;
   temp =temp->next; 
  }
}

void dll_menu()
{
   uint32_t nodeelement;
   uint32_t node_size = 0;
   uint32_t index;
   uint32_t ch;
   struct NODE *head = NULL;
   enum Err_code status;
    printf("Double Linked List Menu\n1.Add New Node\n2.Remove Node\n3.Search a node\n4.Size\n5.Destroy LL\n6.Exit\n Enter Your Choice(1-6)");
	scanf("%u",&ch);
        while(ch!=6)
	{
            switch(ch)
	    {
		case 1: printf("Enter a value:");
				scanf("%u",&nodeelement);
				printf("\nEnter the Index of new node to be added : ");
				scanf("%u",&index);
				status = add_node(&head,nodeelement,index);
				if(status == ERR_INVALID_INDEX) 
				{
					printf("Invalid Index !\n");
					break;
				}
				if(!status)
				{
					display(head);
					break;
				}
			case 2: printf("\nEnter the Index of node to be removed : ");
				scanf("%u",&index);
				status = remove_node(&head,index); 
				if(status == ERR_INVALID_INDEX) 
				{
					printf("Invalid Index !\n");
					break;
				}
				if(status == ERR_DLL_EMPTY)
				{
					printf("No LL to remove node from\n");
					break;
				}

				if(!status)
				{
					display(head);
					break;
				}

			case 3: printf("\nEnter data to be searched : ");
				scanf("%u",&nodeelement);
				status = search(&head,nodeelement,&index);
				if(status == ERR_DLL_EMPTY)
				{
					printf("Empty DLL\n");
					break;
				}
                                if(status == ERR_DATA_NOT_FOUND)
                                {
                                   printf("Data not Found!\n");
					break;
                                }
				printf("Data found at index %u\n",index);
				break;

			case 4: node_size = size(&head);
				printf("\nSize of DLL:%u\n",node_size);
				break;

			case 5: status = destroy(&head);
				if(status == ERR_DLL_EMPTY)
				{
					printf("\nDLL not available to destroy\n");
					break;
				}
				else
				{
					printf("\nDLL destroyed\n");
					break;
				}

			case 6: exit(0);
               }
		printf("Double Linked List Menu\n1.Add New Node\n2.Remove Node\n3.Search a node\n4.Size\n5.Destroy LL\n6.Exit\n Enter Your Choice(1-6)");
	scanf("%u",&ch);
	
	}
}

int main()
{

  dll_menu();
  return 0;
}

