#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        puts("Wrong parameter");
        exit(1);
    }
    if (!isdigit(argv[1][0]))
    {
        puts("Wrong parameter");
        exit(1);
    }
    if (atoi(argv[1]) != 1 && atoi(argv[1]) != 2)
    {
        puts("Wrong parameter");
        exit(1);
    }
    struct hostent *host;
    struct in_addr **add_list;
    int mode = atoi(argv[1]);
    struct in_addr add;
    int check = inet_aton(argv[2], &add);
    if ((check == 1 && mode == 2) || (check == 0 && mode == 1))
    {
        puts("Wrong parameter");
        exit(1);
    }
    if (mode == 1)
    {
        host = gethostbyaddr(&add, sizeof(add), AF_INET);
        if (host == NULL)
        {
            puts("Not found information");
            exit(1);
        }
        printf("Official name: %s\n", host->h_name);
        printf("Alias name:\n");
        for (int i = 0; host->h_aliases[i] != NULL; i++)
        {
            printf(" %s\n", host->h_aliases[i]);
        }
    }
    else
    {
        host = gethostbyname(argv[2]);
        if (host == NULL)
        {
            puts("Not found information");
            exit(1);
        }
        printf("Official IP: %s\n", inet_ntoa(*(struct in_addr *)host->h_addr));
        printf("Alias IP:\n");
        add_list = (struct in_addr **)host->h_addr_list;
        for (int i = 1; add_list[i] != NULL; i++)
        {
            printf("%s\n", inet_ntoa(*add_list[i]));
        }
    }
    return 0;
}
