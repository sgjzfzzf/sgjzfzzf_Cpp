#include "socketprogram.h"

int open_client(char *hostname, char *port)
{
    int clientfd;
    struct addrinfo hints, *listp, *p;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV | AI_ADDRCONFIG;
    getaddrinfo(hostname, port, &hints, &listp);
    for (p = listp;; p = p->ai_next)
    {
        clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (clientfd < 0)
        {
            continue;
        }
        else if (connect(clientfd, p->ai_addr, p->ai_addrlen) != -1)
        {
            break;
        }
        else
        {
            close(clientfd);
        }
    }
    freeaddrinfo(listp);
    if (!p)
    {
        return -1;
    }
    else
    {
        return clientfd;
    }
}

int open_listenfd(char *port)
{
    int listenfd, optval = 1;
    struct addrinfo hints, *listp, *p;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG | AI_NUMERICSERV;
    getaddrinfo(NULL, port, &hints, &listp);
    for (p = listp;; p = p->ai_next)
    {
        listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (listenfd < 0)
        {
            continue;
        }
        else if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0)
        {
            setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int));
            break;
        }
        else
        {
            close(listenfd);
        }
    }
    freeaddrinfo(listp);
    if (!p)
    {
        return -1;
    }
    else if (listen(listenfd, LISTENQ) < 0)
    {
        close(listenfd);
        return -1;
    }
    else
    {
        return listenfd;
    }
}