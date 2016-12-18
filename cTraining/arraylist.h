#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#ifdef __cplusplus
extern "C" {
#endif

typedef int ListData;

typedef struct _array_list ArrayList;

struct _array_list
{
	ListData *data;
	unsigned int length;
	unsigned int _alloc_length;
};


typedef int (*ArrayList_value_equal)(ListData data1,ListData data2);
typedef int (*ArrayList_value_compare)(ListData data1,ListData data2);

ArrayList *new_array_list(int length);

int arrlist_tail_append(ArrayList *list,ListData data);

int arrlist_head_append(ArrayList *list,ListData data);

int arrlist_insert(ArrayList *list,unsigned int index,ListData data);

int arrlist_remove_one(ArrayList *list,unsigned int index);

int arrlist_remove_range(ArrayList *list,unsigned int start_index,unsigned int end_index);

int arrlist_find_value(ArrayList *list,ListData data,ArrayList_value_equal equal_func);

void arrlist_erase(ArrayList *list);

void arrlist_free(ArrayList *list);

ArrayList *arrlist_enlarge(ArrayList *list);

void arrlist_print(ArrayList *list);

int arrlist_value_swap(ArrayList *list,int i,int j);

void arrlist_sort(ArrayList *list, ArrayList_value_compare compare_func, 
				unsigned int left, unsigned int right);

int ArrayList_int_equal (int data1,int data2);

int ArrayList_int_compare (int data1,int data2);



#ifdef __cplusplus
}
#endif

#endif