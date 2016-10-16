#include <stdio.h>
#include <stdlib.h>
#include "List.h"

void Insert(int num, List L, Position P)
{
	Position tmp = calloc(0,sizeof(Position));
	if (tmp == NULL)
		printf("Insert Failed! malloc--out of space.\n");
	tmp->val = num;
	tmp->Next = P->Next;
	P->Next = tmp;
}
void PrintList(List L)
{
	Position tmp = L;
	while (!IsLast(tmp))
	{
		printf("%d\n", tmp->val);
		tmp = tmp->Next;
	}
	printf("%d\n", tmp->val);
}
Position find(int x, List L)
{
	Position tmp = L;
	while (tmp!=NULL)
	{
		if (tmp->val==x)
		{
			return tmp;
		}
		else
		{
			tmp = tmp->Next;
		}
	}
	return -1;
}
Position FindPrevious(int x, List L)
{
	Position tmp = L;

	while (tmp->Next!= NULL)
	{
		if (tmp->Next->val == x)
		{
			return tmp;
		}
		else
		{
			tmp = tmp->Next;
		}
	}
	return NULL;

}
//无法删除第一个数
void Delete(int x, List L)
{
	Position tmp;
	Position forward;
	forward = FindPrevious(x, L);
	if (forward!=NULL)
	{
		tmp = forward->Next;
		forward ->Next= tmp->Next;
		free(tmp);
	}
	else
	{
		printf("not found %d\n",x);
	}
}
void DeleteAll(List L)
{
	Position tmp,p;
	p = L->Next;
	L->Next = NULL;
	while (p!=NULL)
	{
		tmp = p;
		p = p->Next;
		free(tmp);
		//p = tmp;
	}
}
List MakeEmpty(List L)
{
	L->Next = NULL;
	return L;
}
int IsEmpty(List L)
{
	return L->Next == NULL;
}
int IsLast(Position P)
{
	return P->Next == NULL;
}
int main()
{
	printf("hello,test List\n");
	List myList = calloc(0, sizeof(List));
	myList->val = 0;
	myList->Next = NULL;

	Insert(2, myList, myList);
	Insert(3, myList, myList);
	PrintList(myList);
	Delete(0, myList);
	printf("after\n");
	PrintList(myList);
	DeleteAll(myList);
	printf("%d\n", IsEmpty(myList));
	system("pause");
}
