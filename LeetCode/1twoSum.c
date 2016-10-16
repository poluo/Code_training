/*****************************************
*Given an array of integers, return indices of the two numbers such that they add up to 
*a specific target.
*You may assume that each input would have exactly one solution.
*Example:
*Given nums = [2, 7, 11, 15], target = 9,
*Because nums[0] + nums[1] = 2 + 7 = 9,
*return [0, 1].
*
* Note: The returned array must be malloced, assume caller calls free().
*
*LeetCode OJ No.1 Two Sum
*start 2016.8.4
*end  2016.8.4

******************************************/

#include <stdio.h>
int* twoSum(int* nums, int numsSize, int target);
int main(int argc, char const *argv[])
{
	int *val=(int *)malloc(sizeof(int)*2);
	int *array;
	int target,size,i;

	printf("please input the numsSize:\n");
	scanf("%d",&size);
	array=(int *)malloc(sizeof(int)*size);
	
	printf("please input nums\n");
	for (i = 0; i < size; ++i)
	{
		scanf("%d",(array+i));
	}
	printf("please input the target:\n");
	scanf("%d",&target);

	val=twoSum(array,size,target);
	if (val==NULL)
	{
		printf("not found\n");
	}
	else
		printf("the indices is %d and %d\n", *val,*(val+1));
	return 0;
}
int* twoSum(int* nums, int numsSize, int target)
{
	int *ret_val=(int *)malloc(sizeof(int)*2);
	int i=0,j=0;
	for (i = 0; i < numsSize; ++i)
	{
		for (j = i+1; j < numsSize; ++j)
		{
			if ((*(nums+i)+*(nums+j))==target)
			{
				*ret_val=i;
				*(ret_val+1)=j;
				return ret_val;
			}
		}
	}
	return NULL;
    
}