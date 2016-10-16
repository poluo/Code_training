/*Given a linked list, remove the nth node from the end of list and return its head.

For example,

   Given linked list: 1->2->3->4->5, and n = 2.

   After removing the second node from the end, the linked list becomes 1->2->3->5.
Note:
Given n will always be valid.
Try to do this in one pass.*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#include <stdio.h>
#include <stdlib.h>
struct ListNode 
{
    int val;
    struct ListNode *next;
};
struct ListNode* removeNthFromEnd(struct ListNode* head, int n);
struct ListNode* inputList(void);
void PrintList(struct ListNode * L);
int main(int argc, char const *argv[])
{
	int n=0;
	printf("Hello ,test begain!\n");
	struct ListNode* myList=inputList();
	PrintList(myList);
	printf("whitch one do you want remove?\n");
	scanf("%d",&n);
	myList=removeNthFromEnd(myList,n);
	PrintList(myList);
	return 0;
}
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) 
{
	struct ListNode *tmp[n+1];
	struct ListNode *tmp_head=head;
	int i=0,j=0;
	while(tmp_head!=NULL)
	{
		if (i>n)
		{
			for (j = 1; j<=n ; j++)
			{
				tmp[j-1]=tmp[j];
			}
			tmp[n]=tmp_head;
			//printf("j %d\n", j);
			//printf("%d %d %d \n",tmp[0]->val,tmp[1]->val,tmp[2]->val);
		}
		else
			tmp[i]=tmp_head;
		i++;
		//printf("i: %d\n",i);
		tmp_head=tmp_head->next;
	}
	if (n==i)//delete first number
	{
		tmp_head=head;
		head=tmp_head->next;
		free(tmp_head);
		//PrintList(head);
	}
	else
	{
		if (n==1)
		{
			free(tmp[n]);
			tmp[n]=NULL;
			tmp[n-1]->next=NULL;
		}	
		else
		{
			tmp[0]->next=tmp[2];
			free(tmp[1]);
			tmp[1]=NULL;
		}
	}	
	return head;
}
struct ListNode* inputList(void)
{
	struct ListNode *ret=malloc(sizeof(struct ListNode));
	struct ListNode *tmp=ret;
	struct ListNode *tmp1=ret;
	int num=0;
	while(1)
	{
		printf("Please enter your number:\n");
		scanf("%d",&num);
		if (num=='\n'||num==EOF||num==-1)
			break;
		tmp->val=num;
		printf("num %d\n",num);
		tmp->next=malloc(sizeof(struct ListNode));
		tmp1=tmp;
		tmp=tmp->next;
	}
	free(tmp);
	tmp=NULL;
	tmp1->next=NULL;
	return ret;
}
void PrintList(struct ListNode * L)
{
	struct ListNode * tmp = L;
	printf("Print list\n");
	while (tmp!=NULL)
	{
		printf("%d\n", tmp->val);
		tmp = tmp->next;
	}
}