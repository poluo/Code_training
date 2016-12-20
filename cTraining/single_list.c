#include <stdio.h>
#include <stdlib.h>
#include "single_list.h"
int main(int argc, char const *argv[])
{
	SListEntry *mylist=NULL;

	SListEntry *tmp_entry;

	SListValue *list_array;
	

	SList_append(&mylist,10);
	SList_preappend(&mylist,11);
	SList_preappend(&mylist,12);
	SList_preappend(&mylist,13);
	SList_append(&mylist,9);
	SList_preappend(&mylist,14);
	SList_preappend(&mylist,13);

	SList_free(mylist);
	printf("%d\n",mylist->data);
	//tmp_entry=SList_next(mylist);

	//printf("%d\n",tmp_entry->data);

	//printf("%d\n",SList_data(tmp_entry));

	//SList_print(mylist);
	//getchar();
	//tmp_entry=SList_nth_entry(mylist,7);
	//printf("%d\n",SList_remove_entry(&mylist,tmp_entry));
	//printf("%d\n",tmp_entry==NULL?0:SList_data(tmp_entry));
	//printf("%d\n",SList_nth_data(mylist,0));
	//printf("%d\n",SList_remove_data(&mylist,13));
	//SList_print(mylist);
	//tmp_entry=SList_find_data(mylist,10);
	//printf("%d\n",tmp_entry->data);
	//printf("the length of this list=%d\n",SList_length(mylist));


	//list_array=SList_to_array(mylist);

	

	getchar();
	


	return 0;
}

void SList_print(SListEntry *list)
{
	SListEntry *tmp_entry;

	if (list->next==NULL)
	{
		printf("empty\n");
	}

	for (tmp_entry=list; tmp_entry!=NULL ; tmp_entry=tmp_entry->next)
	{
		printf("%d\n",tmp_entry->data );
	}


}

void SList_free(SListEntry *list)
{
	SListEntry *tmp_entry;
	SListEntry *del_entry;

	tmp_entry=list;

	while(tmp_entry!=NULL)
	{
		del_entry=tmp_entry->next;

		free(tmp_entry);

		tmp_entry=del_entry;
	}

}

SListEntry *SList_append(SListEntry **list,SListValue value)
{
	SListEntry *new_entry=malloc(sizeof(SListEntry));
	SListEntry *tmp;

	if (new_entry==NULL)
	{
		return NULL;
	}

	new_entry->data = value;
	new_entry->next=NULL;

	if (*list==NULL)
	{
		*list=new_entry;
	}
	else
	{
		for (tmp=*list; tmp->next!=NULL ; tmp=tmp->next)
		{
			;
		}
		tmp->next = new_entry;
	}
	
	return new_entry;
}

SListEntry *SList_preappend(SListEntry **list,SListValue value)
{
	SListEntry *new_entry=malloc(sizeof(SListEntry));

	if (new_entry==NULL)
	{
		return NULL;
	}

	new_entry->data = value;
	new_entry->next = *list;

	*list = new_entry;

	return new_entry;
}

SListEntry *SList_next(SListEntry *list)
{
	return list->next;
}

SListValue SList_data(SListEntry *list)
{
	return list->data;
}

SListEntry *SList_nth_entry(SListEntry *list, unsigned int n)
{
	SListEntry *tmp_entry;
	int i=0;

	tmp_entry=list;

	if (n<1)
	{
		return NULL;
	}

	for (i = 0; i < n-1; ++i)
	{
		if (tmp_entry->next!=NULL)
		{
			tmp_entry=tmp_entry->next;
		}
		else
		{
			return NULL;
		}
	}

	return tmp_entry;
}

SListValue SList_nth_data(SListEntry *list,unsigned int n)
{
	SListEntry *tmp_entry;
	int i=0;
	tmp_entry=list;

	if (n<1)
	{
		return SLIST_NULL;
	}

	for (i = 0; i < n-1; ++i)
	{
		if (tmp_entry->next!=NULL)
		{
			tmp_entry=tmp_entry->next;
		}
		else
		{
			return SLIST_NULL;
		}
	}

	return tmp_entry->data;
}

unsigned int SList_length(SListEntry *list)
{
	SListEntry *tmp_entry=list;
	unsigned int length=0;

	while(tmp_entry!=NULL)
	{
		tmp_entry=tmp_entry->next;
		length++;
	}

	return length;
}

SListValue *SList_to_array(SListEntry *list)
{
	unsigned int length=SList_length(list);
	SListEntry *tmp_entry;
	int i=0;
	tmp_entry=list;

	SListValue *array=malloc(sizeof(SListValue)*length);

	for (i = 0; i < length; ++i)
	{
		array[i]=tmp_entry->data;
		tmp_entry=tmp_entry->next;
	}

	return array;
}

int SList_remove_entry(SListEntry **list, SListEntry *entry)
{

	SListEntry *tmp_entry;
	SListEntry *tmp_prev_entry;
	tmp_entry=*list;
	int count=0;

	if (tmp_entry==entry)
	{
		*list=tmp_entry->next;
		return 0;
	}

	while(tmp_entry!=NULL&&tmp_entry!=entry)
	{
		tmp_prev_entry=tmp_entry;
		tmp_entry=tmp_prev_entry->next;
		count++;
	}

	if (tmp_entry==NULL)
	{
		return -1;
	}
	else
	{
		tmp_prev_entry->next=entry->next;
		free(entry);
		return 0;
	}

}

int SList_remove_data(SListEntry **list,SListValue value)
{
	SListEntry *tmp_entry;
	SListEntry **tmp_entry_ptr;
	int count = 0;

	tmp_entry_ptr=list;
	while(*tmp_entry_ptr!=NULL)
	{
		if ((*tmp_entry_ptr)->data==value)
		{
			tmp_entry=(*tmp_entry_ptr)->next;
			free(*tmp_entry_ptr);
			*tmp_entry_ptr=tmp_entry;
			count++;
		}
		else
		{
			tmp_entry_ptr=&((*tmp_entry_ptr)->next);
		}
	
	}

	return count;
}

SListEntry *SList_find_data(SListEntry *list,SListValue value)
{
	SListEntry *tmp_entry=list;
	while(tmp_entry->data!=value&&tmp_entry->next!=NULL)
	{
		tmp_entry=tmp_entry->next;
	}

	if (tmp_entry->next==NULL)
	{
		if (tmp_entry->data==value)
		{
			return tmp_entry;
		}
		return NULL;
	}
	else
	{
		return tmp_entry;
	}
}


