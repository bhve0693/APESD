/*

* FileName        :     test_doublelinkedlist.c
* Description     :    This file contains unit-tests for the following operations on a Double Linked List
                       with a double pointer implementation , the addition and removal of nodes
                       , searching a value in the nodes, size of the dll and destroying of the dll.
                       This is implemented in a fashion where head pointer points to the most recently 
                       added item. 
* File Author Name:    Bhallaji Venkatesan 
* Tools used      :    gcc, gdb, gedit
* References      :    https://github.com/afosdick/ecen5013/tree/develop/tutorials/unit_tests


*/

#include <math.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "doublelinkedlist.h"

/**
​ * ​ ​ @brief​ : Test Function to test addition at head of
 *            the double linked list
​ *
​ * ​ ​ No Returns. 
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ state  ​ double pointer to a state machine
 *           
​ *
​ * ​ ​ @return​ ​ None
​ */

void test_add_head_dll(void **state)
{
  enum Err_code status2;
  struct NODE *head = NULL;
  uint32_t nodeelement =2;
  uint32_t index = 0;
  status2 = add_node(&head,nodeelement,index);
  destroy(&head);
  assert_int_equal(status2, SUCCESS);

}

/**
​ * ​ ​ @brief​ : Test Function to test addition at middle of
 *            the double linked list
​ *
​ * ​ ​ No Returns. 
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ state  ​ double pointer to a state machine
 *           
​ *
​ * ​ ​ @return​ ​ None
​ */

void test_add_middle_dll(void **state)
{
  enum Err_code status2;
  struct NODE *head_mid = NULL;
  uint32_t nodeelement =2;
  uint32_t index = 0;
  status2 = add_node(&head_mid,nodeelement,index);
  assert_int_equal(status2, SUCCESS);
  nodeelement =0;
  index =1;
  status2 = add_node(&head_mid,nodeelement,index);
  assert_int_equal(status2, SUCCESS);
  nodeelement =3;
  index =2;
  status2 = add_node(&head_mid,nodeelement,index);
  assert_int_equal(status2, SUCCESS);
  nodeelement =4;
  index =1;
  status2 = add_node(&head_mid,nodeelement,index);
  destroy(&head_mid);
  assert_int_equal(status2, SUCCESS);
}


/**
​ * ​ ​ @brief​ : Test Function to test addition at tail of
 *            the double linked list
​ *
​ * ​ ​ No Returns. 
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ state  ​ double pointer to a state machine
 *           
​ *
​ * ​ ​ @return​ ​ None
​ */

void test_add_tail_dll(void **state)
{
  enum Err_code status2;
  struct NODE *head_tail = NULL;
  uint32_t nodeelement =2;
  uint32_t index = 0;
  status2 = add_node(&head_tail,nodeelement,index);
  assert_int_equal(status2, SUCCESS);
  nodeelement =0;
  index =1;
  status2 = add_node(&head_tail,nodeelement,index);
  assert_int_equal(status2, SUCCESS);
  nodeelement =3;
  index =2;
  status2 = add_node(&head_tail,nodeelement,index);
  assert_int_equal(status2, SUCCESS);
  nodeelement =4;
  index =size(&head_tail);
  assert_int_equal(index, 3);
  status2 = add_node(&head_tail,nodeelement,index);
  destroy(&head_tail);
  assert_int_equal(status2, SUCCESS);
}


/**
​ * ​ ​ @brief​ : Test Function to test addition at an invalid
 *            index of the double linked list
​ *
​ * ​ ​ No Returns. 
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ state  ​ double pointer to a state machine
 *           
​ *
​ * ​ ​ @return​ ​ None
​ */
void test_add_bad_index(void **state)
{
  enum Err_code status2;
  struct NODE *head_tail = NULL;
  uint32_t nodeelement =2;
  uint32_t index = 2;
  status2 = add_node(&head_tail,nodeelement,index);
  assert_int_equal(status2, ERR_INVALID_INDEX);
}


/**
​ * ​ ​ @brief​ : Test Function to test removal at head of the double linked list
​ *
​ * ​ ​ No Returns. 
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ state  ​ double pointer to a state machine
 *           
​ *
​ * ​ ​ @return​ ​ None
​ */
void test_remove_head_dll(void **state)
{
  enum Err_code status2;
  struct NODE *head = NULL;
  uint32_t nodeelement =2;
  uint32_t index = 0;
  status2 = add_node(&head,nodeelement,index);
  assert_int_equal(status2, SUCCESS);
  status2 = remove_node(&head,index);
  destroy(&head);
  assert_int_equal(status2, SUCCESS);

}

/**
​ * ​ ​ @brief​ : Test Function to test removal at the tail
 *            of the double linked list
​ *
​ * ​ ​ No Returns. 
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ state double pointer to a state machine
 *           
​ *
​ * ​ ​ @return​ ​ None
​ */

void test_remove_tail_dll(void **state)
{
  enum Err_code status2;
  struct NODE *head_tail = NULL;
  uint32_t nodeelement =2;
  uint32_t index = 0;
  status2 = add_node(&head_tail,nodeelement,index);
  assert_int_equal(status2, SUCCESS);
  nodeelement =0;
  index =1;
  status2 = add_node(&head_tail,nodeelement,index);
  assert_int_equal(status2, SUCCESS);
  nodeelement =3;
  index =2;
  status2 = add_node(&head_tail,nodeelement,index);
  index =size(&head_tail);
  assert_int_equal(index, 3);
  status2 = remove_node(&head_tail,index);
  destroy(&head_tail);
  assert_int_equal(status2, SUCCESS); 

}


/**
​ * ​ ​ @brief​ : Test Function to test removal at the middle
 *            of the double linked list
​ *
​ * ​ ​ No Returns. 
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ state double pointer to a state machine
 *           
​ *
​ * ​ ​ @return​ ​ None
​ */
void test_remove_middle_dll(void **state)
{
  enum Err_code status2;
  struct NODE *head_mid = NULL;
  uint32_t nodeelement =2;
  uint32_t index = 0;
  status2 = add_node(&head_mid,nodeelement,index);
  assert_int_equal(status2, SUCCESS);
  nodeelement =0;
  index =1;
  status2 = add_node(&head_mid,nodeelement,index);
  assert_int_equal(status2, SUCCESS);
  nodeelement =3;
  index =2;
  status2 = add_node(&head_mid,nodeelement,index);
  assert_int_equal(status2, SUCCESS);
  nodeelement =4;
  index =1;
  status2 = remove_node(&head_mid,index);
  destroy(&head_mid);
  assert_int_equal(status2, SUCCESS);
}


/**
​ * ​ ​ @brief​ : Test Function to test removal at the invalid
 *            index of the double linked list
​ *
​ * ​ ​ No Returns. 
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ state double pointer to a state machine
 *           
​ *
​ * ​ ​ @return​ ​ None
​ */

void test_remove_bad_index(void **state)
{
  enum Err_code status2;
  struct NODE *head_tail = NULL;
  uint32_t nodeelement =2;
  uint32_t index = 0;
  status2 = add_node(&head_tail,nodeelement,index);
  assert_int_equal(status2, SUCCESS);
  index = 2;
  status2 = remove_node(&head_tail,index);
  assert_int_equal(status2, ERR_INVALID_INDEX);
  destroy(&head_tail);
}


/**
​ * ​ ​ @brief​ : Test Function to test removal an empty
 *            double linked list
​ *
​ * ​ ​ No Returns. 
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ state double pointer to a state machine
 *           
​ *
​ * ​ ​ @return​ ​ None
​ */
void test_remove_empty_list(void **state)
{
  enum Err_code status2;
  struct NODE *head_tail = NULL;
  uint32_t index = 0;
  status2 = remove_node(&head_tail,index);
  assert_int_equal(status2, ERR_DLL_EMPTY);
  destroy(&head_tail);
}


/**
​ * ​ ​ @brief​ : Test Function to test destroy 
 *            of a valid double linked list
​ *
​ * ​ ​ No Returns. 
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ state double pointer to a state machine
 *           
​ *
​ * ​ ​ @return​ ​ None
​ */
void test_destroy_pass_dll(void **state)
{
  enum Err_code status2;
  struct NODE *head_tail = NULL;
  uint32_t nodeelement =2;
  uint32_t index = 0;
  status2 = add_node(&head_tail,nodeelement,index);
  assert_int_equal(status2, SUCCESS);
  status2 = destroy(&head_tail);
  assert_int_equal(status2, SUCCESS);

}


/**
​ * ​ ​ @brief​ : Test Function to test destroy an invalid
 *            double linked list
​ *
​ * ​ ​ No Returns. 
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ state double pointer to a state machine
 *           
​ *
​ * ​ ​ @return​ ​ None
​ */
void test_destroy_fail_dll(void **state)
{
  enum Err_code status2;
  struct NODE *head_tail = NULL;
  status2 = destroy(&head_tail);
  assert_int_equal(status2, ERR_DLL_EMPTY);
}


/**
​ * ​ ​ @brief​ : Test Function to test search of an element
 *            of the double linked list
​ *
​ * ​ ​ No Returns. 
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ state double pointer to a state machine
 *           
​ *
​ * ​ ​ @return​ ​ None
​ */
void test_search_pass_dll(void **state)
{
  enum Err_code status2;
  struct NODE *head_mid = NULL;
  uint32_t nodeelement =2;
  uint32_t index = 0;
  uint32_t index_ptr = 0;
  status2 = add_node(&head_mid,nodeelement,index);
  assert_int_equal(status2, SUCCESS);
  nodeelement =0;
  index =1;
  status2 = add_node(&head_mid,nodeelement,index);
  assert_int_equal(status2, SUCCESS);
  nodeelement =3;
  index =2;
  status2 = add_node(&head_mid,nodeelement,index);
  assert_int_equal(status2, SUCCESS);
  nodeelement = 3;
  status2 = search(&head_mid,nodeelement,&index_ptr);
  assert_int_equal(index_ptr, 2);
  assert_int_equal(status2,SUCCESS);
  destroy(&head_mid);
  
}


/**
​ * ​ ​ @brief​ : Test Function to test search of an invalid element
 *            of the double linked list
​ *
​ * ​ ​ No Returns. 
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ state double pointer to a state machine
 *           
​ *
​ * ​ ​ @return​ ​ None
​ */

void test_search_invdata_dll(void **state)
{
  enum Err_code status2;
  struct NODE *head_mid = NULL;
  uint32_t nodeelement =2;
  uint32_t index = 0;
  uint32_t index_ptr = 0;
  status2 = add_node(&head_mid,nodeelement,index);
  assert_int_equal(status2, SUCCESS);
  nodeelement =0;
  index =1;
  status2 = add_node(&head_mid,nodeelement,index);
  assert_int_equal(status2, SUCCESS);
  nodeelement =3;
  index =2;
  status2 = add_node(&head_mid,nodeelement,index);
  assert_int_equal(status2, SUCCESS);
  nodeelement = 4;
  status2 = search(&head_mid,nodeelement,&index_ptr);
  assert_int_equal(index_ptr,0);
  assert_int_equal(status2,ERR_DATA_NOT_FOUND);
  destroy(&head_mid);
}

/**
​ * ​ ​ @brief​ : Test Function to test search an empty
 *            double linked list
​ *
​ * ​ ​ No Returns. 
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ state double pointer to a state machine
 *           
​ *
​ * ​ ​ @return​ ​ None
​ */

void test_search_empty_dll(void **state)
{
  enum Err_code status2;
  struct NODE *head_mid = NULL;
  uint32_t nodeelement =2;
  uint32_t index_ptr = 0;
  status2 = search(&head_mid,nodeelement,&index_ptr);
  assert_int_equal(index_ptr,0);
  assert_int_equal(status2,ERR_DLL_EMPTY);
  destroy(&head_mid);
}

int main(int argc, char **argv)
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_add_head_dll),
    cmocka_unit_test(test_add_middle_dll),
    cmocka_unit_test(test_add_tail_dll),
    cmocka_unit_test(test_add_bad_index),   
    cmocka_unit_test(test_remove_head_dll),
    cmocka_unit_test(test_remove_tail_dll),
    cmocka_unit_test(test_remove_middle_dll),
    cmocka_unit_test(test_remove_bad_index),
    cmocka_unit_test(test_remove_empty_list),
    cmocka_unit_test(test_destroy_pass_dll),
    cmocka_unit_test(test_destroy_fail_dll),
    cmocka_unit_test(test_search_pass_dll),
    cmocka_unit_test(test_search_invdata_dll),
    cmocka_unit_test(test_search_empty_dll),
  
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
