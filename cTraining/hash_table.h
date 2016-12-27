#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

typedef int HashTableKey;

typedef int HashTableValue;

typedef struct _HashTableItem{
	HashTableKey key;
	HashTableValue value;
} HashTableItem;

typedef struct _HashTableEntry
{
	HashTableItem Items;
	struct _HashTableEntry *next;
}HashTableEntry;

typedef unsigned int (*HashTableHashFunc)(HashTableKey value);

typedef int (*HashTableEqualFunc)(HashTableKey value1, HashTableKey value2);

typedef void (*HashTableKeyFreeFunc)(HashTableKey value);

typedef void (*HashTableValueFreeFunc)(HashTableValue value);


typedef struct _HashTable
{
	HashTableEntry **table;
	unsigned int table_size;
	HashTableHashFunc hash_func;
	HashTableEqualFunc equal_func;
	HashTableKeyFreeFunc key_free_func;
	HashTableValueFreeFunc value_free_func;
	unsigned int entries;
	unsigned int prime_index;
}HashTable;



void hash_table_free_entry(HashTable *hash_table,HashTableEntry *entry);

unsigned int hash_table_nums_entrys(HashTable *hash_table);

HashTable *hash_table_new(HashTableHashFunc hash_func,
                          HashTableEqualFunc equal_func);

int hash_table_insert(HashTable *hash_table,
                      HashTableKey key,
                      HashTableValue value);    

int hash_table_remove(HashTable *hash_table, HashTableKey key);

unsigned int hash_func(HashTableKey value);

int hash_equal(HashTableKey value1, HashTableKey value2);
#endif