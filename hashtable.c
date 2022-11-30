#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct
{
    char name[MAX_NAME];
    int age;
    //...add other stuff later,maybe
} person;

person *hash_table[TABLE_SIZE];

unsigned int hash(char *name)
{
    int length = strnlen(name, MAX_NAME);
    unsigned int hash_value = 0;
    for (int i = 0; i < length; i++)
    {
        hash_value += name[i];
        hash_value = (hash_value * name[i]) % TABLE_SIZE;
    }
    return hash_value;
}

void init_hash_table()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hash_table[i] = NULL;
    }
}

void print_table()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (hash_table[i] == NULL)
        {
            printf("\t%i\t---\n", i);
        }
        else
        {
            printf("\t%i\t%s\n", i, hash_table[i]->name);
        }
    }
}

bool hash_table_insert(person *p)
{
    if (p == NULL)
        return false;
    int index = hash(p->name);
    if (hash_table[index] != NULL)
    {
        return false;
    }
    hash_table[index] = p;
    return true;
}

person *hash_table_lookup(char *name)
{
    int index = hash(name);

    if (hash_table[index] != NULL && strcmp(hash_table[index]->name, name) == 0)
    {
        return hash_table[index];
    }
    else
    {
        return NULL;
    }
}

int main()
{
    init_hash_table();
    print_table();

    person jacob = {.name = "Jacob", .age = 256};
    person allen = {.name = "Allen", .age = 27};
    person maria = {.name = "Maria", .age = 17};

    hash_table_insert(&jacob);
    hash_table_insert(&allen);
    hash_table_insert(&maria);

    print_table();

    person *tmp = hash_table_lookup("Maria");

    if (tmp == NULL)
    {
        printf("Not found!\n");
    }
    else
    {
        printf("Found %s.\n", tmp->name);
    }

    return 0;
}
