#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include "hashtable.h"

#include <stdio.h>
#include <time.h>

#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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
void check_host_name(int hostname)
{ // This function returns host name for local computer
    if (hostname == -1)
    {
        perror("gethostname");
        exit(1);
    }
}
void check_host_entry(struct hostent *hostentry)
{ // find host info from host name
    if (hostentry == NULL)
    {
        perror("gethostbyname");
        exit(1);
    }
}
void IP_formatter(char *IPbuffer)
{ // convert IP string to dotted decimal format
    if (NULL == IPbuffer)
    {
        perror("inet_ntoa");
        exit(1);
    }
}
int main()
{
    char host[256];
    char *IP;
    struct hostent *host_entry;
    int hostname;
    hostname = gethostname(host, sizeof(host)); // find the host name
    check_host_name(hostname);
    host_entry = gethostbyname(host); // find host information
    check_host_entry(host_entry);
    IP = inet_ntoa(*((struct in_addr *)host_entry->h_addr_list[0])); // Convert into IP string

    // create a hash data structure
    /* Choose initial capacity of 500 */
    HashTable *ht = create_table(CAPACITY);

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

    char name[25];
    char pass[25];

    printf("\nLogin:");
    scanf("%s", name);

    while (ht_search(ht, name) == NULL)
    {
        printf("\nusername is not in our records, try again:");
        printf("\nLogin:");
        scanf("%s", name);
    }

    printf("Password:");
    scanf("%s", pass);

    int count = 0;

    // have user retry password attempt if the entered password exceeds the length of the actual password or if it is equal to in length but not the same value
    while (!((strncmp(ht_search(ht, name), pass, strlen(ht_search(ht, name)) - 2) == 0)) || (strlen(pass) != (strlen(ht_search(ht, name)) - 2)))
    {
        if (strlen(pass) == strlen(ht_search(ht, name)))
        {
            if (strncmp(ht_search(ht, name), pass, strlen(ht_search(ht, name))))
            {
                exit(1);
            }
            else
            {
                break;
            }
        }
        if (count >= 2)
        {
            printf("\nExceeded 3 Attempts. Account is locked!");
            exit(0);
        }
        printf("\nFailed login! Please re-enter: ");

        time_t rawtime;
        struct tm *timeinfo;

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        fprintf(fptr, "\nHost name: %s (IP: %s) going by user %s failed to log in timestamp: %s", host, IP, name, asctime(timeinfo));

        printf("\nPassword:");
        scanf("%s", pass);
        count++;
    }

    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    fprintf(fptr, "\nHost name: %s (IP: %s) going by user %s succesfully logged in, timestamp : %s", host, IP, name, asctime(timeinfo));
    printf("\nSuccesfully Logged in!");

    fclose(fp);

    fclose(fptr);

    return 0;
}
