#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include "hashtable.h"

#include <stdio.h>
#include <time.h>

/**
 * @file script.c
 * @author Joscandy Nunez
 * @brief
 * @version 0.1
 * @date 2022-11-22
 *
 * @copyright Copyright (c) 2022
 *
 */

int main()
{

    // create a hash data structure
    /* Choose initial capacity of 500 */
    HashTable *ht = create_table(5000);

    char *filename = "LoginsAndPasswords.txt";
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    /*CREATE OUTPUT FILE*/
    // write to file
    int num;
    FILE *fptr;

    // use appropriate location if you are using MacOS or Linux
    fptr = fopen("signIn.txt", "w");

    if (fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    /* READ IN FILE */
    fp = fopen(filename, "r");
    if (fp == NULL)
        exit(0);
    static char *couple[2];
    while ((read = getline(&line, &len, fp)) != -1)
    {
        if ((couple[0] = strtok(line, ",")) != NULL)
        {
            couple[1] = strtok(NULL, ", ");
        }

        ht_insert(ht, couple[0], couple[1]);
    }
    print_hashtable(ht);

    // take in login from user

    char name[50];
    char pass[50];
    printf("\nLogin:");
    scanf("%s", &name);
    printf("\nPassword:");
    scanf("%s", &pass);

    printf(ht_search(ht, name));
    int count = 0;
    while ((!strncmp(ht_search(ht, name), pass, sizeof(ht_search(ht, name))) == 0))
    {
        if (count >= 2)
        {
            printf("\nExceeded 3 Attempts. Account is locked!");
            exit(0);
        }
        printf("\nFailed login!");

        time_t rawtime;
        struct tm *timeinfo;

        time(&rawtime);
        timeinfo = localtime(&rawtime);
        printf("Current local time and date: %s", asctime(timeinfo));

        fprintf(fptr, "\n%s Failed logged in %s", name, asctime(timeinfo));

        printf("\nPassword:");
        scanf("%s", &pass);
        count++;
    }

    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    printf("Current local time and date: %s", asctime(timeinfo));

    fprintf(fptr, "\n%s Succesfully logged in %s", name, asctime(timeinfo));
    printf("\nSuccesful Login!");

    fclose(fp);

    fclose(fptr);

    return 0;
}
