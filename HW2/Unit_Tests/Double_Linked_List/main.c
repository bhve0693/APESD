/*

* FileName        :    main.c
* Description     :    This file implements a demo of the following operations on a Double Linked List
                       with a double pointer implementation , the addition and removal of nodes
                       , searching a value in the nodes, size of the dll and destroying of the dll.
                        
* File Author Name:    Bhallaji Venkatesan 
* Tools used      :    gcc, gedit
* References      :    https://github.com/afosdick/ecen5013/tree/develop/tutorials/unit_tests

*/

#include <stdio.h>
#include <stdlib.h>
#include "doublelinkedlist.h"


void dll_menu()
{
  uint32_t nodeelement;
  uint32_t node_size = 0;
  uint32_t index;
  uint32_t ch;
  struct NODE *head = NULL;
  enum Err_code status;
  printf("Double Linked List Menu\n1.Add New Node\n2.Remove Node\n3.Search a node\n");
  printf("4.Size\n5.Destroy LL\n6.Exit\n Enter Your Choice(1-6)");
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
       default: printf("Invalid Request. Please Request again! \r\n");
                break;
     }
     printf("Double Linked List Menu\n1.Add New Node\n2.Remove Node\n3.Search a node\n");
     printf("4.Size\n5.Destroy LL\n6.Exit\n Enter Your Choice(1-6)");
     scanf("%u",&ch);
  }
}

int main(int argc, char **argv)
{
  dll_menu();
  return 0;
}
