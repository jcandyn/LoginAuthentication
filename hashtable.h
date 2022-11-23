#ifndef HASHTABLE
#define HASHTABLE
#pragma once

// ...

#define TABLE_SIZE 7
#define NUM_INPUTS 7

int hash(char *s)
/* Note, this is a horrible hash function.  It's here for
        instructional purposes */
{
    return strlen(s) % TABLE_SIZE;
}

typedef struct entry
{
    char *key;
    int val;
    struct entry *next;
} entry;

entry *table[TABLE_SIZE] = {NULL};

void insert(char *s, int v)
/* this insert is NOT checking for duplicates.  :/ */
{
    int h = hash(s);
    entry *t = (entry *)malloc(sizeof(entry));

    t->key = s;
    t->val = v;
    t->next = table[h];
    table[h] = t;
}

void clean_table()
{
    entry *p, *q;
    int i;

    for (i = 0; i < TABLE_SIZE; ++i)
    {
        for (p = table[i]; p != NULL; p = q)
        {
            q = p->next;
            free(p);
        }
    } // for each entry
} // clean_table

int search(const char *key, int *out_val)
{
    // Find the hash index into the table.
    const int index = hash(key);

    // Now do a linear search through the linked list.
    for (struct entry *node = table[index]; node; node = node->next)
    {
        // If we find a node with a matching key:
        if (strcmp(node->key, key) == 0)
        {
            // Output the value and return 1 for success.
            *out_val = node->val;
            return 1;
        }
    }
    // We didn't find anything. Return 0 for failure.
    return 0;
}
#endif