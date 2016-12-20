#ifndef SINGLE_LIST_H
#define SINGLE_LIST_H 


#define SLIST_NULL (-1)
typedef struct _SListEntry SListEntry;

typedef int SListValue;

typedef struct _SListIterator SListIterator;

struct _SListIterator {
	SListEntry **prev_next;
	SListEntry *current;
};


struct _SListEntry {
	SListValue data;
	SListEntry *next;
};
/*add a value at the list tail*/
SListEntry *SList_append(SListEntry **list,SListValue value);

void SList_print(SListEntry *list);
/*add a value at the list head*/
SListEntry *SList_preappend(SListEntry **list,SListValue value);

void SList_free(SListEntry *list);
/*Retrieve the next entry in a list.*/
SListEntry *SList_next(SListEntry *list);
/*return the value stored list entry*/
SListValue SList_data(SListEntry *list);

SListEntry *SList_nth_entry(SListEntry *list, unsigned int n);

SListValue SList_nth_data(SListEntry *list,unsigned int n);

unsigned int SList_length(SListEntry *list);

SListValue *SList_to_array(SListEntry *list);

int SList_remove_entry(SListEntry **list, SListEntry *entry);

int SList_remove_data(SListEntry **list,SListValue value);

SListEntry *SList_find_data(SListEntry *list,SListValue value);

SListEntry *SList_find_data(SListEntry *list,SListValue value);





















#endif