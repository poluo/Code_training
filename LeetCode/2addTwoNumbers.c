/*****************************************
*You are given two linked lists representing two non-negative numbers. 
*The digits are stored in reverse order and each of their nodes contain a single digit.
* Add the two numbers and return it as a linked list.
*Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
*Output: 7 -> 0 -> 8
* 
* Definition for singly-linked list.
*struct ListNode {
*     int val;
*     struct ListNode *next;
* };
*
*LeetCode OJ No.2 Add Two Numbers
*start 2016.8.5
*end   2016.8.5

******************************************/
#include <stdio.h>
struct ListNode 
{
	int val;
	struct ListNode *next;
};
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2);
int main(int argc, char const *argv[])
{
	int array1[3]={2,5,8};
	int array2[3]={3,5,9};
	struct ListNode *tmp1=convert(array1,3);
	struct ListNode *tmp2=convert(array2);
	//printf("TEST Begain:\n");
	
	return 0;
}
struct ListNode* addTwoNumbers(int *array)
{
	struct ListNode *ret=malloc(sizeof(struct ListNode));
	struct ListNode *tmp=ret;
	int i=0;
	for (i = 0; i < sizeof(array)/sizeof(int); i++)
	{
		tmp->val=array[i];
		tmp->next=malloc(sizeof(struct ListNode));
		tmp=tmp->next;
	}
	tmp=NULL;
	/**/
	tmp=ret;
	while(tmp!=NULL)
	{
		printf("tmp->val:%d  ", tmp->val);
		tmp=tmp->next;
	}
}
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) 
{
	struct ListNode* current_L1=l1;
	struct ListNode* current_L2=l2;
	struct ListNode* ret=malloc(sizeof(struct ListNode));
	struct ListNode* ret_1=ret;
	int carray=0,is_carray=0;
	while(current_L1!=NULL&&current_L2!=NULL)
	{
		if (current_L1->val+current_L2->val>=9)
		{
			carray=1;
			if (is_carray==1)
			{
				ret->val=current_L1->val+current_L2->val+carray-10;
				is_carray=0;
			}
			else
				ret->val=current_L1->val+current_L2->val-10;
			is_carray=1;
			
		}
		else
		{
			if (is_carray==1)
			{
				ret->val=current_L1->val+current_L2->val+carray;
				is_carray=0;
			}
			else
				ret->val=current_L1->val+current_L2->val;
			
		}
		ret->next=malloc(sizeof(struct ListNode));
		current_L1=current_L1->next;
		current_L2=current_L2->next;
		ret=ret->next;
	}
	ret->next=NULL;
	return ret_1;
}   


