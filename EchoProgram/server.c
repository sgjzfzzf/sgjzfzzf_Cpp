#include "socketprogram.h"

void echo(int);

int main(int argc, char **argv)
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    char client_hostname[MAXLINE], client_port[MAXLINE];
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        return -1;
    }
    else
    {
        listenfd = open_listenfd(argv[1]);
        while (1)
        {
            clientlen = sizeof(struct sockaddr_storage);
            connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
            getnameinfo((struct sockaddr *)&clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);
            printf("Connected to (%s, %s)\n", client_hostname, client_port);
            echo(connfd);
            close(connfd);
        }
        return 0;
    }
}

void echo(int connfd)
{
    size_t n;
    char buf[MAXLINE];
    while ((n = readline(connfd, buf)) != 0)
    {
        printf("server received %d bytes\n", (int)n);
        write(connfd, buf, n);
    }
}