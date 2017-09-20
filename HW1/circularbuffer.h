/***************************************************************************** 
* Copyright (C) 2017 by Bhallaji Venkatesan 
* Redistribution, modification or use of this software in source or binary 
* forms is permitted as long as the files maintain this copyright. Users are 
* permitted to modify this and use it to learn about double linked lists.
* Bhallaji Venkatesan and the University of Colorado are not liable for 
* any misuse of this material.  *****************************************************************************/ 
/** 
* @file circularbuffer.h 
* @brief  Includes function declartions for allocate, ADD, Remove , search value, 
*         size of circular buffer and destroy actions for the circular buffer * 
* @author Bhallaji Venkatesan 
* @date September 8 2017 */
#ifndef __CIRCULARBUFFER_H_INCLUDED
#define __CIRCULARBUFFER_H_INCLUDED

#include <stdio.h> 
#include <stdlib.h> 
#include <stdint.h>

/***Global Structures ***/

/*
​ * ​ ​ @brief   ​ : Structure for the elements of Circular Buffer
​ *  ​ @contents : head    -> pointer to head node
 *               tail    -> pointer to tail node
 *               base    -> pointer to base node   
 *		 size    -> Maximum size of the buffer
 *               num_items-> Current number of items in buffer
​ */

struct cbuffer{
  uint32_t *head;
  uint32_t *tail;
  uint32_t *base;
  uint32_t size;
  uint32_t num_items;
};



/*** Enumerations ***/

/*
​ * ​ ​ @brief​ : Enum for ErrorCode
​ *
​ * ​ ​ Returns a code stating the status of different operations:
 *   SUCCESS              : Successful opeartion
 *   ERR_CBUFF_EMPTY      : Empty buffer
 *   ERR_INVALID_INDEX    : Invalid Index
 *   ERR_MALLOC_FAIL      : Failed MALLOC
​ * ​ ​ ERR_DATA_NOT_FOUND   : Data not found
​ */

enum Err_code  
{
 SUCCESS,
 ERR_CBUFF_EMPTY,
 ERR_INVALID_INDEX,
 ERR_MALLOC_FAIL,
 ERR_DATA_NOT_FOUND
};


/*** Function Declarations ***/
/**
​ * ​ ​ @brief​ : Destroys the circular buffer
​ *
​ * ​ ​ Returns a status code of destroy operation
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ buffer  ​ A double pointer to the circular buffer 

​ *
​ * ​ ​ @return​ ​ (enum)Err_code 
​ */
enum Err_code destroy(struct cbuffer **buffer);


/**
​ * ​ ​ @brief​ : Allocates memory for the circular buffer
​ *
​ * ​ ​ Returns a status code of Memory allocation
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ buffer  ​ A double pointer to the circular buffer
 *           size     size of the circular buffer to be allocated 

​ *
​ * ​ ​ @return​ ​ (enum)Err_code 
​ */
enum Err_code allocate(struct cbuffer **buffer,uint32_t size);


/**
​ * ​ ​ @brief​ : Checks for Circular buffer to be full or not
​ *
​ * ​ ​ Returns 0 or 1 based upon True or False
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ buffer  ​ A double pointer to the circular buffer
 *           
 *
​ *
​ * ​ ​ @return​ ​ uint8_t(0 or 1)
​ */
uint8_t Is_buffer_full(struct cbuffer **buffer);


/**
​ * ​ ​ @brief​ : Checks for Circular buffer to be empty or not
​ *
​ * ​ ​ Returns 0 or 1 based upon True or False
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ buffer  ​ A double pointer to the circular buffer
 *           
 *
​ *
​ * ​ ​ @return​ ​ uint8_t(0 or 1)
​ */
uint8_t Is_buffer_empty(struct cbuffer **buffer);


/**
​ * ​ ​ @brief​ : Adds item at the head of the circular buffer
​ *
​ * ​ ​ Returns a status code of Addition operation
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ buffer  ​ A double pointer to the circular buffer
 *           item     item to be added to the circular buffer 

​ *
​ * ​ ​ @return​ ​ (enum)Err_code 
 */

enum Err_code add_item(struct cbuffer **buffer,uint32_t item);

/**
​ * ​ ​ @brief​ : Removes item from the tail of the circular buffer
​ *
​ * ​ ​ Returns a status code of Removal operation
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ buffer  ​ A double pointer to the circular buffer
 *            

​ *
​ * ​ ​ @return​ ​ (enum)Err_code 
 */

enum Err_code remove_item(struct cbuffer **buffer);

/**
​ * ​ ​ @brief​ : Dumps the contents of the Circular buffer
​ *
​ * ​ ​ 
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ buffer  ​ A double pointer to the circular buffer
 *            

​ *
​ * ​ ​ @return​ ​ None
 */

void dump(struct cbuffer **buffer);

/**
​ * ​ ​ @brief​ : Return the current Size of the buffer 
​ *
​ * ​ ​ 
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ buffer  ​ A double pointer to the circular buffer
 *            

​ *
​ * ​ ​ @return​ ​ (uint32_t)size
 */

uint32_t size(struct cbuffer **buffer); 
#endif //__CIRCULARBUFFER_H_INCLUDED

