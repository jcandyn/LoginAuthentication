#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

// #include "hashtable.h"

/**
 * @file script.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-11-22
 *
 * @copyright Copyright (c) 2022
 *
 */

// read lines from a file, one at a time
int main()
{

    // create a hash data structure

    char *filename = "LoginsAndPasswords.txt";
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    /* Choose initial capacity of 10 */
    /* Specify the size of the keys and values you want to store once */

    char *username;
    char *password;

    fp = fopen(filename, "r");
    if (fp == NULL)
        exit(0);
    static char *couple[2];
    while ((read = getline(&line, &len, fp)) != -1)
    {
        if ((couple[0] = strtok(line, ",")) != NULL)
        {
            couple[1] = strtok(NULL, ",");
        }
        username = (char *)malloc(sizeof(char) * strlen(couple[0]));
        username = couple[0];
        printf("username:::: %s ", username);

        password = (char *)malloc(sizeof(char) * strlen(couple[1]));
        password = couple[1];
        printf("password:::: %s ", password);

        // Then learn how to split each line into tokens (fields) using ',' as the delimiter
        //  get separated tokens by username and password
        // printf("\n split 0: %s", couple[0]);
        // printf("\n split 1: %s", couple[1]);
        // printf("\n Retrieved line of length %zu:\n", read);
        // printf("%s", line);

        fclose(fp);

        // if (line)
        //     free(line);
        // exit(1);

        return 0;
    }
}
/**
 * @brief







Then learn how to populate and read from this data structure (and print to stdout.)

Each one of these should have its own function.

Each of these have many tutorials available on line. Give it a go and come back when you are stuck. Show your work, explain what you have tried, describe where you are stuck. Turn on all compiler warnings.
 *
 */