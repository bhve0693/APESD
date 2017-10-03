/**
​ * ​ ​ @brief​ : Userspace Test Function that Sorts the input buffer 
 *            in the order of large to small and updates the input 
 *            buffer pointer
​ *
​ * ​ ​ No Returns. Updates the Output Buffer to be sorted
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ input  ​ A pointer to the input buffer 
 *           output  A pointer to the output buffer to be sorted 
 *           size    Size of the input buffer to be sorted
​ *
​ * ​ ​ @return​ ​ None
​ */
void ltos_sort(int32_t *input, int32_t *output,int size)
{
   int outer,inner,temp = 0;
   memcpy(output,input,(sizeof(int32_t)*size)); 
   for(outer =0;outer<size;outer++)
   {
     for(inner = outer+1;inner<=size;inner++)
     {
       if(*(output+outer) < *(output+inner))
       { 
	 temp = *(output+outer);
         *(output+outer) = *(output+inner); 
         *(output + inner) = temp;
       }
      }
    }
}