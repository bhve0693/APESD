
#ifndef __DOUBLELINKEDLIST_H_INCLUDED
#define __DOUBLELINKEDLIST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



/*** Global Variables ***/ 
uint32_t global_index = 0;


/***Global Structures ***/

/*
​ * ​ ​ @brief   ​ : Structure for the Nodes of DLL
​ *  ​ @contents : element -> data value of a node
 *               prev    -> pointer to previous node
 *               next    -> pointer to next node   
​ */

struct NODE{
uint32_t element;
struct NODE *prev;
struct NODE *next;
};


/*** Enumerations ***/

/*
​ * ​ ​ @brief​ : Enum for ErrorCode
​ *
​ * ​ ​ Returns a code stating the status of different operations:
 *   SUCCESS              : Successful opeartion
 *   ERR_DLL_EMPTY        : Empty Linked List
 *   ERR_INVALID_INDEX    : Invalid Index
 *   ERR_MALLOC_FAIL      : Failed MALLOC
​ * ​ ​ ERR_DATA_NOT_FOUND   : Data not found
​ */

enum Err_code  
{
 SUCCESS,
 ERR_DLL_EMPTY,
 ERR_INVALID_INDEX,
 ERR_MALLOC_FAIL,
 ERR_DATA_NOT_FOUND
};

/*** Function Declarations ***/
/**
​ * ​ ​ @brief​ : Destroys all nodes from the linked list
​ *
​ * ​ ​ Returns a status code of destroy operation
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ hdnode_ptr  ​ A double pointer to the head of the Linked List

​ *
​ * ​ ​ @return​ ​ (enum)Err_code 
​ */
enum Err_code destroy(struct NODE** hdnode_ptr);


/**
​ * ​ ​ @brief​ : Adds a node at the required index in the linked list
​ *
​ * ​ ​ Returns a status code of add operation
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ hdnode_ptr  ​ A double pointer to the head of the Linked List
​ * ​ ​ @param​ ​ data ​        Data to be added to the Linked List
​ * ​ ​ @param​ ​ index ​       index where data is to be added
​ *
​ * ​ ​ @return​ ​ (enum)Err_code
​ */
enum Err_code add_node(struct NODE** hdnode_ptr,uint32_t data,uint32_t index);

/**
​ * ​ ​ @brief​ : Remove a node from Linked List
​ *
​ * ​ ​ Returns a status code of remove node operation
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ hdnode_ptr  ​ A double pointer to the head of the Linked List
​ * ​ ​ @param​ ​ index ​       index from where data is to be removed
​ *
​ * ​ ​ @return​ ​ (enum)Err_code
​ */
enum Err_code remove_node(struct NODE** hdnode_ptr,uint32_t index);


/**
​ * ​ ​ @brief​ : Search a node the linked list based on value
​ *
​ * ​ ​ Returns the position of the node in the Linked List
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ hdnode_ptr  ​     A double pointer to the head of the Linked List
​ * ​ ​ @param​ ​ data ​            Data to be searched for in the list
 *   @param​ ​ index ​           Pointer to the index variable to be updated
​ *
​ * ​ ​ @return​ ​ (enum)Err_code
              Updates the pointer to index.
​ */
enum Err_code search(struct NODE** hdnode_ptr,uint32_t data, uint32_t *index);

/**
​ * ​ ​ @brief​ : Returns current size of the LinkedList
​ *
​ * ​ ​ Returns size of Linked List
​ *
​ * ​ ​ @return​ ​ uint32_t
​ */
uint32_t size(struct NODE **hdnode_ptr);

//__DOUBLELINKEDLIST_H_INCLUDED
#endif​ 

