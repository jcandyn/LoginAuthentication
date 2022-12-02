#ifndef HASHTABLE
#define HASHTABLE
#include <stdbool.h>
#pragma once

// ...
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 50000 // Size of the Hash Table

/**
 * @brief creates a hash index given a string using the modulo operator and table size
 *
 * @param str
 * @return unsigned long
 */
unsigned long hash_function(char *str)
{
    unsigned long i = 0;
    for (int j = 0; str[j]; j++)
        i += str[j];
    return i % CAPACITY;
}

typedef struct Ht_item Ht_item;

// Define the Hash Table Item here
struct Ht_item
{
    char *key;
    char *value;
};

typedef struct LinkedList LinkedList;

// Define the Linkedlist here
struct LinkedList
{
    Ht_item *item;
    LinkedList *next;
};

typedef struct HashTable HashTable;

// Define the Hash Table here
struct HashTable
{
    // Contains an array of pointers
    // to items
    Ht_item **items;
    LinkedList **overflow_buckets;
    int size;
    int count;
};

Ht_item *create_item(char *key, char *value)
{
    // Creates a pointer to a new hash table item
    Ht_item *item = (Ht_item *)malloc(sizeof(Ht_item));
    item->key = (char *)calloc(strlen(key) + 1, sizeof(char));
    item->value = (char *)calloc(strlen(value) + 1, sizeof(char));

    strcpy(item->key, key);
    strcpy(item->value, value);

    return item;
}

static LinkedList *allocate_list()
{
    // Allocates memory for a Linkedlist pointer
    LinkedList *list = (LinkedList *)calloc(1, sizeof(LinkedList));
    return list;
}

HashTable *create_table(int size)
{
    // Creates a new HashTable
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (Ht_item **)calloc(table->size, sizeof(Ht_item *));
    for (int i = 0; i < table->size; i++)
        table->items[i] = NULL;

    return table;
}

void free_item(Ht_item *item)
{
    // Frees an item
    free(item->key);
    free(item->value);
    free(item);
}

void free_hashtable(HashTable *table)
{
    // Frees the table
    for (int i = 0; i < table->size; i++)
    {
        Ht_item *item = table->items[i];
        if (item != NULL)
            free_item(item);
    }

    free(table->items);
    free(table);
}

void ht_insert(HashTable *table, char *key, char *value)
{
    // Create the item
    Ht_item *item = create_item(key, value);

    // Compute the index
    int index = hash_function(key);

    Ht_item *current_item = table->items[index];

    if (current_item == NULL)
    {
        // Key does not exist.
        if (table->count == table->size)
        {
            // Hash Table Full
            printf("Insert Error: Hash Table is full\n");
            // Remove the create item
            free_item(item);
            return;
        }

        // Insert directly
        table->items[index] = item;
        table->count++;
    }
}

char *ht_search(HashTable *table, char *key)
{
    // Searches the key in the hashtable
    // and returns NULL if it doesn't exist
    int index = hash_function(key);
    Ht_item *item = table->items[index];
    LinkedList *head;

    // Ensure that we move to items which are not NULL
    while (item != NULL)
    {
        if (strcmp(item->key, key) == 0)
            return item->value;
        if (head == NULL)
            return NULL;
        item = head->item;
        head = head->next;
    }
    return NULL;
}

void print_hashtable(HashTable *table)
{
    printf("\n--------HashTable---------\n");
    for (int i = 0; i < table->size; i++)
    {
        if (table->items[i])
        {
            printf("index:%d, key:%s, value:%s", i, table->items[i]->key, table->items[i]->value);

            printf("\n");
        }
    }
    printf("--------END--------\n");
}

#endif