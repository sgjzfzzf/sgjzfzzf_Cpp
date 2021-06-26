#include "socketprogram.h"

int main(int argc, char **argv)
{
    int clientfd;
    char *host, *port, buf[MAXLINE];
    if (argc != 3)
    {
        fprintf(stderr, "usage %s <host><port>\n", argv[0]);
        return -1;
    }
    else
    {
        host = argv[1];
        port = argv[2];
        clientfd = open_client(host, port);
        if (clientfd == -1)
        {
            fputs("error", stderr);
            return -1;
        }
        while (fgets(buf, MAXLINE, stdin) != NULL)
        {
            write(clientfd, buf, strlen(buf));
            readline(clientfd, buf);
            fputs(buf, stdout);
        }
        return 0;
    }
}