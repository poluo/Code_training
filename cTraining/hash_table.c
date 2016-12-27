#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"
static const unsigned int hash_table_primes[] = {
	193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317,
	196613, 393241, 786433, 1572869, 3145739, 6291469,
	12582917, 25165843, 50331653, 100663319, 201326611,
	402653189, 805306457, 1610612741,
};

static const unsigned int hash_table_num_primes
	= sizeof(hash_table_primes) / sizeof(int);

int main(int argc, char const *argv[])
{
	HashTable *my_table=NULL;
	my_table=hash_table_new(hash_func,hash_equal);
	
	hash_table_insert(my_table,1,1);
	hash_table_insert(my_table,2,20);
	
	HashTableKey key=3;
	HashTableValue val=hash_table_find_value(my_table,key);  

	printf("key=%d val=%d\n", key,val);

	return 0;
}

static int hash_allocate_table(HashTable *hash_table)
{
	unsigned int size = 0;
	if (hash_table -> prime_index <= hash_table_num_primes)
	{
		size = hash_table_primes[hash_table -> prime_index];
	}
	else
	{
		size = hash_table -> entries * 10;
	}

	hash_table -> table_size = size;

	hash_table -> table =calloc(hash_table->table_size,sizeof(HashTableEntry *));
	return hash_table->table == NULL;
}


HashTable *hash_table_new(HashTableHashFunc hash_func,
                          HashTableEqualFunc equal_func)
{
	HashTable *HashTable_ptr = malloc(sizeof(HashTable));
	HashTable_ptr -> table = malloc(sizeof(HashTableEntry *));
	HashTable_ptr -> entries = 0;
	HashTable_ptr -> prime_index = 0;
	HashTable_ptr -> hash_func = hash_func;
	HashTable_ptr -> equal_func = equal_func;

	if (hash_allocate_table(HashTable_ptr))
	{
		return NULL;
	}

	return HashTable_ptr;
}

int hash_table_insert(HashTable *hash_table, HashTableKey key, HashTableValue value)
{
	int index = 0;
	HashTableEntry *rover;
	HashTableEntry *new_entry;
	HashTableItem *item;

	index = hash_table->hash_func(key) % hash_table->table_size;
	
	if (hash_table->entries >= hash_table->table_size)
	{
		printf("two long\n");
		return 1;
		//hash_table_enlarge(hash_table);
	}

	rover = hash_table->table[index];
	
	while(rover != NULL)
	{
		item = &(rover->Items);

		if (hash_table->equal_func(item->key,key) == 0)
		{

			/* the key is already exist */
			if (hash_table->value_free_func != NULL)
			{
				hash_table->value_free_func(item->value);
			}

			if (hash_table->key_free_func != NULL)
			{
				hash_table->key_free_func(item->key);
			}

			item->key=key;
			item->value=value;

			return 0;
		}

		rover =rover->next;
	}

	new_entry = malloc(sizeof(HashTableEntry));

	if (new_entry == NULL)
	{
		return 0;
	}
	new_entry->Items.key = key;
	new_entry->Items.value = value;

	new_entry->next = hash_table->table[index];
	hash_table->table[index] = new_entry;

	hash_table->entries++;

	return 0;
} 

int hash_table_remove(HashTable *hash_table, HashTableKey key)
{
	int index = 0;
	HashTableEntry **rover;
	HashTableEntry *spec_entry;
	HashTableItem  item;

	index = hash_table->hash_func(key) % hash_table->table_size;
	rover = &hash_table->table[index];

	while(*rover != NULL)
	{
		item = (*rover)->Items;

		if (hash_table->equal_func(item.key,key) == 0)
		{
			/* found the key */
			spec_entry = *rover;

			*rover = spec_entry->next;

			//hash_table_free_entry(hash_table,spec_entry);

			hash_table->entries--;

			return 0;
		}

		rover =&(*rover)->next;
	}

	return 1;
} 

void hash_table_free_entry(HashTable *hash_table,HashTableEntry *entry)
{
	HashTableItem item;

	item = entry->Items;

	if (hash_table->key_free_func != NULL)
	{
		hash_table->key_free_func(item.key);
	}
	if (hash_table->value_free_func != NULL)
	{
		hash_table->value_free_func(item.value);
	}
	free(entry);
}
HashTableValue hash_table_find_value(HashTable *hash_table,HashTableKey key)
{
	HashTableEntry *rover;
	int index = 0;
	int compare_ret=1;

	index = hash_table->hash_func(key) % hash_table->table_size;

	rover=hash_table->table[index];
	compare_ret=hash_table->equal_func(rover->Items.key,key);
	while(compare_ret && rover!=NULL)
	{
		compare_ret=hash_table->equal_func(rover->Items.key,key);
		rover=rover->next;
	}

	if (compare_ret)
	{
		return 0xEFFFFFFF;
	}
	return rover->Items.value;
}

unsigned int hash_table_nums_entrys(HashTable *hash_table)
{
	return hash_table->entries;
}

unsigned int hash_func(HashTableKey value)
{
	return value/2;
}
int hash_equal(HashTableKey value1, HashTableKey value2)
{
	return value1 - value2;
}