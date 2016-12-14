#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _array_list ArrayList;
typedef int ListData;
struct _array_list
{
	ListData *data;
	unsigned int length;
	unsigned int _alloc_length;
};
typedef int (*ArrayList_value_equal)(ListData data1,ListData data2);
typedef int (*ArrayList_value_compare)(ListData data1,ListData data2);

ArrayList *new_array_list(int length)
{
	ArrayList *tmp_arraylist=malloc(sizeof(ArrayList));
	if (tmp_arraylist==NULL)
	{
		return NULL;
	}
	tmp_arraylist->data=calloc(length,sizeof(ListData));
	if (tmp_arraylist->data==NULL)
	{
		free(tmp_arraylist);
		return NULL;
	}
	tmp_arraylist->_alloc_length=length;
	tmp_arraylist->length=0;
	return tmp_arraylist;
}
int arrlist_tail_append(ArrayList *list,ListData data)
{
	if (list->length>=list->_alloc_length)
	{
		return 1;
	}
	list->data[list->length]=data;
	list->length++;
	return 0;
}
int arrlist_head_append(ArrayList *list,ListData data)
{
	
	if (list->length>=list->_alloc_length)
	{
		return 1;
	}
	memmove(&list->data[1],&list->data[0],(list->length) * (sizeof(ListData)));
	list->data[0]=data;
	list->length++;
	return 0;
}
int arrlist_insert(ArrayList *list,unsigned int index,ListData data)
{
	if (index>=list->length)
	{
		return 1;
	}
	memmove(&list->data[index+1],&list->data[index],(list->length-index) * (sizeof(ListData)));
	list->data[index]=data;
	list->length++;
	return 0;
}
int arrlist_remove_one(ArrayList *list,unsigned int index)
{
	if (index >= list->length)
	{
		return 1;
	}
	memmove(&list->data[index],&list->data[index+1],(list->length-index) * (sizeof(ListData)));
	list->length--;
	return 0;
}
int arrlist_remove_range(ArrayList *list,unsigned int start_index,unsigned int end_index)
{
	if (start_index < 0||end_index >= list->length)
	{
		return 1;
	}
	memmove(&list->data[start_index],&list->data[end_index],(end_index - start_index) * (sizeof(ListData)));

	list->length -= end_index - start_index;
	return 0;
}
int arrlist_find_value(ArrayList *list,ListData data,ArrayList_value_equal equal_func)
{
	int i=0;
	for (i = 0; i < list->length; ++i)
	{
		if (!equal_func(list->data[i],data))
		{
			return i;
		}
	}
	return -1;
}
void arrlist_erase(ArrayList *list)
{
	int i=0;
	memset(&list->data[0],0,sizeof(ListData)*list->length);
	list->length=0;
}
void arrlist_free(ArrayList *list)
{
	free(list->data);
	free(list);
}
ArrayList *arrlist_enlarge(ArrayList *list)
{
	ArrayList *tmp_arraylist=realloc(list,list->_alloc_length*2);
	tmp_arraylist->_alloc_length*=2;
	return tmp_arraylist;
}
void arrlist_print(ArrayList *list)
{
	int i=0;
	printf("ArrayList allocated length=%d used length=%d\n",list->_alloc_length,list->length);
	for (i= 0; i < list->length; ++i)
	{
		printf("%d  \n",list->data[i]);
	}
	printf("\n");
}
int arrlist_value_swap(ArrayList *list,int i,int j)
{
	if(i>=list->length||j>=list->length)
		return -1;

	ListData tmp;

	tmp=list->data[i];
	list->data[i]=list->data[j];
	list->data[j]=tmp;

	return 0;
}
void arrlist_sort(ArrayList *list,unsigned int left,unsigned int right)
{
	int i=0,last=0;
	if(left>=right)
		return;
	arrlist_value_swap(list,left,(left+right)/2);
	last=left;
	for (i = left+1; i <=right; i++)
	{
		if ((list->data[i]-list->data[left])<0)
		{
			arrlist_value_swap(list,++last,i);
		}
	}
	arrlist_value_swap(list,left,last);
	arrlist_sort(list,left,last-1);
	arrlist_sort(list,last+1,right);
}

int ArrayList_int_equal (int data1,int data2)
{
	if (data1==data2)
		return 0;
	else
		return 1;
}
int ArrayList_int_comp (int data1,int data2)
{
	return data1-data2;
}
int main(int argc, char const *argv[])
{
	ArrayList *test=new_array_list(10);
	int i=0;
	for(i=5;i>0;i--)
	{
		arrlist_tail_append(test,i);
	}
	arrlist_head_append(test,100);
	arrlist_tail_append(test,4);
	arrlist_insert(test,3,10);
	arrlist_print(test);
	arrlist_sort(test,0,test->length-1);
	arrlist_print(test);
	getchar();
	return 0;
}
