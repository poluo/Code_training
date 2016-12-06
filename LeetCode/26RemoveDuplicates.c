#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
	int my_array[9]={1,1,3,4,4,5,6,7,7};
	//remove_duplicates(my_array,5);
    removeDuplicates(my_array,9);
	return 0;
}
int remove_duplicates(int* nums, int numsSize) 
{
    int* tmp_arr=calloc(0,sizeof(int)*numsSize);
    int i=0,count=0;
    tmp_arr[0]=nums[0];
    count++;
    for (i = 1; i < numsSize; i++)
    {
    	if (nums[i]==tmp_arr[count-1])
    	{
    		;    
    	}
    	else
    	{
    		tmp_arr[count]=nums[i];
    		count++;
    	}
    }
    printf("count=%d \n",count);
    for (i = 0; i < count; i++)
    {
    	printf("%d \n",tmp_arr[i]);
    }
    return count;
}
int removeDuplicates(int* nums, int numsSize) 
{
    int i=0;
    int count_dup=0;
    i=1;
    while(i<numsSize)
    {
        //第i个数与第i-1个数相同
        if (nums[i]==nums[i-1-count_dup])
        {
            //printf("count_dup=%d nums[i]=%d num=%d \n",count_dup,nums[i],nums[i-1-count_dup]);
            count_dup++;
        }
        else
        {
            nums[i-count_dup]=nums[i];
            //printf("nums[i]=%d num=%d \n",nums[i],nums[i-1-count_dup]);
        }
        i++;
    }
    //printf("count_dup=%d \n",count_dup);
    for(i=0;i<numsSize-count_dup;i++)
    {
        printf("%d\n",nums[i] );
    }
    printf("length=%d \n",numsSize-count_dup);
    return numsSize-count_dup;
}
